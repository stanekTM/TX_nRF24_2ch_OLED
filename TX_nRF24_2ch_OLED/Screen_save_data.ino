
//*********************************************************************************************************************
// Print screen SAVE DATA message
//*********************************************************************************************************************
void save_data_screen()
{
  save_data_eeprom(); // Save to EEPROM and set default parameters if necessary
  
  
  u8g2.firstPage(); do {
    
    char msg_buffer[13]; // Set memory buffer for text strings
    
    // Print "SAVE DATA"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[0])));
    u8g2.setCursor(25, 20);
    u8g2.print(msg_buffer);
    
    // Print model name "XXXXX"
    u8g2.setCursor(25, 40);
    u8g2.print(modelName);
    
    // Print number of which model in use
    u8g2.setCursor(63, 40);
    u8g2.print(modelActual + 1);
    
  } while (u8g2.nextPage());
  
  delay(1000); // Screen message for 1sec
  
  screen--;
  menuActual = 0;
  menuSubActual = 4;
}
 
