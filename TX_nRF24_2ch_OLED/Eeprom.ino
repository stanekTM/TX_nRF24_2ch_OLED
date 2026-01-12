
//*********************************************************************************************************************
// Clear EEPROM and, if necessary, set default parameters
//*********************************************************************************************************************
void clear_data_eeprom()
{
  unsigned int eepromPos; // For EEPROM position reference
  
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, 0); // Save default "modelActual = 0"
  
  // Start writing default values for every model memory bank
  for (int j = 0; j < MODELS; j++)
  {
    eepromPos = NUM_BYTES_PER_MODEL * j; // Define start position for EEPROM storing (25 * [0, 1, 2, 3, 4...])
    
    // Save default model name "MODEL" 5byte
    for (uint8_t i = 0; i < 5; i++)
    {
      EEPROM.update(eepromPos++, modelName[i]);
    }
    
    EEPROM.update(eepromPos++, 0x00); // Save default REVERSE value in first address of start position
    
    // Save default SUB TRIM center values ​​for two channels in each model memory bank
    for (int i = 0; i < CHANNELS; i++)
    {
      EEPROMUpdateInt(eepromPos, 0);
      eepromPos += 2;
    }
    
    // Save default EPA values for every channels
    for (int i = 0; i < 4; i++)
    {
      EEPROM.update(eepromPos++, epa[i] + EPA_MAX);
    }
    
    // Save default EXPO values will start after first address of start position
    for (int i = 0; i < CHANNELS; i++)
    {
      EEPROM.update(eepromPos++, 0);
    }
  }
}

//*********************************************************************************************************************
// Save to EEPROM and set default parameters if necessary
//*********************************************************************************************************************
void save_data_eeprom()
{
  unsigned int eepromBase; // For EEPROM position reference
  
  eepromBase = NUM_BYTES_PER_MODEL * modelActual; // Define start position for EEPROM write/update (25 * [0, 1, 2, 3, 4...])
  
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, modelActual); // Save ACTUAL MODEL data
  
  unsigned int eepromPos = eepromBase; // For write/update data
  
  // Save model name "XXXXX" 5byte
  for (int i = 0; i < 5; i++)
  {
    EEPROM.update(eepromPos++, modelName[i]);
  }
  
  EEPROM.update(eepromPos++, reverse); // Save REVERSE data
  
  // Save SUB TRIM data
  for (int i = 0; i < CHANNELS; i++)
  {
    EEPROMUpdateInt(eepromPos, subTrim[i]);
    eepromPos += 2;
  }
  
  // Save EPA data
  for (int i = 0; i < 4; i++)
  {
    EEPROM.update(eepromPos, epa[i]);
    eepromPos++;
  }
  
  // Save EXPO data
  for (int i = 0; i < CHANNELS; i++)
  {
    EEPROM.update(eepromPos, expo[i]);
    eepromPos++;
  }
}

//*********************************************************************************************************************
// Save MIN, MAX and CENTER calibration values in EEPROM
//*********************************************************************************************************************
void calib_save_data_eeprom()
{
  unsigned int posEeprom; // For EEPROM position reference
  
  // Save MIN and MAX
  for (int ch = 0; ch < CHANNELS; ch++)
  {
    // MIN
    posEeprom = 1000 + (ch * 4);
    EEPROMUpdateInt(posEeprom, min_pots_calib[ch]);
    
    // MAX
    posEeprom += 2;
    EEPROMUpdateInt(posEeprom, max_pots_calib[ch]);
  }
  
  // Save CENTER
  for (int ch = 0; ch < CHANNELS; ch++)
  {
    posEeprom = 1016 + (ch * 2);
    EEPROMUpdateInt(posEeprom, mid_pots_calib[ch]);
  }
}

//*********************************************************************************************************************
// Reading selected model data from EEPROM
//*********************************************************************************************************************
unsigned char stored_data_eeprom(unsigned char mod)
{
  unsigned int eepromBase; // For EEPROM position reference
  
  // Read which model to upload data
  if (mod == 255)
  {
    mod = EEPROM.read(ACTUAL_MODEL_EEPROM_ADDR);
  }
  
  eepromBase = NUM_BYTES_PER_MODEL * mod; // Define start position for EEPROM read (25 * [0, 1, 2, 3, 4...])
  
  unsigned int eepromPos = eepromBase; // For read data
  
  // Read model name "XXXXX" 5byte
  for (int i = 0; i < 5; i++)
  {
    modelName[i] = EEPROM.read(eepromPos++);
  }
  
  reverse = EEPROM.read(eepromPos++); // Read REVERSE from first position
  
  // Read SUB TRIM offset values for selected model
  for (int i = 0; i < CHANNELS; i++)
  {
    subTrim[i] = EEPROMReadInt(eepromPos);
    eepromPos += 2;
  }
  
  // Read EPA values after first position
  for (int i = 0; i < 4; i++)
  {
    epa[i] = EEPROM.read(eepromPos++);
  }
  
  // Read EXPO values after first position
  for (int i = 0; i < CHANNELS; i++)
  {
    expo[i] = EEPROM.read(eepromPos++);
  } 
  

  // Read MIN, MAX and CENTER values in EEPROM
  unsigned int posEeprom; // For EEPROM position reference
  
  // Read MIN and MAX calibration values from EEPROM
  for (int i = 0; i < CHANNELS; i++)
  {
    // Read MIN calibration values for channels
    posEeprom = 1000 + (i * 4);
    min_pots_calib[i] = EEPROMReadInt(posEeprom);
    
    // Read MAX calibration values for channels
    posEeprom += 2;
    max_pots_calib[i] = EEPROMReadInt(posEeprom);
  }
  
  // Read CENTER calibration values from EEPROM
  for (int i = 0; i < CHANNELS; i++)
  {
    posEeprom = 1016 + (i * 2);
    mid_pots_calib[i] = EEPROMReadInt(posEeprom);
  }
  
  return mod;
}

//*********************************************************************************************************************
// Read and update EEPROM data format
//*********************************************************************************************************************
int EEPROMReadInt(int p_address)
{
  // Read a 16 bit value in EEPROM
  byte Byte1 = EEPROM.read(p_address);
  byte Byte2 = EEPROM.read(p_address + 1);
  
  long firstTwoBytes = ((Byte1 << 0) & 0xFF) + ((Byte2 << 8) & 0xFF00);
  
  return (firstTwoBytes);
}

// Will update only changed value to preserve EEPROM writing cycles
void EEPROMUpdateInt(int p_address, int p_value)
{
  // Write a 16bit value in EEPROM
  byte Byte1 = ((p_value >> 0) & 0xFF);
  byte Byte2 = ((p_value >> 8) & 0xFF);
  
  EEPROM.update(p_address, Byte1);
  EEPROM.update(p_address + 1, Byte2);
}

/*
void EEPROMWriteInt(int p_address, int p_value)
{
  // Write a 16bit value in EEPROM
  byte Byte1 = ((p_value >> 0) & 0xFF);
  byte Byte2 = ((p_value >> 8) & 0xFF);
  
  EEPROM.write(p_address, Byte1);
  EEPROM.write(p_address + 1, Byte2);
}
*/
 
