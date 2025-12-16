
//*********************************************************************************************************************
// Calibration and screen
//*********************************************************************************************************************
void calibration()
{
  while (calibStatus == 1)
  {
    // Reading MIN and MAX value for every channel
    unsigned int raw_pots;
    
    for (int ch = 0; ch < CHANNELS; ch++)
    {
      // Get value from every ADC ports
      raw_pots = analogRead(ch);
      
      // Get MIN values
      if (raw_pots < pot_calib_min[ch])
      {
        pot_calib_min[ch] = raw_pots;
      }
      
      // Get MAX values
      if (raw_pots > pot_calib_max[ch])
      {
        pot_calib_max[ch] = raw_pots;
      }
    }
    
    // Print calibration "MIN-MAX CALIBRATION" real time channels
    calibration_screen();
    
    delay(10);
    
    // Set calibStatus = 0 to exit calibration procedure by pressing button UP
    if (read_button() == 1)
    {
      calibStatus = 0;
    }
  }
  calibStatus = 1;
  
  // Button UP not pressed check
  while (read_button() != 0)
  {
    delay(10);
  }
  
  while (calibStatus == 1)
  {
    for (int ch = 0; ch < CHANNELS; ch++)
    {
      // Get value from every ADC ports
      pot_calib_mid[ch] = analogRead(ch);
    }
    
    // Print calibration "CENTER" real time channels
    calib_center_screen();
    
    delay(10);
    
    // Set calibStatus = 0 to exit calibration procedure by pressing button UP
    if (read_button() == 1)
    {
      calibStatus = 0;
    }
  }
  
  // Print calibration message "SAVE DATA"
  calib_save_screen();
  
  // Save MIN, MAX and CENTER values in Eeprom
  unsigned int posEeprom;
  
  // Save MIN and MAX calibration values from Eeprom
  for (int ch = 0; ch < CHANNELS; ch++)
  {
    // Save MIN calibration values for channels
    posEeprom = 1000 + (ch * 4);
    EEPROMUpdateInt(posEeprom, pot_calib_min[ch]);
    
    // Save MAX calibration values for channels
    posEeprom += 2;
    EEPROMUpdateInt(posEeprom, pot_calib_max[ch]);
  }
  
  // Save CENTER calibration values from Eeprom
  for (int ch = 0; ch < CHANNELS; ch++)
  {
    // Save CENTER calibration values for channels
    posEeprom = 1016 + (ch * 2);
    EEPROMUpdateInt(posEeprom, pot_calib_mid[ch]);
  }
  
  delay(2000); // Screen message for 2sec
}
 
