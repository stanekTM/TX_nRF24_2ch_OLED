
//*********************************************************************************************************************
// Pots calibration
//*********************************************************************************************************************
void calibration()
{
  // Checking the status to start the calibration process
  while (calibStatus == 1)
  {
    // Get MIN and MAX value for each channel
    for (int i = 0; i < RC_CHANNELS; i++)
    {
      raw_pots = analogRead(pins_pots[i]);
      
      // MIN
      if (raw_pots < min_pots_calib[i])
      {
        min_pots_calib[i] = raw_pots;
      }
      
      // MAX
      if (raw_pots > max_pots_calib[i])
      {
        max_pots_calib[i] = raw_pots;
      }
    }
    
    // Print "MIN-MAX CALIBRATION" in real time
    calibration_screen();
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
    for (int i = 0; i < RC_CHANNELS; i++)
    {
      mid_pots_calib[i] = analogRead(pins_pots[i]);
    }
    
    // Print "CENTER CALIBRATION" in real time
    calib_center_screen();
    delay(10);
    
    // Press the UP button to end the calibration process
    if (read_button() == 1)
    {
      calibStatus = 0;
    }
  }
  
  // Save MIN, MAX and CENTER calibration values in EEPROM
  calib_save_data_eeprom();
  
  // Print message "SAVE DATA CALIBRATION"
  calib_save_data_screen();
  delay(2000); // Message on screen for 2 seconds
}
 
