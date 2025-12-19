
//*********************************************************************************************************************
// Print calibration "MIN-MAX CALIBRATION" real time channels
//*********************************************************************************************************************
void calibration_screen()
{
  // Set memory buffer for text strings
  char msg_buffer[11];
  char word_buffer[13];
  char char_buffer[8];
  
  u8g2.firstPage(); do {
    
    read_pots(); // Macro again for stable pots value
    
    // Print "MIN-MAX"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[3])));
    u8g2.setCursor(0, 9);
    u8g2.print(msg_buffer);
    
    // Print "CALIBRATION"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[2])));
    u8g2.setCursor(52, 9);
    u8g2.print(msg_buffer);
    
    // Drawing horizontal line under header and vertical/middle line
    u8g2.drawHLine(0, 10, 128);
    u8g2.drawVLine(64, 12, 15);
    
    // Print "CH1" and value
    strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[0])));
    u8g2.setCursor(0, 22);
    u8g2.print(word_buffer);
    u8g2.setCursor(30, 22);
    u8g2.print(analogRead(0));
    
    // Print "CH2" and value
    strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[1])));
    u8g2.setCursor(71, 22);
    u8g2.print(word_buffer);
    u8g2.setCursor(101, 22);
    u8g2.print(analogRead(1));
    
    // Print "Move the pots"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[8])));
    u8g2.setCursor(20, 44);
    u8g2.print(msg_buffer);
    
    // Print "SAVE DATA"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[0])));
    u8g2.setCursor(0, 64);
    u8g2.print(msg_buffer);
    
    // Print "="
    strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[10])));
    u8g2.setCursor(66, 64);
    u8g2.print(char_buffer);
    
    // Print "UP"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[9])));
    u8g2.setCursor(76, 64);
    u8g2.print(msg_buffer);
    
  } while (u8g2.nextPage());
}

//*********************************************************************************************************************
// Print calibration "CENTER CALIBRATION" real time channels
//*********************************************************************************************************************
void calib_center_screen()
{
  // Set memory buffer for text strings
  char msg_buffer[11];
  char word_buffer[13];
  char char_buffer[8];
  
  u8g2.firstPage(); do {
    
    read_pots(); // Macro again for stable pots value
    
    // Print "CENTER"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[4])));
    u8g2.setCursor(0, 9);
    u8g2.print(msg_buffer);
    
    // Print "CALIBRATION"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[2])));
    u8g2.setCursor(52, 9);
    u8g2.print(msg_buffer);
    
    // Drawing horizontal line under header and vertical/middle line
    u8g2.drawHLine(0, 10, 128);
    u8g2.drawVLine(64, 12, 15);
    
    // Print "CH1" and value
    strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[0])));
    u8g2.setCursor(0, 22);
    u8g2.print(word_buffer);
    u8g2.setCursor(30, 22);
    u8g2.print(analogRead(0));
    
    // Print "CH2" and value
    strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[1])));
    u8g2.setCursor(71, 22);
    u8g2.print(word_buffer);
    u8g2.setCursor(101, 22);
    u8g2.print(analogRead(1));
    
    // Print "Don't"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[7])));
    u8g2.setCursor(0, 44);
    u8g2.print(msg_buffer);
    
    // Print "Move the pots"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[8])));
    u8g2.setCursor(38, 44);
    u8g2.print(msg_buffer);
    
    // Print "SAVE DATA"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[0])));
    u8g2.setCursor(0, 64);
    u8g2.print(msg_buffer);
    
    // Print "="
    strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[10])));
    u8g2.setCursor(66, 64);
    u8g2.print(char_buffer);
    
    // Print "UP"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[9])));
    u8g2.setCursor(76, 64);
    u8g2.print(msg_buffer);
    
  } while (u8g2.nextPage());
}

//*********************************************************************************************************************
// Print message "SAVE DATA CALIBRATION"
//*********************************************************************************************************************
void calib_save_data_screen()
{
  char msg_buffer[11]; // Set memory buffer for text strings
  
  u8g2.firstPage(); do {
    
    // Print "SAVE DATA"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[0])));
    u8g2.setCursor(33, 20);
    u8g2.print(msg_buffer);
    
    // Print "CALIBRATION"
    strcpy_P(msg_buffer, (char*)pgm_read_word(&(message[2])));
    u8g2.setCursor(25, 40);
    u8g2.print(msg_buffer);
    
  } while (u8g2.nextPage());
}
 
