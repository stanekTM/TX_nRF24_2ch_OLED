
//*********************************************************************************************************************
// Print screen CLEAR DATA? message
// If you hold down the EXIT button while powering on, you can clear/write the data to the default values.
// The calibration data will not be cleared.
//*********************************************************************************************************************
void clear_data_screen()
{
  if (digitalRead(PIN_BUTTON_EXIT) == LOW)
  {
    bool is_wait = true;
    
    // Set memory buffer for text strings
    char msg_buffer[13];
    char char_buffer[8];
    
    u8g2.firstPage(); do {
      
      // Print "CLEAR DATA?"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[1])));
      u8g2.setCursor(28, 20);
      u8g2.print(msg_buffer);
      
      // Print "YES"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[11])));
      u8g2.setCursor(0, 40);
      u8g2.print(msg_buffer);
      
      // Print "="
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[10])));
      u8g2.setCursor(24, 40);
      u8g2.print(char_buffer);
      
      // Print "UP"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[9])));
      u8g2.setCursor(34, 40);
      u8g2.print(msg_buffer);
      
      // Print "NO"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[12])));
      u8g2.setCursor(74, 40);
      u8g2.print(msg_buffer);
      
      // Print "="
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[10])));
      u8g2.setCursor(91, 40);
      u8g2.print(char_buffer);
      
      // Print "DOWN"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[10])));
      u8g2.setCursor(101, 40);
      u8g2.print(msg_buffer);
      
    } while (u8g2.nextPage());
    
    
    while (is_wait)
    {
      switch (read_button())
      {
        // Button DOWN
        case 3:
        is_wait = false;
        break;
        
        // Button UP
        case 1:
        is_wait = false;
        
        // Clear EEPROM and, if necessary, set default parameters
        clear_data_eeprom();
        delay(2000);
        break;
      }
    }
  }
}
 
