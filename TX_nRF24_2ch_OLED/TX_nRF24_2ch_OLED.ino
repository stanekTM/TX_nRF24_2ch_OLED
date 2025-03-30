
//*********************************************************************************************************************
// RC transmitter for cars, boats and tanks
//******************************************
// Simple surface 2 channel RC transmitter from my repository https://github.com/stanekTM/TX_nRF24_2ch_OLED
//
// The hardware includes nRF24L01+ transceiver and ATmega328P processor with an OLED screen.
// The code is Arduino and contains only the necessary functions of modern transmitters,
// where only the steering and throttle channel is enough without unnecessary functions.
//
// This RC transmitter works with RC receiver from my repository https://github.com/stanekTM/RX_nRF24_Motor_Servo
//
// Thank you to the original authors "Gabapentin" https://github.com/Gabapentin/Arduino-RC-6CH-Radio-control
// and "doohans" https://github.com/doohans/arduino_surface_TX_4ch for code inspiration.
//*********************************************************************************************************************


#include <RF24.h>    // https://github.com/nRF24/RF24
#include <SPI.h>     // Arduino standard library
#include <EEPROM.h>  // Arduino standard library
#include <U8g2lib.h> // https://github.com/olikraus/u8g2
#include "Config.h"  // Load static and variable configuration settings

//*********************************************************************************************************************
// Program setup
//*********************************************************************************************************************
void setup()
{
  //Serial.begin(9600);
  
  radio_setup();
  
  //-----------------------------------------------------------------
  // Debouncing mechanical buttons
  // NOTE: For input pin buttons is necessary to mount on every pin
  // 0,1uF/100nF(104)ceramic capacitors from pin to GND
  //-----------------------------------------------------------------
  pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
  pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);
  pinMode(PIN_BUTTON_SELECT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_EXIT, INPUT_PULLUP);
  
  // LCD config with U8G2 library display init (mandatory)
  //u8g2.setBusClock(800000); //max 800000
  u8g2.begin();
  //u8g2.setFlipMode(1);   
  //u8g2.setContrast(10);
  // Set default font type used for all display sessions (mandatory)
  u8g2.setFont(u8g2_font_7x13_tr); // height 9 pixels (X11)
  
  // Print boot screen
  u8g2.firstPage(); do {
    
    // Print version string
    u8g2.setCursor(0, 28);
    u8g2.print(fw_version);

  } while (u8g2.nextPage());
  
  delay(1000);
  
  // NOTE: SHOULD BE USED FOR THE FIRST TIME AFTER CALIBRATION !!!
  resetEeprom_screen(); // Print "ERASE DATA" screen
  
  // Load data from Eeprom
  modelActual = storedDataEeprom(255);
}

//*********************************************************************************************************************
// Program loop
//*********************************************************************************************************************
void loop()
{
  // Start Calibration screen if button SELECT is pressed on power on
  if (calibStatus == 1 && read_button() == 2)
  {
    // Recall calibration procedure
    Calibration();
  }
  // Set condition 0 to continue loop if calibration procedure is not selected
  else
  {
    calibStatus = 0;
  }
  
  
  rc_packet.ch1 = pots_value[0]; // A0
  rc_packet.ch2 = pots_value[1]; // A1
  telemetry_packet.rssi = 0;
  
  send_and_receive_data();
  
  TX_batt_monitoring();
  RX_batt_monitoring();
  
  read_button_exit();      // Macro for read button status definitions
  read_pots();             // Macro for read pots, joysticks, values, applying calibration and rules
  select();                // Select screen, calibration, step control for channels/values
}
 
