
//*********************************************************************************************************************
// Drawing MENU screen display
//*********************************************************************************************************************
// This is the state machine, which will replace the do - while loop
void draw_menu_screen()
{
  static uint8_t is_next_page = 0;
  
  // Call to first page, if required
  if (is_next_page == 0)
  {
    u8g2.firstPage();
    is_next_page = 1;
  }
  
  // Draw our screen
  menu_screen();
  
  // Call to next page
  if (u8g2.nextPage() == 0)
  {
    is_next_page = 0; // Ensure, that first page is called
  }
}

//------------------------------------------------------------------------
void menu_screen()
{
  // Set memory buffer for text strings
  char menu_buffer[7];
  char char_buffer[9];
  
  read_pots(); // Macro again for stable pots value
  
  // Print MODEL NAME "MODEL"
  u8g2.setCursor(0, 9);
  u8g2.print(modelName);
  
  // Print number of which model in use
  u8g2.setCursor(40, 9);
  u8g2.print(modelActual + 1);
  
  
  // Print "1 or 2"
  u8g2.setCursor(107, 9);
  u8g2.print(menuPage + 1);
  
  // Print "/"
  strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[9])));
  u8g2.setCursor(114, 9);
  u8g2.print(char_buffer);
  
  // Total Menu count/menu count per page + 1
  u8g2.setCursor(122, 9);
  u8g2.print((MENU_COUNT - 1) / 5 + 1);
  
  // Drawing horizontal line under header
  u8g2.drawHLine(0, 10, 128);
  
  
  for (int i = 1; i < 6; i++)
  {
    if (i + (5 * menuPage) > MENU_COUNT)
    break;
    
    // Print main menu items "END POINT, MODEL SELECT, REVERSE, SAVE MODEL, SUB TRIM, MODEL NAME, EXPO"
    strcpy_P(menu_buffer, (char*)pgm_read_word(&(menu_name[i + (5 * menuPage) - 1])));
    
    if (i + (5 * menuPage) == menuSubActual)
    {
      // Print ">"
      strcpy_P(char_buffer, (char*)pgm_read_word(&(one_char[5])));
      u8g2.setCursor(0, 11 + (i * 10));
      u8g2.print(char_buffer);
      
      // Print main menu items
      u8g2.setCursor(10, 11 + (i * 10));
      u8g2.print(menu_buffer);
    }
    else
    {
      // Print main menu items
      u8g2.setCursor(23, 11 + (i * 10));
      u8g2.print(menu_buffer);
    }
  }
  
  menuActual = 0; // To move the cursor DOWN properly
}
 
