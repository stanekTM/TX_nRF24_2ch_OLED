
//*********************************************************************************************************************
// Drawing SAVE DATA screen display
//*********************************************************************************************************************
void save_data_screen()
{
  save_data_eeprom();
  
  // Start of save data message screen
  u8g2.firstPage(); do {
    
    // Set memory buffer for text strings
    char msg_buffer[11];
    
    // Print "SAVE DATA"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[0])));
    u8g2.setCursor(25, 20);
    u8g2.print(msg_buffer);
    
    // Print MODEL NAME "MODEL"
    u8g2.setCursor(25, 40);
    u8g2.print(modelName);
    
    // Print number of which model in use
    u8g2.setCursor(75, 40);
    u8g2.print(modelActual + 1);
    
  } while (u8g2.nextPage());
  
  delay(1000); // Screen message for 1sec
  
  screen--;
  menuActual = 0;
  menuSubActual = 4;
}
 
