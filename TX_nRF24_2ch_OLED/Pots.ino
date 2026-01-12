
//*********************************************************************************************************************
// Read pots, apply calibration, EPA, EXPO, SUB TRIM, REVERSE
//*********************************************************************************************************************
void read_pots()
{
  for (int ch = 0; ch < CHANNELS; ch++)
  {
    raw_pots = analogRead(ch);
    
    // Convert analog value to pots value
    if (raw_pots < (mid_pots_calib[ch] - DEAD_ZONE))
    {
      pots_value[ch] = map(raw_pots, min_pots_calib[ch], mid_pots_calib[ch] - DEAD_ZONE, MID_CONTROL_VAL - (500 * epa[ch] / EPA_MAX), MID_CONTROL_VAL);
      
      // Use of EXPO
      if (expo[ch] > 0)
      {
        pots_value[ch] = calc_expo(MID_CONTROL_VAL, pots_value[ch], MIN_CONTROL_VAL, expo[ch]);
      }
    }
    else if (raw_pots > (mid_pots_calib[ch] + DEAD_ZONE))
    {
      pots_value[ch] = map(raw_pots, mid_pots_calib[ch] + DEAD_ZONE, max_pots_calib[ch], MID_CONTROL_VAL, MID_CONTROL_VAL + (500 * epa[ch + 2] / EPA_MAX));
      
      // Use of EXPO
      if (expo[ch] > 0)
      {
        pots_value[ch] = calc_expo(MID_CONTROL_VAL, pots_value[ch], MAX_CONTROL_VAL, expo[ch]);
      }
    }
    else
    {
      pots_value[ch] = MID_CONTROL_VAL + subTrim[ch];
    }
    
    // Check REVERSE and applying REVERSE value if necessary
    if (bitRead(reverse, ch) == 1)
    {
      pots_value[ch] = (MIN_CONTROL_VAL + MAX_CONTROL_VAL) - pots_value[ch];
    }

  }
}
 
