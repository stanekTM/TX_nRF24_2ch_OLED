
//*********************************************************************************************************************
// Clear EEPROM and, if necessary, set default parameters
//*********************************************************************************************************************
void clear_data_eeprom()
{
  unsigned int eeprom_pos; // For EEPROM position reference
  
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, 0); // Save default "modelActual = 0"
  
  // Start writing default values for every model memory bank
  for (int j = 0; j < MODELS; j++)
  {
    eeprom_pos = NUM_BYTES_PER_MODEL * j; // Define start position for EEPROM storing (25 * [0, 1, 2, 3, 4...])
    
    // Save default model name "MODEL" 5byte
    for (uint8_t i = 0; i < 5; i++)
    {
      EEPROM.update(eeprom_pos++, modelName[i]);
    }
    
    EEPROM.update(eeprom_pos++, 0x00); // Save default REVERSE value in first address of start position
    
    // Save default SUB TRIM center values ​​for two channels in each model memory bank
    for (int i = 0; i < CHANNELS; i++)
    {
      EEPROMUpdateInt(eeprom_pos, 0);
      eeprom_pos += 2;
    }
    
    // Save default EPA values for every channels
    for (int i = 0; i < 4; i++)
    {
      EEPROM.update(eeprom_pos++, epa[i] + EPA_MAX);
    }
    
    // Save default EXPO values will start after first address of start position
    for (int i = 0; i < CHANNELS; i++)
    {
      EEPROM.update(eeprom_pos++, 0);
    }
  }
}

//*********************************************************************************************************************
// Save to EEPROM and set default parameters if necessary
//*********************************************************************************************************************
void save_data_eeprom()
{
  unsigned int eeprom_base; // For EEPROM position reference
  
  eeprom_base = NUM_BYTES_PER_MODEL * modelActual; // Define start position for EEPROM write/update (25 * [0, 1, 2, 3, 4...])
  
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, modelActual); // Save ACTUAL MODEL data
  
  unsigned int eeprom_pos = eeprom_base; // For write/update data
  
  // Save model name "XXXXX" 5byte
  for (int i = 0; i < 5; i++)
  {
    EEPROM.update(eeprom_pos++, modelName[i]);
  }
  
  EEPROM.update(eeprom_pos++, reverse); // Save REVERSE data
  
  // Save SUB TRIM data
  for (int i = 0; i < CHANNELS; i++)
  {
    EEPROMUpdateInt(eeprom_pos, subTrim[i]);
    eeprom_pos += 2;
  }
  
  // Save EPA data
  for (int i = 0; i < 4; i++)
  {
    EEPROM.update(eeprom_pos, epa[i]);
    eeprom_pos++;
  }
  
  // Save EXPO data
  for (int i = 0; i < CHANNELS; i++)
  {
    EEPROM.update(eeprom_pos, expo[i]);
    eeprom_pos++;
  }
}

//*********************************************************************************************************************
// Save MIN, MAX and CENTER calibration values in EEPROM
//*********************************************************************************************************************
void calib_save_data_eeprom()
{
  unsigned int eeprom_pos; // For EEPROM position reference
  
  // Save MIN and MAX
  for (int i = 0; i < CHANNELS; i++)
  {
    // MIN
    eeprom_pos = 1000 + (i * 4);
    EEPROMUpdateInt(eeprom_pos, min_pots_calib[i]);
    
    // MAX
    eeprom_pos += 2;
    EEPROMUpdateInt(eeprom_pos, max_pots_calib[i]);
  }
  
  // Save CENTER
  for (int i = 0; i < CHANNELS; i++)
  {
    eeprom_pos = 1016 + (i * 2);
    EEPROMUpdateInt(eeprom_pos, mid_pots_calib[i]);
  }
}

//*********************************************************************************************************************
// Reading selected model data from EEPROM
//*********************************************************************************************************************
unsigned char stored_data_eeprom(unsigned char mod)
{
  unsigned int eeprom_base; // For EEPROM position reference
  
  // Read which model to upload data
  if (mod == 255)
  {
    mod = EEPROM.read(ACTUAL_MODEL_EEPROM_ADDR);
  }
  
  eeprom_base = NUM_BYTES_PER_MODEL * mod; // Define start position for EEPROM read (25 * [0, 1, 2, 3, 4...])
  
  unsigned int eeprom_pos = eeprom_base; // For read data
  
  // Read model name "XXXXX" 5byte
  for (int i = 0; i < 5; i++)
  {
    modelName[i] = EEPROM.read(eeprom_pos++);
  }
  
  reverse = EEPROM.read(eeprom_pos++); // Read REVERSE from first position
  
  // Read SUB TRIM offset values for selected model
  for (int i = 0; i < CHANNELS; i++)
  {
    subTrim[i] = EEPROMReadInt(eeprom_pos);
    eeprom_pos += 2;
  }
  
  // Read EPA values after first position
  for (int i = 0; i < 4; i++)
  {
    epa[i] = EEPROM.read(eeprom_pos++);
  }
  
  // Read EXPO values after first position
  for (int i = 0; i < CHANNELS; i++)
  {
    expo[i] = EEPROM.read(eeprom_pos++);
  } 
  

  // Read MIN, MAX and CENTER values in EEPROM
  unsigned int pos_eeprom; // For EEPROM position reference
  
  // Read MIN and MAX calibration values from EEPROM
  for (int i = 0; i < CHANNELS; i++)
  {
    // Read MIN calibration values for channels
    pos_eeprom = 1000 + (i * 4);
    min_pots_calib[i] = EEPROMReadInt(pos_eeprom);
    
    // Read MAX calibration values for channels
    pos_eeprom += 2;
    max_pots_calib[i] = EEPROMReadInt(pos_eeprom);
  }
  
  // Read CENTER calibration values from EEPROM
  for (int i = 0; i < CHANNELS; i++)
  {
    pos_eeprom = 1016 + (i * 2);
    mid_pots_calib[i] = EEPROMReadInt(pos_eeprom);
  }
  
  return mod;
}

//*********************************************************************************************************************
// Read and update EEPROM data format
//*********************************************************************************************************************
int EEPROMReadInt(int p_address)
{
  // Read a 16 bit value in EEPROM
  byte byte1 = EEPROM.read(p_address);
  byte byte2 = EEPROM.read(p_address + 1);
  
  long first_two_bytes = ((byte1 << 0) & 0xFF) + ((byte2 << 8) & 0xFF00);
  
  return (first_two_bytes);
}

// Will update only changed value to preserve EEPROM writing cycles
void EEPROMUpdateInt(int p_address, int p_value)
{
  // Write a 16bit value in EEPROM
  byte byte1 = ((p_value >> 0) & 0xFF);
  byte byte2 = ((p_value >> 8) & 0xFF);
  
  EEPROM.update(p_address, byte1);
  EEPROM.update(p_address + 1, byte2);
}

/*
void EEPROMWriteInt(int p_address, int p_value)
{
  // Write a 16bit value in EEPROM
  byte byte1 = ((p_value >> 0) & 0xFF);
  byte byte2 = ((p_value >> 8) & 0xFF);
  
  EEPROM.write(p_address, byte1);
  EEPROM.write(p_address + 1, byte2);
}
*/
 
