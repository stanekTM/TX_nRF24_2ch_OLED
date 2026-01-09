/*
  **************************************************************************************************************
  RC transmitter
  **************
  Simple surface 2 channel RC transmitter from my repository https://github.com/stanekTM/TX_nRF24_2ch_OLED
  
  This RC transmitter works with RC receiver from my repository https://github.com/stanekTM/RX_nRF24_Motor_Servo
  
  Thank you to the original authors "Gabapentin" https://github.com/Gabapentin/Arduino-RC-6CH-Radio-control
  and "doohans" https://github.com/doohans/arduino_surface_TX_4ch for code inspiration.
  **************************************************************************************************************
*/

#include <RF24.h>    // v1.4.11
#include <RF24_config.h>
#include <nRF24L01.h>
#include <SPI.h>
#include <EEPROM.h>
#include <U8g2lib.h> // v2.33.15
#include "Config.h"  // Load static and variable configuration settings

//**************************************************************************************************************
// Program setup
//**************************************************************************************************************
void setup()
{
  //Serial.begin(9600);
  
  radio_setup();
  
  pinMode(PIN_BUTTON_UP, INPUT_PULLUP);
  pinMode(PIN_BUTTON_DOWN, INPUT_PULLUP);
  pinMode(PIN_BUTTON_SELECT, INPUT_PULLUP);
  pinMode(PIN_BUTTON_EXIT, INPUT_PULLUP);
  
  // OLED SSD1306 I2C config
  u8g2.begin();
  u8g2.setBusClock(1000000);
  //u8g2.setFlipMode(1);
  //u8g2.setContrast(10);
  // Set default font type used for all display sessions (mandatory)
  u8g2.setFont(u8g2_font_7x13_tr); // Height 9 pixels (X11)
  
  // Print boot screen
  u8g2.firstPage(); do {
    
    // Print version string
    u8g2.setCursor(0, 28);
    u8g2.print(fw_version);
    
  } while (u8g2.nextPage());
  
  delay(1000);
  
  // If you hold down the EXIT button while powering on, you can clear/write the data to the default values
  clear_data_screen(); // Print screen CLEAR DATA? message
  
  modelActual = stored_data_eeprom(255); // Reading selected model data from EEPROM
}

//**************************************************************************************************************
// Program loop
//**************************************************************************************************************
void loop()
{
  // If you hold down the SELECT button while powering on, the calibration procedure will start
  if (calibStatus == 1 && read_button() == 2)
  {
    calibration();
  }
  else
  {
    calibStatus = 0;
  }
  
  send_and_receive_data();
  
  read_pots();
  
  rc_packet.ch1 = pots_value[0]; // A0
  rc_packet.ch2 = pots_value[1]; // A1
  
  TX_batt_monitoring();
  RX_batt_monitoring();
  
  select();
}
 
