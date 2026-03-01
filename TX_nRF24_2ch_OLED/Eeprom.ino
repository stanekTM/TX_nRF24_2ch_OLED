
//*********************************************************************************************************************
// Reading selected model data from EEPROM
//*********************************************************************************************************************
unsigned char stored_data_eeprom(unsigned char mod)
{
  // Read which model to upload data
  if (mod == 255)
  {
    mod = EEPROM.read(ACTUAL_MODEL_EEPROM_ADDR);
  }
  
  // Define start position for EEPROM read (25 * [0, 1, 2, 3, 4...])
  unsigned int eeprom_pos = NUM_BYTES_PER_MODEL * mod;
  
  // Read model name "XXXXX" 5 byte
  for (int i = 0; i < 5; i++)
  {
    modelName[i] = EEPROM.read(eeprom_pos++);
  }
  
  // Read EPA
  for (int i = 0; i < 4; i++)
  {
    epa[i] = EEPROM.read(eeprom_pos++);
  }
  
  // Read REVERSE
  reverse = EEPROM.read(eeprom_pos++);
  
  // Read SUB TRIM
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.get(eeprom_pos, subTrim[i]);
    eeprom_pos += 2;
  }
  
  // Read EXPO
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    expo[i] = EEPROM.read(eeprom_pos++);
  }
  
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
  
  // Save model name "XXXXX" 5 byte
  for (int i = 0; i < 5; i++)
  {
    EEPROM.update(eeprom_pos++, modelName[i]);
  }
  
  // Save EPA
  for (int i = 0; i < 4; i++)
  {
    EEPROM.update(eeprom_pos++, epa[i]);
  }
  
  // Save REVERSE
  EEPROM.update(eeprom_pos++, reverse);
  
  // Save SUB TRIM
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.put(eeprom_pos, subTrim[i]);
    eeprom_pos += 2;
  } 
  
  // Save EXPO
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    EEPROM.update(eeprom_pos++, expo[i]);
  }
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
    
    // Save default model name "MODEL" 5 byte
    for (int i = 0; i < 5; i++)
    {
      EEPROM.update(eeprom_pos++, modelName[i]);
    }
    
    // Save default EPA
    for (int i = 0; i < 4; i++)
    {
      EEPROM.update(eeprom_pos++, epa[i] + EPA_MAX);
    }
    
    // Save default REVERSE
    EEPROM.update(eeprom_pos++, reverse);
    
    // Save default SUB TRIM
    for (int i = 0; i < RC_CHANNELS; i++)
    {
      EEPROM.put(eeprom_pos, subTrim[i]);
      eeprom_pos += 2;
    }
    
    // Save default EXPO
    for (int i = 0; i < RC_CHANNELS; i++)
    {
      EEPROM.update(eeprom_pos++, expo[i]);
    }
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
 
