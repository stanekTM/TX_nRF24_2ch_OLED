
//*********************************************************************************************************************
// EXPO equation
// Y = X * EXPO((X - EPA) / dv))
// Proper dv value : 300 ~ 700
//*********************************************************************************************************************
int calc_expo(unsigned short mid_value, unsigned short value, unsigned short max_value, unsigned short dv)
{
  if (value == mid_value)
  {
    return value;
  }
  
  if (dv <= 0)
  {
    return value;
  }
  
  dv = 9 - dv; // 1 ~ 9 -> 9 ~ 1 conversion
  
  dv = map(dv, 1, 9, 300, 700);
  
  if (value > mid_value)
  {
    value = (value - mid_value) * exp((((double)value - mid_value) - (max_value - mid_value)) / dv) + mid_value;
    
    return value;
  }
  else
  {
    unsigned short trim_val = 6;
    
    value = (MAX_CONTROL_VAL + trim_val) - value + (MIN_CONTROL_VAL + trim_val);
    max_value = (MAX_CONTROL_VAL + trim_val) - max_value + (MIN_CONTROL_VAL + trim_val);
    
    value = (value - mid_value) * exp((((double)value - mid_value) - (max_value - mid_value)) / dv) + mid_value;
    
    return (MAX_CONTROL_VAL + trim_val) - value + (MIN_CONTROL_VAL + trim_val);
  }
}
 
