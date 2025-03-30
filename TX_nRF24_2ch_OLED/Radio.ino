
//*********************************************************************************************************************
// Setup radio comunication
//*********************************************************************************************************************
RF24 radio(PIN_CE, PIN_CSN); // Setup CE and CSN pins

void radio_setup()
{
  radio.begin();
  radio.setAutoAck(true);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.setRetries(5, 5);
  radio.setChannel(RADIO_CHANNEL);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN (-18dBm), RF24_PA_LOW (-12dBm), RF24_PA_HIGH (-6dbm), RF24_PA_MAX (0dBm)
  radio.stopListening();
  radio.openWritingPipe(address);
}

//*********************************************************************************************************************
// Send and receive data
//*********************************************************************************************************************
unsigned long rf_timeout = 0;

void send_and_receive_data()
{
  radio.write(&rc_packet, sizeof(rc_packet_size));
  
  if (radio.available())
  {
    radio.read(&telemetry_packet, sizeof(telemetry_packet_size));
    
    rf_timeout = millis();
  }
}
 
