# RC transmitter
Simple surface 2 channel RC transmitter.
Includes nRF24L01+ transceiver and ATmega328P processor with an OLED screen.
The code is Arduino and contains only the necessary functions of modern transmitters, where only the steering and throttle channel is enough without unnecessary functions.
Telemetry monitors receiver voltage and "fake" RSSI (the nRF24L01+ transceiver does not contain real RSSI and is only a rough counting of lost packets).

This RC transmitter works with RC receiver from my repository [**RX_nRF24_Motor_Servo**](https://github.com/stanekTM/RX_nRF24_Motor_Servo).

Thank you to the original authors "Gabapentin" [Arduino-RC-6CH-Radio-control](https://github.com/Gabapentin/Arduino-RC-6CH-Radio-control) and "doohans" [arduino_surface_TX_4ch](https://github.com/doohans/arduino_surface_TX_4ch) for code inspiration.

## The firmware includes
* Two proportional channels 1000us - 2000us
* Adjustable left and right endpoints 0 - 100%
* Adjustable sub-trims +-125us
* Adjustable exponential curves in steps 1 - 9
* Channel reverse
* Calibration of potentiometers
* Memory for ten models
* Five character model name
* RX voltage telemetry

## Arduino pins
```
A0 - joystick 1
A1 - joystick 2

D2 - button Up/Prev
D3 - button Down/Next
D4 - button Menu/Select
D5 - button Exit

A7 - input TX battery

OLED I2C:
A4 - SDA
A5 - SCL

nRF24L01:
D9  - CE
D10 - CSN
D11 - MOSI
D12 - MISO
D13 - SCK
```

## Used libraries
* <RF24.h>    https://github.com/nRF24/RF24
* <U8g2lib.h> https://github.com/olikraus/u8g2
* <EEPROM.h>  Arduino standard library
* <SPI.h>     Arduino standard library
