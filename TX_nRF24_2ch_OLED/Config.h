
//*********************************************************************************************************************
// Version
//*********************************************************************************************************************
const char fw_version[] = "TX stanekTM v1.5";

//*********************************************************************************************************************
// Battery voltage settings TX/RX, minimum battery voltage for alarm
//*********************************************************************************************************************
#define TX_BATTERY_VOLTAGE    4.2  // Maximum battery voltage
#define TX_MONITORED_VOLTAGE  3.35 // Minimum battery voltage for alarm

#define RX_BATTERY_VOLTAGE    4.2  // Maximum battery voltage
#define RX_MONITORED_VOLTAGE  3.35 // Minimum battery voltage for alarm

//*********************************************************************************************************************
// pins connecting
//*********************************************************************************************************************
// Joystick 1              A0
// Joystick 2              A1

// Pin battery             A7

// Pins button
#define PIN_BUTTON_UP      2 // For Up/Prev functions
#define PIN_BUTTON_DOWN    3 // For Down/Next functions
#define PIN_BUTTON_SELECT  4 // For Menu/Select functions
#define PIN_BUTTON_EXIT    5 // For Exit

// Pins for nRF24L01+
#define PIN_CE             9
#define PIN_CSN            10
//          MOSI           11 Hardware SPI
//          MISO           12 Hardware SPI
//          SCK            13 Hardware SPI

// Pins LCD display
//          SDA            A4 Hardware I2C
//          SCL            A5 Hardware I2C

//*********************************************************************************************************************
// Config radio comunication
//*********************************************************************************************************************
// RF communication channel settings (0-125, 2.4Ghz + 76 = 2.476Ghz)
#define RADIO_CHANNEL  76

// Setting a unique address (5 bytes number or character)
const byte address[] = "jirka";

// This structure defines the data sent (max 32 bytes)
struct rc_packet_size
{
  unsigned int ch1;
  unsigned int ch2;
  //unsigned int ch3;
  //unsigned int ch4;
  //unsigned int ch5;
  //unsigned int ch6;
  //unsigned int ch7;
  //unsigned int ch8;
  //unsigned int ch9;
  //unsigned int ch10;
  //unsigned int ch11;
  //unsigned int ch12;
};
rc_packet_size rc_packet;

// This struct defines data, which are embedded inside the ACK payload
struct telemetry_packet_size
{
  byte rssi;
  byte batt_A1 = 255;
  byte batt_A2; // Not used yet
};
telemetry_packet_size telemetry_packet;

//*********************************************************************************************************************
// Configuration of the global TX parameter
//*********************************************************************************************************************
#define DEAD_ZONE                 10   // Dead zone bar center value of poor quality joysticks
#define EPA_MAX                   100  // Maximum EPA value
#define SUB_TRIM_MAX              125  // Maximum SUB TRIM value
#define CHANNELS                  2    // Number of channels

#define MENU_COUNT                7    // Total menu count
#define MODELS                    10   // Total memory models 30
#define NUM_BYTES_PER_MODEL       25   // Maximum bytes for data storage per model 32
#define ACTUAL_MODEL_EEPROM_ADDR  1023

//*********************************************************************************************************************
// Control range value
//*********************************************************************************************************************
#define MIN_CONTROL_VAL  1000
#define MID_CONTROL_VAL  1500
#define MAX_CONTROL_VAL  2000

//*********************************************************************************************************************
// Parameters of potentiometers
//*********************************************************************************************************************
unsigned short int pots[CHANNELS];
unsigned short int pots_value[CHANNELS];
unsigned short int pot_calib_min[] = {0, 0};
unsigned short int pot_calib_mid[] = {512, 512};
unsigned short int pot_calib_max[] = {1023, 1023};

//*********************************************************************************************************************
// PPM setting parameters
//*********************************************************************************************************************
unsigned char epa[4];                       // EPA value array
unsigned char epaSelection = 0xFF;          // Default value for EPA selection

short subTrim[2];                           // SUB TRIM channel array
unsigned short int subTrimSelection = 0xFF; // Default value for SUB TRIM

unsigned char expo[2];                      // EXPO value array
unsigned char expoSelection = 0xFF;         // Default value for EXPO selection

unsigned char reverse;                      // Reading bit status

//*********************************************************************************************************************
// MODEL NAME
//*********************************************************************************************************************
char modelName[] = "MODEL";              // MODEL NAME 5 byte
unsigned char modelNameSelection = 0xFF; // Default value for MODEL NAME selection

