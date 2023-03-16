#include <M5Tough.h>
#include <Arduino.h>
#include <lvgl.h>
#include <Wire.h>
#include <SPI.h>

#define LV_HOR_RES_MAX 320
#define LV_VER_RES_MAX 240

// init the tft espi
static lv_disp_draw_buf_t draw_buf;
static lv_disp_drv_t disp_drv;   // Descriptor of a display driver
static lv_indev_drv_t indev_drv; // Descriptor of a touch driver

M5Display *tft;

static void ta_event_cb(lv_event_t * e);
static lv_obj_t * kb;

void tft_lv_initialization() {
  M5.begin();
  lv_init();

  static lv_color_t buf1[(LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10];  // Declare a buffer for 1/10 screen siz
  static lv_color_t buf2[(LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10];  // second buffer is optionnal

  // Initialize `disp_buf` display buffer with the buffer(s).
  lv_disp_draw_buf_init(&draw_buf, buf1, buf2, (LV_HOR_RES_MAX * LV_VER_RES_MAX) / 10);
  tft = &M5.Lcd;
}

// Display flushing
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p) {
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  tft->startWrite();
  tft->setAddrWindow(area->x1, area->y1, w, h);
  tft->pushColors((uint16_t *)&color_p->full, w * h, true);
  tft->endWrite();

  lv_disp_flush_ready(disp);
}

void init_disp_driver() {
  lv_disp_drv_init(&disp_drv);  // Basic initialization

  disp_drv.flush_cb = my_disp_flush;  // Set your driver function
  disp_drv.draw_buf = &draw_buf;      // Assign the buffer to the display
  disp_drv.hor_res = LV_HOR_RES_MAX;  // Set the horizontal resolution of the display
  disp_drv.ver_res = LV_VER_RES_MAX;  // Set the vertical resolution of the display

  lv_disp_drv_register(&disp_drv);                   // Finally register the driver
  lv_disp_set_bg_color(NULL, lv_color_hex3(0x000));  // Set default background color to black
}

void my_touchpad_read(lv_indev_drv_t * drv, lv_indev_data_t * data) {
  TouchPoint_t pos = M5.Touch.getPressPoint();
  bool touched = ( pos.x == -1 ) ? false : true;  
  if (!touched) {    
    data->state = LV_INDEV_STATE_RELEASED;
  } else {
    data->state = LV_INDEV_STATE_PRESSED; 
    data->point.x = pos.x;
    data->point.y = pos.y;
  }
}

void init_touch_driver() {
  lv_disp_drv_register(&disp_drv);
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_t * my_indev = lv_indev_drv_register(&indev_drv);  // register
}

void setup() {
  tft_lv_initialization();
  init_disp_driver();
  init_touch_driver();
  lv_example_meter_1();
}

static lv_obj_t * meter;

static void set_value(void * indic, int32_t v) {
    lv_meter_set_indicator_value(meter, (lv_meter_indicator_t *) indic, v);
}

/**
 * A simple meter
 */
void lv_example_meter_1(void) {
    meter = lv_meter_create(lv_scr_act());
    lv_obj_center(meter);
    lv_obj_set_size(meter, 210, 210);

    /*Add a scale first*/
    lv_meter_scale_t * scale = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale, 37, 2, 9, lv_palette_main(LV_PALETTE_GREY));
    lv_meter_set_scale_range(meter, scale, -180, 180, 360, 90);

    lv_meter_scale_t * scale2 = lv_meter_add_scale(meter);
    lv_meter_set_scale_ticks(meter, scale2, 12, 0, 0, lv_palette_main(LV_PALETTE_GREY));               
    lv_meter_set_scale_major_ticks(meter, scale2, 1, 3, 14, lv_color_black(), 14);    /*Every tick is major*/
    lv_meter_set_scale_range(meter, scale2, -150, 180, 330, 120);

    lv_meter_indicator_t * indic;

    /*Add a red arc to the start*/
    indic = lv_meter_add_arc(meter, scale, 4, lv_palette_main(LV_PALETTE_RED), 2);
    lv_meter_set_indicator_start_value(meter, indic, -60);
    lv_meter_set_indicator_end_value(meter, indic, -20);

    /*Make the tick lines red at the start of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_RED), lv_palette_main(LV_PALETTE_RED),
                                     false, 0);
    lv_meter_set_indicator_start_value(meter, indic, -60);
    lv_meter_set_indicator_end_value(meter, indic, -20);

    /*Add a green arc to the end*/
    indic = lv_meter_add_arc(meter, scale, 4, lv_palette_main(LV_PALETTE_GREEN), 2);
    lv_meter_set_indicator_start_value(meter, indic, 20);
    lv_meter_set_indicator_end_value(meter, indic, 60);

    /*Make the tick lines green at the end of the scale*/
    indic = lv_meter_add_scale_lines(meter, scale, lv_palette_main(LV_PALETTE_GREEN), lv_palette_main(LV_PALETTE_GREEN), false,
                                     0);
    lv_meter_set_indicator_start_value(meter, indic, 20);
    lv_meter_set_indicator_end_value(meter, indic, 60);

    /*Add a needle line indicator*/
    indic = lv_meter_add_needle_line(meter, scale, 6, lv_palette_main(LV_PALETTE_GREY), -10);

    /*Create an animation to set the value*/
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_exec_cb(&a, set_value);
    lv_anim_set_var(&a, indic);
    lv_anim_set_values(&a, -60, -20);
    lv_anim_set_time(&a, 2000);
    lv_anim_set_repeat_delay(&a, 100);
    lv_anim_set_playback_time(&a, 500);
    lv_anim_set_playback_delay(&a, 100);
    lv_anim_set_repeat_count(&a, LV_ANIM_REPEAT_INFINITE);
    lv_anim_start(&a);
}

void loop() {
  M5.update();
  lv_task_handler();
  lv_tick_inc(1);
}