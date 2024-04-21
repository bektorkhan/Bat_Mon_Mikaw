ESP32 esp32-2432s028 2.8" Touch Battery Motor Monitor for sailboat

## Using command line to upload firmware

````
python3 "~/.arduino15/packages/esp32/tools/esptool_py/4.5.1/esptool.py" \
 --chip esp32 --port "/dev/ttyACM0" --baud 921600  \
 --before default_reset --after hard_reset write_flash  \
 -z --flash_mode dio --flash_freq 80m --flash_size 16MB \
 0x1000 "bbn_m5tough_active_boat.ino.bootloader.bin" \
 0x8000 "bbn_m5tough_active_boat.ino.partitions.bin" \
 0xe000 "~/.arduino15/packages/esp32/hardware/esp32/2.0.9/tools/partitions/boot_app0.bin" \
 0x10000 "bbn_m5tough_active_boat.ino.bin" 
````


## Related projects:

https://github.com/m5stack/M5Tough

https://github.com/JohnySeven/SensESPWatch

https://github.com/JohnySeven/TWatchSK

https://github.com/SignalK/SensESP

https://github.com/norbert-walter/esp32-nmea2000

https://github.com/hatlabs/SH-wg-firmware

https://github.com/hatlabs/SH-ESP32-nmea2000-gateway

https://github.com/andyrbarrow/SignalKM5StackInstrument

https://github.com/bareboat-necessities/my-bareboat/tree/master/m5-boat-display

https://github.com/andyrbarrow/MQTTNMEADisplay

https://github.com/bareboat-necessities/rust-modules/tree/main/lightning-detect

https://github.com/idreamsi/LoRa-GPS-Tracker

https://bareboat-necessities.github.io/my-bareboat/bareboat-math.html

https://github.com/BjarneBitscrambler/SignalK-Orientation

https://github.com/SensESP/ve.direct_mppt

https://github.com/SensESP/VEDirect

https://github.com/joelkoz/CommonSens/tree/main/signalk-smart-switch

https://github.com/arduino-libraries

https://github.com/mhaberler/SensESP-M5Stack

https://github.com/wellenvogel/esp32-nmea2000

https://github.com/AK-Homberger/NMEA2000WifiGateway-with-ESP32

https://github.com/AK-Homberger/NMEA2000-SignalK-Gateway

https://github.com/AK-Homberger/NMEA2000-AIS-Gateway

https://github.com/AK-Homberger/ESP32-Evo-Remote-Pilot-NMEA2000

https://github.com/AK-Homberger/NMEA2000-TempPressure

https://github.com/wholybee/esp32-smartBMSdisplay

https://github.com/ChrisLizon/VictronSOCLCD

https://github.com/jukolein/W132

https://github.com/RalfJL/VE.Direct2MQTT

https://github.com/humppafreak/SensESP-PeetBrosWind

https://github.com/sharandac/My-TTGO-Watch

https://github.com/spascual90/Fenix

https://github.com/KimBP/AIS/blob/master/Examples/AISDecode/AISDecode.ino

https://github.com/skpang/Teensy40_800x400_LCD50_LVGL_NMEA2000_mfd

https://github.com/bareboat-necessities/bbn-nmea200-m5atom

https://github.com/speters/ClipperDuet2N2k

TackTick Micronet to NMEA DIY
https://github.com/Rodemfr/MicronetToNMEA

Seatalk (arduino mega). esp32 doesn't support 9-bit UART required for Seatalk1
https://github.com/yOyOeK1/seatalk4

Script that reads 9-bits seatalk 1 messages from any GPIO port using bitbanging, and converts it into NMEA0183 messages
https://github.com/marcobergman/seatalk_convert

LoRa anchor alarm
https://github.com/factoidforrest/anchor-alarm-lora

SeaTalk Autopilot Control
https://github.com/nauti-control/STWirelessRemote
