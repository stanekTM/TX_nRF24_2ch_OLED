
//*********************************************************************************************************************
// Print screen EXPO
//*********************************************************************************************************************
// This is the state machine, which will replace the do - while loop
void draw_expo_screen()
{
  static uint8_t is_next_page = 0;
  
  // Call to first page, if required
  if (is_next_page == 0)
  {
    u8g2.firstPage();
    is_next_page = 1;
  }
  
  expo_screen(); // Draw our screen
  
  // Call to next page
  if (u8g2.nextPage() == 0)
  {
    is_next_page = 0; // Ensure, that first page is called
  }
}

//------------------------------------------------------------------------
void expo_screen()
{
  // Set memory buffer for text strings
  char menu_buffer[7];
  char word_buffer[13];
  char char_buffer[9];
  
  read_pots(); // Reused for stable pots values
  
  // Print "EXPO"
  strcpy_P(menu_buffer, (char*)pgm_read_word(&(menu_name[6])));
  u8g2.setCursor(0, 9);
  u8g2.print(menu_buffer);
  
  u8g2.drawHLine(0, 10, 128); // Drawing horizontal line under header
  
  
  // Drawing only first 2 channels
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    // Print channel items name "CH1, CH2"
    strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[i])));
    u8g2.setCursor(10, 21 + (i * 10));
    u8g2.print(word_buffer);
    
    // Print EXPO value
    u8g2.setCursor(43, 21 + (i * 10));
    u8g2.print(expo[i]);
    
    
    if (i == menuSubActual - 1)
    {
      if (expoSelection == i)
      {
        // Print ">"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[5])));
        u8g2.setCursor(0, 21 + (i * 10));
        u8g2.print(char_buffer);
        
        // Print "("
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[2])));
        u8g2.setCursor(35, 21 + (i * 10));
        u8g2.print(char_buffer);
        
        // Print ")"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[3])));
        u8g2.setCursor(50, 21 + (i * 10));
        u8g2.print(char_buffer);
      }
      else
      {
        // Print ">"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[5])));
        u8g2.setCursor(0, 21 + (i * 10));
        u8g2.print(char_buffer);
      }
      
      
      // Draw EXPO Graph
      u8g2.drawFrame(77, 13, 51, 51);
      
      u8g2.drawHLine(78, 38, 49);
      //u8g2.drawHLine(0, 62, 128); // Auxiliary line
      
      u8g2.drawVLine(102, 14, 49);
      //u8g2.drawVLine(126, 0, 64); // Auxiliary line
      
      u8g2.drawLine(77, 63, 127, 13); // Diagonal line
      
      
      if (expo[i] > 0)
      { 
        // Bottom
        for (int j = 77; j <= 102; j++)
        {
          u8g2.drawPixel(j, map(calc_expo(MID_CONTROL_VAL,
          map(j, 77, 102, MIN_CONTROL_VAL, MID_CONTROL_VAL), MIN_CONTROL_VAL, expo[i]), MIN_CONTROL_VAL, MID_CONTROL_VAL, 63, 38));
        }
        
        // Top
        for (int j = 102; j <= 127; j++)
        {
          u8g2.drawPixel(j, map(calc_expo(MID_CONTROL_VAL,
          map(j, 102, 127, MID_CONTROL_VAL, MAX_CONTROL_VAL), MAX_CONTROL_VAL, expo[i]), MID_CONTROL_VAL, MAX_CONTROL_VAL, 38, 13));
        }
      }
    }
  }
}
 
