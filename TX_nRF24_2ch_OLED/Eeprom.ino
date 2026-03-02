
//*********************************************************************************************************************
// Reading selected model data from EEPROM
//*********************************************************************************************************************
unsigned char stored_data_eeprom(unsigned char mod)
{
  // Read which model to upload data
  if (mod == 255)
  {
    mod = EEPROM.read(ACTUAL_MODEL_EEPROM_ADDR); // mod 0 to 9
  }
  
  // Define start position for EEPROM read (25 * [0, 1, 2, 3, 4...])
  unsigned int eeprom_pos = NUM_BYTES_PER_MODEL * mod;
  
  // Read model name "XXXXX"
  for (int i = 0; i < 5; i++)
  {
    modelName[i] = EEPROM.read(eeprom_pos++);
    //Serial.println(eeprom_pos); // 1, 2, 3, 4, 5 (5 byte)
    //Serial.println(modelName[i]);
  }
  
  // Read EPA
  for (int i = 0; i < 4; i++)
  {
    epa[i] = EEPROM.read(eeprom_pos++);
    //Serial.println(eeprom_pos); // 6, 7, 8, 9
    //Serial.println(epa[i]);
  }
  
  // Read EXPO
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    expo[i] = EEPROM.read(eeprom_pos++);
    //Serial.println(eeprom_pos); // 10, 11
    //Serial.println(expo[i]);
  }
  
  // Read SUB TRIM
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.get(eeprom_pos, subTrim[i]);
    eeprom_pos += 2;
    //Serial.println(eeprom_pos); // (12)13, (14)15 (2 bytes)
    //Serial.println(subTrim[i]);
  }
  
  // Read REVERSE
  reverse = EEPROM.read(eeprom_pos++);
  //Serial.println(eeprom_pos); // 16
  //Serial.println(reverse);    // bit 0 NOR and NOR, bit 1 REV and NOR, bit 2 NOR and REV, bit 3 REV and REV
  
  // Read RC channels
  for (int i = 0; i < RC_CHANNELS; i++)
  {  
    EEPROM.get( i * 4 + 1000,      min_pots_calib[i]);
    EEPROM.get((i * 4 + 1000) + 2, max_pots_calib[i]);
    EEPROM.get( i * 2 + 1016,      mid_pots_calib[i]);
  }
  
  return mod;
}

//*********************************************************************************************************************
// Save to EEPROM and set default parameters if necessary
//*********************************************************************************************************************
void save_data_eeprom()
{
  // Save ACTUAL MODEL
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, modelActual);
  
  // Define start position for EEPROM write/update (25 * [0, 1, 2, 3, 4...])
  unsigned int eeprom_pos = NUM_BYTES_PER_MODEL * modelActual;
  
  // Save model name "XXXXX"
  for (int i = 0; i < 5; i++)
  {
    EEPROM.update(eeprom_pos++, modelName[i]);
    //Serial.println(eeprom_pos); // 1, 2, 3, 4, 5 (5 byte)
    //Serial.println(modelName[i]);
  }
  
  // Save EPA
  for (int i = 0; i < 4; i++)
  {
    EEPROM.update(eeprom_pos++, epa[i]);
    //Serial.println(eeprom_pos); // 6, 7, 8, 9
    //Serial.println(epa[i]);
  }
  
  // Save EXPO
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.update(eeprom_pos++, expo[i]);
    //Serial.println(eeprom_pos); // 10, 11
    //Serial.println(expo[i]);
  }
  
  // Save SUB TRIM
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.put(eeprom_pos, subTrim[i]);
    eeprom_pos += 2;
    //Serial.println(eeprom_pos); // (12)13, (14)15 (2 bytes)
    //Serial.println(subTrim[i]);
  } 
  
  // Save REVERSE
  EEPROM.update(eeprom_pos++, reverse);
  //Serial.println(eeprom_pos); // 16
  //Serial.println(reverse);    // bit 0 NOR and NOR, bit 1 REV and NOR, bit 2 NOR and REV, bit 3 REV and REV
}

//*********************************************************************************************************************
// Clear EEPROM and, if necessary, set default parameters
//*********************************************************************************************************************
void clear_data_eeprom()
{
  // Save default "modelActual = 0"
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, 0);
  
  // Start writing default values for every model memory bank
  for (int j = 0; j < MODELS; j++)
  {
    // Define start position for EEPROM storing (25 * [0, 1, 2, 3, 4...])
    unsigned int eeprom_pos = NUM_BYTES_PER_MODEL * j;
    
    // Save default model name "MODEL"
    for (int i = 0; i < 5; i++)
    {
      EEPROM.update(eeprom_pos++, modelName[i]);
      //Serial.println(eeprom_pos); // 1, 2, 3, 4, 5 (5 byte)
      //Serial.println(modelName[i]);
    }
    
    // Save default EPA 100%
    for (int i = 0; i < 4; i++)
    {
      EEPROM.update(eeprom_pos++, epa[i] + EPA_MAX);
      //Serial.println(eeprom_pos); // 6, 7, 8, 9
      //Serial.println(epa[i]);
    }
    
    // Save default EXPO
    for (int i = 0; i < RC_CHANNELS; i++)
    {
      EEPROM.update(eeprom_pos++, expo[i]);
      //Serial.println(eeprom_pos); // 10, 11
      //Serial.println(expo[i]);
    }
    
    // Save default SUB TRIM
    for (int i = 0; i < RC_CHANNELS; i++)
    {
      EEPROM.put(eeprom_pos, subTrim[i]);
      eeprom_pos += 2;
      //Serial.println(eeprom_pos); // (12)13, (14)15 (2 bytes)
      //Serial.println(subTrim[i]);
    }
    
    // Save default REVERSE (NOR and NOR)
    EEPROM.update(eeprom_pos++, reverse);
    //Serial.println(eeprom_pos); // 16
    //Serial.println(reverse);    // bit 0
  }
}

//*********************************************************************************************************************
// Save min., max. and center calibration values in EEPROM
//*********************************************************************************************************************
void calib_save_data_eeprom()
{
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.put( i * 4 + 1000,      min_pots_calib[i]);
    EEPROM.put((i * 4 + 1000) + 2, max_pots_calib[i]);
    EEPROM.put( i * 2 + 1016,      mid_pots_calib[i]);
  }
}
 
