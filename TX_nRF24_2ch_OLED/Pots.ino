
//*********************************************************************************************************************
// Read pots, apply calibration, EPA, EXPO, SUB TRIM, REVERSE
//*********************************************************************************************************************
void read_pots()
{
  for (int ch = 0; ch < CHANNELS; ch++)
  {
    raw_pots = analogRead(ch);
    
    int mid_sub_trim = MID_CONTROL_VAL + subTrim[ch];
    int min_epa_val = MID_CONTROL_VAL - (5 * epa[ch]);     // Minimum EPA CH1 and CH2 values (1000us to 1500us)
    int max_epa_val = MID_CONTROL_VAL + (5 * epa[ch + 2]); // Maximum EPA CH1 and CH2 values (1500us to 2000us)
    //Serial.println(min_epa_val);
    
    // Convert analog value to pots value
    if (raw_pots < (mid_pots_calib[ch] - DEAD_ZONE))
    {
      pots_value[ch] = map(raw_pots, min_pots_calib[ch], mid_pots_calib[ch] - DEAD_ZONE, min_epa_val/*1000*/, mid_sub_trim);
      
      // Use of EXPO
      if (expo[ch] > 0)
      {
        pots_value[ch] = calc_expo(mid_sub_trim, pots_value[ch], MIN_CONTROL_VAL, expo[ch]);
      }
    }
    else if (raw_pots > (mid_pots_calib[ch] + DEAD_ZONE))
    {
      pots_value[ch] = map(raw_pots, mid_pots_calib[ch] + DEAD_ZONE, max_pots_calib[ch], mid_sub_trim, max_epa_val/*2000*/);
      
      // Use of EXPO
      if (expo[ch] > 0)
      {
        pots_value[ch] = calc_expo(mid_sub_trim, pots_value[ch], MAX_CONTROL_VAL, expo[ch]);
      }
    }
    else
    {
      pots_value[ch] = mid_sub_trim;
    }
    
    // Check REVERSE and applying REVERSE value if necessary
    if (bitRead(reverse, ch) == 1)
    {
      pots_value[ch] = (MIN_CONTROL_VAL + MAX_CONTROL_VAL) - pots_value[ch];
    }
  }
}
 
