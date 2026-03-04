
//*********************************************************************************************************************
// Reading the state of the SELECT, UP, DOWN and EXIT input buttons in a loop
//*********************************************************************************************************************
uint32_t button_time = 0; // The time variable must be global

uint8_t read_button()
{
  if (millis() - button_time > 200) // Button anti-bounce delay
  {
    if (digitalRead(PIN_BUTTON_SELECT) == LOW)
    {
      button_time = millis();
      return 2;
    }
    
    if (digitalRead(PIN_BUTTON_UP) == LOW)
    {
      button_time = millis();
      return 1;
    }
    
    if (digitalRead(PIN_BUTTON_DOWN) == LOW)
    {
      button_time = millis();
      return 3;
    }
    
    if (digitalRead(PIN_BUTTON_EXIT) == LOW)
    {
      screen = 0;
      menuSubActual = 1;
      menuActual = 0;
      menuPage = 0;
      
      modelNameSelection = 0xFF;
      epaSelection = 0xFF;
      subTrimSelection = 0xFF;
      expoSelection = 0xFF;
    }
  }
  
  return 0;
}
 
