
//*********************************************************************************************************************
// Hold button DOWN on power ON to initialize default memory data
// Will only write data settings to default (not erase calibration data)
// NOTE: SHOULD BE USED FOR THE FIRST TIME AFTER CALIBRATION !!!
//*********************************************************************************************************************
void erase_data_screen()
{
  if (digitalRead(PIN_BUTTON_EXIT) == LOW)
  {
    bool isWait = true;
    
    // Set memory buffer for text strings
    char msg_buffer[11];
    char char_buffer[8];
    
    u8g2.firstPage(); do {
      
      // Print "ERASE DATA?"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[1])));
      u8g2.setCursor(25, 20);
      u8g2.print(msg_buffer);
      
      // Print "Y"
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[0])));
      u8g2.setCursor(0, 40);
      u8g2.print(char_buffer);
      
      // Print "="
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[10])));
      u8g2.setCursor(10, 40);
      u8g2.print(char_buffer);
      
      // Print "DOWN"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[10])));
      u8g2.setCursor(20, 40);
      u8g2.print(msg_buffer);
      
      // Print "N"
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[1])));
      u8g2.setCursor(95, 40);
      u8g2.print(char_buffer);
      
      // Print "="
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[10])));
      u8g2.setCursor(105, 40);
      u8g2.print(char_buffer);
      
      // Print "UP"
      strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[9])));
      u8g2.setCursor(115, 40);
      u8g2.print(msg_buffer);
      
    } while (u8g2.nextPage());
    
    while (isWait)
    {
      switch (read_button())
      {
        // Button UP
        case 1:
        isWait = false;
        break;
        
        // Button DOWN
        case 3:
        isWait = false;
        
        // Recall "Reset to default" macro
        erase_data_eeprom();
        
        /*
        u8g2.firstPage(); do {
          
          // Print "ERASE DATA"
          strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[1])));
          u8g2.setCursor(25, 20);
          u8g2.print(msg_buffer);
          
        } while (u8g2.nextPage());
        
        delay(2000);
        */

        break;
      }
    }
  }
}
 
