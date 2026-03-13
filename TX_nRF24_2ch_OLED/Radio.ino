
//*********************************************************************************************************************
// Radio setup
//*********************************************************************************************************************
RF24 radio(PIN_CE, PIN_CSN); // nRF24 class driver

void radio_setup()
{
  radio.begin();
  radio.setAutoAck(1);
  radio.enableAckPayload();
  radio.enableDynamicPayloads();
  radio.setRetries(2, 0);
  radio.setChannel(RF_CHANNEL);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_MIN); // RF24_PA_MIN (-18dBm), RF24_PA_LOW (-12dBm), RF24_PA_HIGH (-6dbm), RF24_PA_MAX (0dBm)
  radio.stopListening();
  radio.openWritingPipe(RF_address);
}

//*********************************************************************************************************************
// Send and receive data
//*********************************************************************************************************************
uint32_t rf_timeout = 0;

void send_and_receive_data()
{
  if (radio.write(&tx_packet, sizeof(tx_packet)))
  {
    if (radio.available())
    {
      radio.read(&rx_ack_packet, sizeof(rx_ack_packet));
      
      rf_timeout = millis();
    }
  }
}
 
