
//*********************************************************************************************************************
// Drawing MODEL NAME screen display
//*********************************************************************************************************************
// This is the state machine, which will replace the do - while loop
void draw_model_name_screen()
{
  static uint8_t is_next_page = 0;
  
  // Call to first page, if required
  if (is_next_page == 0)
  {
    u8g2.firstPage();
    is_next_page = 1;
  }
  
  model_name_screen(); // Draw our screen
  
  // Call to next page
  if (u8g2.nextPage() == 0)
  {
    is_next_page = 0; // Ensure, that first page is called
  }
}

//------------------------------------------------------------------------
void model_name_screen()
{
  // Set memory buffer for text strings
  char menu_buffer[7];
  char char_buffer[9];
  
  // Print "MODEL NAME"
  strcpy_P(menu_buffer, (char*)pgm_read_word(&(menu_name[5])));
  u8g2.setCursor(0, 9);
  u8g2.print(menu_buffer);
  
  // Print number of which model in use
  u8g2.setCursor(90, 9);
  u8g2.print(modelActual + 1);
  
  u8g2.drawHLine(0, 10, 128); // Drawing horizontal line under header
  
  // Print model name "XXXXX" 5byte
  u8g2.setFont(u8g2_font_VCR_OSD_tr); // Height 15 pixels (dafont)
  
  
  for (int i = 0; i < 5; i++)
  {
    u8g2.setCursor(13 + (i * 23), 45);
    u8g2.print(modelName[i]);
    
    if (i == menuSubActual - 1)
    {
      if (modelNameSelection == i)
      {
        // Print "("
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[2])));
        u8g2.setCursor(1 + (i * 23), 45);
        u8g2.print(char_buffer);
        
        // Print ")"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[3])));
        u8g2.setCursor(25 + (i * 23), 45);
        u8g2.print(char_buffer);
      }
      else
      {
        // Print ">"
        strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[5])));
        u8g2.setCursor(1 + (i * 23), 45);
        u8g2.print(char_buffer);
      }
    }
  }
  
  u8g2.setFont(u8g2_font_7x13_tr); // Height 9 pixels (X11)
}
 
