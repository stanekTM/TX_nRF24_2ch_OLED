
//*********************************************************************************************************************
// Pots calibration
//*********************************************************************************************************************
void calibration()
{
  while (calibStatus == 1)
  {
    // Get MIN and MAX value for each channel
    unsigned int raw_pots;
    
    for (int ch = 0; ch < CHANNELS; ch++)
    {
      raw_pots = analogRead(ch);
      
      // MIN
      if (raw_pots < pot_calib_min[ch])
      {
        pot_calib_min[ch] = raw_pots;
      }
      
      // MAX
      if (raw_pots > pot_calib_max[ch])
      {
        pot_calib_max[ch] = raw_pots;
      }
    }
    
    calibration_screen(); // Print "MIN-MAX CALIBRATION" in real time
    delay(10);
    
    // Set "calibStatus = 0" to exit calibration procedure by pressing button UP
    if (read_button() == 1)
    {
      calibStatus = 0;
    }
  }
  
  calibStatus = 1;
  
  
  // Check if the UP button is not pressed
  while (read_button() != 0)
  {
    delay(10);
  }
  
  
  // Get CENTER value for each channel
  while (calibStatus == 1)
  {
    for (int ch = 0; ch < CHANNELS; ch++)
    {
      pot_calib_mid[ch] = analogRead(ch);
    }
    
    calib_center_screen(); // Print "CENTER CALIBRATION" in real time
    delay(10);
    
    // Set "calibStatus = 0" to exit calibration procedure by pressing button UP
    if (read_button() == 1)
    {
      calibStatus = 0;
    }
  }
  
  
  calib_save_data_eeprom(); // Save MIN, MAX and CENTER calibration values in EEPROM
  
  
  calib_save_data_screen(); // Print message "SAVE DATA CALIBRATION"
  delay(2000);              // Message on screen for 2 seconds
}
 
