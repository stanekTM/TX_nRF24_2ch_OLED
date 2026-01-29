
//*********************************************************************************************************************
// Read pots, apply calibration, EPA, EXPO, SUB TRIM, REVERSE
//*********************************************************************************************************************
void read_pots()
{
  for (int i = 0; i < RC_CHANNELS; i++)
  {
    raw_pots = analogRead(i);
    
    int mid_epa_val = MID_CONTROL_VAL + subTrim[i];
    
    // epa[0], epa[1] 1000us to 1500us
    int min_epa_val = map((1500 - (epa[i] * 5)), 1000, 1500, 1000, 1500 + subTrim[i]);
    
    // epa[2], epa[3] 2000us to 1500us
    int max_epa_val = map((1500 + (epa[i + 2] * 5)), 2000, 1500, 2000, 1500 + subTrim[i]);
    
    // Convert analog value to pots value
    if (raw_pots < mid_pots_calib[i] - DEAD_ZONE)
    {
      pots_value[i] = map(raw_pots, min_pots_calib[i], mid_pots_calib[i] - DEAD_ZONE, min_epa_val, mid_epa_val);
      
      // Use of EXPO
      if (expo[i] > 0) pots_value[i] = calc_expo(mid_epa_val, pots_value[i], min_epa_val, expo[i]);
    }
    else if (raw_pots > mid_pots_calib[i] + DEAD_ZONE)
    {
      pots_value[i] = map(raw_pots, mid_pots_calib[i] + DEAD_ZONE, max_pots_calib[i], mid_epa_val, max_epa_val);
      
      // Use of EXPO
      if (expo[i] > 0) pots_value[i] = calc_expo(mid_epa_val, pots_value[i], max_epa_val, expo[i]);
    }
    else
    {
      pots_value[i] = mid_epa_val;
    }
    
    // Check REVERSE and applying REVERSE value if necessary
    if (bitRead(reverse, i) == 1) pots_value[i] = (MIN_CONTROL_VAL + MAX_CONTROL_VAL) - pots_value[i];
  }
}
 
