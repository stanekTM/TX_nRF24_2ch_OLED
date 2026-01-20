
//*********************************************************************************************************************
// Read pots, apply calibration, EPA, EXPO, SUB TRIM, REVERSE
//*********************************************************************************************************************
void read_pots()
{
  for (int i = 0; i < CHANNELS; i++)
  {
    raw_pots = analogRead(i);
    
    int min_epa_val = map(epa[i],     EPA_MAX, 0,  900, MID_CONTROL_VAL); // epa[0], epa[1]
    int max_epa_val = map(epa[i + 2], EPA_MAX, 0, 2100, MID_CONTROL_VAL); // epa[2], epa[3]
    
    // Convert analog value to pots value
    if (raw_pots < mid_pots_calib[i] - DEAD_ZONE)
    {
      pots_value[i] = map(raw_pots, min_pots_calib[i], mid_pots_calib[i] - DEAD_ZONE, min_epa_val, MID_CONTROL_VAL);
      
      // Use of EXPO
      if (expo[i] > 0) pots_value[i] = calc_expo(MID_CONTROL_VAL, pots_value[i], min_epa_val, expo[i]);
    }
    else if (raw_pots > mid_pots_calib[i] + DEAD_ZONE)
    {
      pots_value[i] = map(raw_pots, mid_pots_calib[i] + DEAD_ZONE, max_pots_calib[i], MID_CONTROL_VAL, max_epa_val);
      
      // Use of EXPO
      if (expo[i] > 0) pots_value[i] = calc_expo(MID_CONTROL_VAL, pots_value[i], max_epa_val, expo[i]);
    }
    else
    {
      pots_value[i] = MID_CONTROL_VAL;
    }
    
    // Use SUB TRIM and limit to 1000us to 2000us
    pots_value[i] = constrain(pots_value[i] + subTrim[i], MIN_CONTROL_VAL, MAX_CONTROL_VAL);
    
    // Check REVERSE and applying REVERSE value if necessary
    if (bitRead(reverse, i) == 1) pots_value[i] = (MIN_CONTROL_VAL + MAX_CONTROL_VAL) - pots_value[i];
  }
}
 
