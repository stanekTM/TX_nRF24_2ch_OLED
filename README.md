## Surface 2 channel RC transmitter
Hardware includes nRF24L01+ transceiver and ATmega328P processor with an OLED screen.

The code is Arduino and contains only the necessary functions of modern transmitters, where only the steering and throttle channel is enough without unnecessary functions.

Telemetry monitors receiver voltage and "fake" RSSI (the nRF24L01+ transceiver does not contain real RSSI and is only a rough counting of lost packets).

This RC transmitter works with RC receiver from my repository [**RX_nRF24_Stanek**](https://github.com/stanekTM/RX_nRF24_Stanek).

### The firmware includes
* Two proportional channels 1000us -> 2000us
* Adjustable left and right endpoints 0 -> 100% (+-500us)
* Adjustable sub-trims +-100us
* Adjustable exponential curves in steps 1 -> 9
* Channel reverse
* Calibration of potentiometers
* Memory for 10 models
* Five character model name
* RX voltage telemetry
* Deleting all saved data (out of calibration)

### Arduino pins
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

nRF24L01+:
D9  - CE
D10 - CSN
D11 - MOSI
D12 - MISO
D13 - SCK
```
