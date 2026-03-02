
//*********************************************************************************************************************
// Load selected model data from EEPROM (locations 1 to 160 bytes), RC channels EEPROM locations 212 to 222 bytes
//*********************************************************************************************************************
unsigned char load_data_eeprom(unsigned char model)
{
  // Read ACTUAL MODEL
  if (model == 255)
  {
    model = EEPROM.read(ACTUAL_MODEL_EEPROM_ADDR); // model 0 to 9
  }
  
  // Define the starting position of reading from EEPROM (16 * (0, 1, 2, 3, 4...))
  unsigned int eeprom_pos = NUM_BYTES_PER_MODEL * model; // EEPROM locations 1 to 160 bytes
  
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
  
  // Read RC channels EEPROM locations 212 to 222 bytes
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.get(i * 6 + 200, min_pots_calib[i]); // EEPROM locations 212, 218
    EEPROM.get(i * 6 + 202, mid_pots_calib[i]); // EEPROM locations 214, 220
    EEPROM.get(i * 6 + 204, max_pots_calib[i]); // EEPROM locations 216, 222
  }
  
  return model;
}

//*********************************************************************************************************************
// Save selected model data to EEPROM (locations 1 to 160 bytes)
//*********************************************************************************************************************
void save_data_eeprom()
{
  // Save ACTUAL MODEL
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, modelActual);
  
  // Define the initial position of saving to EEPROM
  unsigned int eeprom_pos = NUM_BYTES_PER_MODEL * modelActual; // EEPROM locations 1 to 160 bytes
  
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
// Clear all model data and save default values ​​to EEPROM (locations 1 to 160 bytes)
//*********************************************************************************************************************
void clear_data_eeprom()
{
  // Save default ACTUAL MODEL
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, 0);
  
  // Start saving all default model data for each memory bank
  for (int j = 0; j < MODELS; j++)
  {
    // Define the initial save position for each memory bank
    unsigned int eeprom_pos = NUM_BYTES_PER_MODEL * j;  // EEPROM locations 1 to 160 bytes
    
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
// Save RC channel calibration values ​​to EEPROM (locations 212 to 222 bytes)
//*********************************************************************************************************************
void calib_save_data_eeprom()
{
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.put(i * 6 + 200, min_pots_calib[i]); // EEPROM locations 212, 218
    EEPROM.put(i * 6 + 202, mid_pots_calib[i]); // EEPROM locations 214, 220
    EEPROM.put(i * 6 + 204, max_pots_calib[i]); // EEPROM locations 216, 222
  }
}
 
