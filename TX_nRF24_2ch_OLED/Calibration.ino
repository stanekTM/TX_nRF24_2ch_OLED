
//*********************************************************************************************************************
// Pots calibration
//*********************************************************************************************************************
void calibration()
{
  // Checking the status to start the calibration process
  while (calibStatus == 1)
  {
    // Get MIN and MAX value for each channel

    for (int ch = 0; ch < CHANNELS; ch++)
    {
      raw_pots = analogRead(ch);
      
      // MIN
      if (raw_pots < min_pots_calib[ch])
      {
        min_pots_calib[ch] = raw_pots;
      }
      
      // MAX
      if (raw_pots > max_pots_calib[ch])
      {
        max_pots_calib[ch] = raw_pots;
      }
    }
    
    calibration_screen(); // Print "MIN-MAX CALIBRATION" in real time
    delay(10);
    
    // Press the UP button to end the calibration process
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
  
  
  // Checking the status to start the calibration process
  while (calibStatus == 1)
  {
    // Get CENTER value for each channel
    for (int ch = 0; ch < CHANNELS; ch++)
    {
      mid_pots_calib[ch] = analogRead(ch);
    }
    
    calib_center_screen(); // Print "CENTER CALIBRATION" in real time
    delay(10);
    
    // Press the UP button to end the calibration process
    if (read_button() == 1)
    {
      calibStatus = 0;
    }
  }
  
  
  calib_save_data_eeprom(); // Save MIN, MAX and CENTER calibration values in EEPROM
  
  
  calib_save_data_screen(); // Print message "SAVE DATA CALIBRATION"
  delay(2000);              // Message on screen for 2 seconds
}
 