//*********************************************************************************************************************
// Checking the status of the calibration switch
//*********************************************************************************************************************
bool calibStatus = 1; // Checking status to enter in calibration procedure

//*********************************************************************************************************************
// Menu management variables
//*********************************************************************************************************************
unsigned char menuActual    = 0;
unsigned char menuSubActual = 1;
unsigned char modelActual   = 0; // Added for model menu management
unsigned char menuSubModel  = 0; // Added for model menu management
unsigned char screen        = 0;
unsigned char menuPage      = 0; // For menu page
unsigned char modelPage     = 0; // For model page

//*********************************************************************************************************************
// Config LCD display
//*********************************************************************************************************************
U8G2_SSD1306_128X64_NONAME_1_HW_I2C
u8g2(U8G2_R0, U8X8_PIN_NONE);       // https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#constructor-name

//*********************************************************************************************************************
// Using PROGMEM for characters and text strings to save RAM memory
// Array text strings for drawing menu "menu_buffer[7]"
//*********************************************************************************************************************
const char menu_0[] PROGMEM = "END POINT";
const char menu_1[] PROGMEM = "MODEL SELECT";
const char menu_2[] PROGMEM = "REVERSE";
const char menu_3[] PROGMEM = "SAVE MODEL";
const char menu_4[] PROGMEM = "SUB TRIM";
const char menu_5[] PROGMEM = "MODEL NAME";
const char menu_6[] PROGMEM = "EXPO";

const char* const menu_name[] PROGMEM = {
  menu_0,
  menu_1,
  menu_2,
  menu_3,
  menu_4,
  menu_5,
  menu_6
};

//*********************************************************************************************************************
// Array text strings (short) for channel/pots names, status, model for all screens "word_buffer[13]"
//*********************************************************************************************************************
const char word_0[] PROGMEM = "CH1";
const char word_1[] PROGMEM = "CH2";
const char word_2[] PROGMEM = "TX";
const char word_3[] PROGMEM = "RX";
const char word_4[] PROGMEM = "RSSI";
const char word_5[] PROGMEM = "free";
const char word_6[] PROGMEM = "us";
const char word_7[] PROGMEM = "free";
const char word_8[] PROGMEM = "NOR";
const char word_9[] PROGMEM = "REV";

const char* const word_name[] PROGMEM = {
  word_0,
  word_1,
  word_2,
  word_3,
  word_4,
  word_5,
  word_6,
  word_7,
  word_8,
  word_9
};

//*********************************************************************************************************************
// Array for single characters "char_buffer[9]"
//*********************************************************************************************************************
const char char_0[] PROGMEM = "Y";
const char char_1[] PROGMEM = "N";
const char char_2[] PROGMEM = "(";
const char char_3[] PROGMEM = ")";
const char char_4[] PROGMEM = "<";
const char char_5[] PROGMEM = ">";
const char char_6[] PROGMEM = "L";
const char char_7[] PROGMEM = "R";
const char char_8[] PROGMEM = "%";
const char char_9[] PROGMEM = "/";
const char char_10[] PROGMEM = "=";
const char char_11[] PROGMEM = "V";

const char* const one_char[] PROGMEM = {
  char_0,
  char_1,
  char_2,
  char_3,
  char_4,
  char_5,
  char_6,
  char_7,
  char_8,
  char_9,
  char_10,
  char_11
};

//*********************************************************************************************************************
// Array text strings for screen messages "msg_buffer[11]"
//*********************************************************************************************************************
const char message_0[] PROGMEM = "SAVE DATA";
const char message_1[] PROGMEM = "ERASE DATA?";
const char message_2[] PROGMEM = "CALIBRATION";
const char message_3[] PROGMEM = "MIN-MAX";
const char message_4[] PROGMEM = "CENTER";
const char message_5[] PROGMEM = "off!";
const char message_6[] PROGMEM = "low!";
const char message_7[] PROGMEM = "Don't";
const char message_8[] PROGMEM = "Move the pots";
const char message_9[] PROGMEM = "UP";
const char message_10[] PROGMEM = "DOWN";

const char* const message[] PROGMEM = {
  message_0,
  message_1,
  message_2,
  message_3,
  message_4,
  message_5,
  message_6,
  message_7,
  message_8,
  message_9,
  message_10
};
 
