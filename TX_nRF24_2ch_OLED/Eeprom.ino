
//*********************************************************************************************************************
// This macro will be used to clear Eeprom and set default parameters if necessary
//*********************************************************************************************************************
void erase_data_eeprom()
{
  unsigned int eepromPos; // For Eeprom position reference
  
  // Update default "modelActual = 0"
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, 0);
  
  // Start writing default values for every model memory bank
  for (int j = 0; j < MODELS; j++)
  {
    // Define start position for Eeprom storing (25 * [0, 1, 2, 3, 4...])
    eepromPos = NUM_BYTES_PER_MODEL * j;
    
    // Update default model name "MODEL" 5byte
    for (uint8_t i = 0; i < 5; i++)
    {
      EEPROM.update(eepromPos++, modelName[i]);
    }
    
    // Update default REVERSE value in first address of start position
    EEPROM.update(eepromPos++, 0x00);
    
    // Update default SUB TRIM center pots values for two channels in every model memory bank
    for (int i = 0; i < CHANNELS; i++)
    {
      EEPROMUpdateInt(eepromPos, 0);
      eepromPos += 2;
    }
    
    // Update default EPA values for every channels
    for (int i = 0; i < 4; i++)
    {
      EEPROM.update(eepromPos++, epa[i] + EPA_MAX);
    }
    
    // Update default EXPO values will start after first address of start position
    for (int i = 0; i < CHANNELS; i++)
    {
      EEPROM.update(eepromPos++, 0);
    }
  }
}

//*********************************************************************************************************************
// This macro will be used to save Eeprom and set default parameters if necessary
//*********************************************************************************************************************
void save_data_eeprom()
{
  unsigned int eepromBase; // For Eeprom position reference
  
  // Define start position for Eeprom write/update (25 * [0, 1, 2, 3, 4...])
  eepromBase = NUM_BYTES_PER_MODEL * modelActual;
  
  // Update ACTUAL MODEL data
  EEPROM.update(ACTUAL_MODEL_EEPROM_ADDR, modelActual);
  

  // For write/update data
  unsigned int eepromPos = eepromBase;
  
  // Update model name "XXXXX" 5byte
  for (int i = 0; i < 5; i++)
  {
    EEPROM.update(eepromPos++, modelName[i]);
  }
  
  // Update REVERSE data
  EEPROM.update(eepromPos++, reverse);
  
  // Update SUB TRIM data
  for (int i = 0; i < CHANNELS; i++)
  {
    EEPROMUpdateInt(eepromPos, subTrim[i]);
    eepromPos += 2;
  }
  
  // Update EPA data
  for (int i = 0; i < 4; i++)
  {
    EEPROM.update(eepromPos, epa[i]);
    eepromPos++;
  }
  
  // Update EXPO data
  for (int i = 0; i < CHANNELS; i++)
  {
    EEPROM.update(eepromPos, expo[i]);
    eepromPos++;
  }
}

//*********************************************************************************************************************
// Macro for read selected model data from Eeprom
//*********************************************************************************************************************
unsigned char stored_data_eeprom(unsigned char mod)
{
  unsigned int eepromBase; // For Eeprom position reference
  
  // Read which model to upload data
  if (mod == 255)
  {
    mod = EEPROM.read(ACTUAL_MODEL_EEPROM_ADDR);
  }
  
  // Define start position for Eeprom read (25 * [0, 1, 2, 3, 4...])
  eepromBase = NUM_BYTES_PER_MODEL * mod;
  
  unsigned int eepromPos = eepromBase;
  
  // Read model name "XXXXX" 5byte
  for (int i = 0; i < 5; i++)
  {
    modelName[i] = EEPROM.read(eepromPos++);
  }
  
  // Read REVERSE from first position
  reverse = EEPROM.read(eepromPos++);
  
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
  

  // Read MIN, MAX and CENTER values in Eeprom
  unsigned int posEeprom; // For Eeprom position reference
  
  // Read MIN and MAX calibration values from Eeprom
  for (int i = 0; i < CHANNELS; i++)
  {
    // Read MIN calibration values for channels
    posEeprom = 1000 + (i * 4);
    pot_calib_min[i] = EEPROMReadInt(posEeprom);
    
    // Read MAX calibration values for channels
    posEeprom += 2;
    pot_calib_max[i] = EEPROMReadInt(posEeprom);
  }
  
  // Read CENTER calibration values from Eeprom
  for (int i = 0; i < CHANNELS; i++)
  {
    posEeprom = 1016 + (i * 2);
    pot_calib_mid[i] = EEPROMReadInt(posEeprom);
  }
  
  return mod;
}

//*********************************************************************************************************************
// Read and Update Eeprom data format
//*********************************************************************************************************************
int EEPROMReadInt(int p_address)
{
  // Read a 16 bit value in Eeprom
  byte Byte1 = EEPROM.read(p_address);
  byte Byte2 = EEPROM.read(p_address + 1);
  
  long firstTwoBytes = ((Byte1 << 0) & 0xFF) + ((Byte2 << 8) & 0xFF00);
  
  return (firstTwoBytes);
}

// Will update only changed value to preserve Eeprom writing cycles
void EEPROMUpdateInt(int p_address, int p_value)
{
  // Write a 16bit value in Eeprom
  byte Byte1 = ((p_value >> 0) & 0xFF);
  byte Byte2 = ((p_value >> 8) & 0xFF);
  
  EEPROM.update(p_address, Byte1);
  EEPROM.update(p_address + 1, Byte2);
}

/*
void EEPROMWriteInt(int p_address, int p_value)
{
  // Write a 16bit value in Eeprom
  byte Byte1 = ((p_value >> 0) & 0xFF);
  byte Byte2 = ((p_value >> 8) & 0xFF);
  
  EEPROM.write(p_address, Byte1);
  EEPROM.write(p_address + 1, Byte2);
}
*/
 
