
//*********************************************************************************************************************
// Read pots, apply calibration, EPA, EXPO, SUB TRIM, REVERSE
//*********************************************************************************************************************
void read_pots()
{
  for (int i = 0; i < CHANNELS; i++)
  {
    raw_pots = analogRead(i);
    
    // Range correction
    if (raw_pots < min_pots_calib[i]) raw_pots = min_pots_calib[i];
    if (raw_pots > max_pots_calib[i]) raw_pots = max_pots_calib[i];
    
    int mid_sub_trim = MID_CONTROL_VAL + subTrim[i];
    int min_epa_val = MID_CONTROL_VAL - (5 * epa[i]);     // Minimum EPA CH1 and CH2 values (1000us to 1500us)
    int max_epa_val = MID_CONTROL_VAL + (5 * epa[i + 2]); // Maximum EPA CH1 and CH2 values (1500us to 2000us)
    //Serial.println(min_epa_val);
    
    // Convert analog value to pots value
    if (raw_pots < (mid_pots_calib[i] - DEAD_ZONE))
    {
      pots_value[i] = map(raw_pots, min_pots_calib[i], mid_pots_calib[i] - DEAD_ZONE, min_epa_val/*1000*/, mid_sub_trim/*1500*/);
      
      // Use of EXPO
      if (expo[i] > 0)
      {
        pots_value[i] = calc_expo(mid_sub_trim, pots_value[i], min_epa_val, expo[i]);
      }
    }
    else if (raw_pots > (mid_pots_calib[i] + DEAD_ZONE))
    {
      pots_value[i] = map(raw_pots, mid_pots_calib[i] + DEAD_ZONE, max_pots_calib[i], mid_sub_trim/*1500*/, max_epa_val/*2000*/);
      
      // Use of EXPO
      if (expo[i] > 0)
      {
        pots_value[i] = calc_expo(mid_sub_trim, pots_value[i], max_epa_val, expo[i]);
      }
    }
    else
    {
      pots_value[i] = mid_sub_trim/*1500*/;
    }
    
    // Check REVERSE and applying REVERSE value if necessary
    if (bitRead(reverse, i) == 1)
    {
      pots_value[i] = (MIN_CONTROL_VAL + MAX_CONTROL_VAL) - pots_value[i];
    }
    
    // Range correction
    if (pots_value[i] < MIN_CONTROL_VAL) pots_value[i] = MIN_CONTROL_VAL;
    if (pots_value[i] > MAX_CONTROL_VAL) pots_value[i] = MAX_CONTROL_VAL;
  }
}
 
