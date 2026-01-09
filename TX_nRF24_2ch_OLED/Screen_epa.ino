
//*********************************************************************************************************************
// Print screen EPA with real-time channels
//*********************************************************************************************************************
// This is the state machine, which will replace the do - while loop
void draw_epa_screen()
{
  static uint8_t is_next_page = 0;
  
  // Call to first page, if required
  if (is_next_page == 0)
  {
    u8g2.firstPage();
    is_next_page = 1;
  }
  
  epa_screen(); // Draw our screen
  
  // Call to next page
  if (u8g2.nextPage() == 0)
  {
    is_next_page = 0; // Ensure, that first page is called
  }
}

//------------------------------------------------------------------------
void epa_screen()
{
  // Set memory buffer for text strings
  char menu_buffer[7];
  char word_buffer[13];
  char char_buffer[9];
  
  read_pots(); // Reused for stable pots values
  
  // Print "EPA"
  strcpy_P(menu_buffer, (char*)pgm_read_word(&(menu_name[0])));
  u8g2.setCursor(0, 9);
  u8g2.print(menu_buffer);
  
  /*
  // Print "%"
  strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[8])));
  u8g2.setCursor(122, 9);
  u8g2.print(char_buffer);
  */
  
  u8g2.drawHLine(0, 10, 128); // Drawing horizontal line under header
  
  
  for (int i = 0; i < 2; i++)
  {
    // Print channel items name "CH1 and CH2"
    strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[i])));
    u8g2.setCursor(44, 21 + (i * 26));
    u8g2.print(word_buffer);
    
    // Check REVERSE and applying REVERSE value if necessary
    if (bitRead(reverse, i) == 1)
    {
      // Print "REV"
      strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[9])));
      u8g2.setCursor(72, 21 + (i * 26));
      u8g2.print(word_buffer);
      
      // Print "R"
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[7])));
      u8g2.setCursor(0, 21 + (i * 26));
      u8g2.print(char_buffer);
      
      // Print "L"
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[6])));
      u8g2.setCursor(122, 21 + (i * 26));
      u8g2.print(char_buffer);
    }
    else
    {
      // Print "L"
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[6])));
      u8g2.setCursor(0, 21 + (i * 26));
      u8g2.print(char_buffer);
      
      // Print "R"
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[7])));
      u8g2.setCursor(122, 21 + (i * 26));
      u8g2.print(char_buffer);
    }
    
    // Print PPM value
    u8g2.setCursor(44, 31 + (i * 26));
    u8g2.print(pots_value[i]);
    
    // Print "us"
    strcpy_P(word_buffer, (char*)pgm_read_word(&(word_name[6])));
    u8g2.setCursor(72, 31 + (i * 26));
    u8g2.print(word_buffer);
    
    
    // Left section start
    // EPA value
    u8g2.setCursor(6, 31 + (i * 26));
    u8g2.print(epa[i]);
    
    if (i == menuSubActual - 1)
    {
      if (epaSelection == i)
      {
        // Print "("
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[2])));
        u8g2.setCursor(-2, 31 + (i * 26));
        u8g2.print(char_buffer);
        
        // Print ")"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[3])));
        u8g2.setCursor(26, 31 + (i * 26));
        u8g2.print(char_buffer);
      }
      else
      {
        // Print "<"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[4])));
        u8g2.setCursor(29, 31 + (i * 26));
        u8g2.print(char_buffer);
      }
    }
    // Left section end
    
    
    // Right section start
    // EPA value
    u8g2.setCursor(103, 31 + (i * 26));
    u8g2.print(epa[i + 2]);
    
    if (i + 2 == menuSubActual - 1)
    {
      if (epaSelection == i + 2)
      {
        // Print "("
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[2])));
        u8g2.setCursor(95, 31 + (i * 26));
        u8g2.print(char_buffer);
        
        // Print ")"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[3])));
        u8g2.setCursor(123, 31 + (i * 26));
        u8g2.print(char_buffer);
      }
      else
      {
        // Print ">"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[5])));
        u8g2.setCursor(93, 31 + (i * 26));
        u8g2.print(char_buffer);
      }
    }
    // Right section end
  }
}
 
