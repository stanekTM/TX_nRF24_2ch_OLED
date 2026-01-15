
//*********************************************************************************************************************
// TX battery voltage monitoring
//*********************************************************************************************************************
float tx_batt_volt = 0;
bool tx_low_batt = 0;

void TX_batt_monitoring()
{
  tx_batt_volt = analogRead(PIN_BATTERY) * (TX_BATTERY_VOLTAGE / 1023);
  
  tx_low_batt = tx_batt_volt <= TX_MONITORED_VOLTAGE;
  
  //Serial.println(tx_batt_volt);
}

//*********************************************************************************************************************
// RX battery voltage monitoring
//*********************************************************************************************************************
float rx_batt_volt = 0;
bool rx_low_batt = 0;
bool previous_state_batt;

void RX_batt_monitoring()
{
  rx_batt_volt = telemetry_packet.batt_A1 * (RX_BATTERY_VOLTAGE / 255);
  
  rx_low_batt = rx_batt_volt <= RX_MONITORED_VOLTAGE;
  
  // Battery alarm lock
  if (rx_low_batt)
  {
    previous_state_batt = 1;
  }
  rx_low_batt = previous_state_batt;
  
  //Serial.println(rx_batt_volt);
}
 
