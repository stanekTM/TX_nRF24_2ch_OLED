
#include <Arduino.h>

//*********************************************************************************************************************
// Version
//*********************************************************************************************************************
const char fw_version[] = "TX stanekTM v1.8";

//*********************************************************************************************************************
// Maximum nominal battery voltage TX/RX and minimum battery voltage for alarm
//*********************************************************************************************************************
#define TX_BATTERY_VOLTAGE    4.2  // Maximum nominal battery voltage
#define TX_MONITORED_VOLTAGE  3.45 // Minimum battery voltage for alarm

#define RX_BATTERY_VOLTAGE    4.2  // Maximum nominal battery voltage
#define RX_MONITORED_VOLTAGE  3.45 // Minimum battery voltage for alarm

float tx_batt_volt = 0;
bool tx_low_batt = 0;

float rx_batt_volt = 0;
bool rx_low_batt = 0;
bool previous_state_batt = 0;

//*********************************************************************************************************************
// Global TX control range config
//*********************************************************************************************************************
#define DEAD_ZONE        10   // Dead zone bar center value of poor quality joysticks
#define EPA_MAX          100  // Maximum EPA value
#define SUB_TRIM_MAX     100  // Maximum SUB TRIM value
#define RC_CHANNELS      2    // Number of channels

// Control range value
#define MIN_CONTROL_VAL  1000
#define MID_CONTROL_VAL  1500
#define MAX_CONTROL_VAL  2000

//*********************************************************************************************************************
// Config radio comunication
//*********************************************************************************************************************
// RF communication channel setting (0-125, 2.4Ghz + 76 = 2.476Ghz)
#define RF_CHANNEL  76

// Setting a unique address (5 bytes number or character)
const byte address[] = "jirka";

// Sent data array (max 32 bytes)
unsigned int rc_packet[RC_CHANNELS] = {1500};
byte rc_packet_size = RC_CHANNELS * 2; // For one control channel with a value of 1000 to 2000 we need 2 bytes(packets)

// Structure of received ACK data
struct telemetry_packet_size
{
  byte rssi;
  byte batt_A1 = 255;
  byte batt_A2; // Not used yet
};
telemetry_packet_size telemetry_packet;

//*********************************************************************************************************************
// Analog reading parameters for calibration
//*********************************************************************************************************************
unsigned int raw_pots;
unsigned int pots_value[RC_CHANNELS] = {1500};
unsigned int min_pots_calib[RC_CHANNELS] = {0};
unsigned int mid_pots_calib[RC_CHANNELS] = {512};
unsigned int max_pots_calib[RC_CHANNELS] = {1023};

//*********************************************************************************************************************
// Checking the status to start the calibration process
//*********************************************************************************************************************
bool calibStatus = 1;

//*********************************************************************************************************************
// Setting control output values
//*********************************************************************************************************************
short epa[4];                          // EPA value array
unsigned char epaSelection = 0xFF;     // Default value for EPA selection

short subTrim[2];                      // SUB TRIM channel array
unsigned char subTrimSelection = 0xFF; // Default value for SUB TRIM

short expo[2];                         // EXPO value array
unsigned char expoSelection = 0xFF;    // Default value for EXPO selection

unsigned char reverse;                 // Reading bit status

//*********************************************************************************************************************
// Global menu and memory config
//*********************************************************************************************************************
#define MENU_COUNT                7    // Total menu count
#define MODELS                    10   // Total memory models
#define NUM_BYTES_PER_MODEL       25   // Maximum bytes for data storage per model
#define ACTUAL_MODEL_EEPROM_ADDR  1023

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
// OLED SSD1306 I2C config
//*********************************************************************************************************************
U8G2_SSD1306_128X64_NONAME_1_HW_I2C
u8g2(U8G2_R0, U8X8_PIN_NONE);       // https://github.com/olikraus/u8g2/wiki/u8g2setupcpp#constructor-name

//*********************************************************************************************************************
// MODEL NAME
//*********************************************************************************************************************
char modelName[] = "MODEL";              // Default MODEL NAME 5byte
unsigned char modelNameSelection = 0xFF; // Default value for MODEL NAME selection

//*********************************************************************************************************************
// Using PROGMEM for characters and text strings to save RAM memory
//*********************************************************************************************************************
// Array text strings for menu screen "menu_buffer[7]"
//*********************************************************************************************************************
const char menu_0[] PROGMEM = "EPA";
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
// Array text strings (short) for all screens "word_buffer[10]"
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
// Array for single characters "char_buffer[12]"
//*********************************************************************************************************************
const char char_0[] PROGMEM = "free";
const char char_1[] PROGMEM = "free";
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
// Array text strings for screen messages "msg_buffer[13]"
//*********************************************************************************************************************
const char message_0[] PROGMEM = "SAVE DATA";
const char message_1[] PROGMEM = "CLEAR DATA?";
const char message_2[] PROGMEM = "CALIBRATION";
const char message_3[] PROGMEM = "MIN-MAX";
const char message_4[] PROGMEM = "CENTER";
const char message_5[] PROGMEM = "off!";
const char message_6[] PROGMEM = "low!";
const char message_7[] PROGMEM = "Don't";
const char message_8[] PROGMEM = "Move the pots";
const char message_9[] PROGMEM = "UP";
const char message_10[] PROGMEM = "DOWN";
const char message_11[] PROGMEM = "YES";
const char message_12[] PROGMEM = "NO";

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
  message_10,
  message_11,
  message_12
};

//*********************************************************************************************************************
// ATmega328P/PB pins overview
//*********************************************************************************************************************
// ATmega328P/PB pins overview
// PD0 - D0   PWM  328PB
// PD1 - D1   PWM  328PB
// PD2 - D2   PWM  328PB
// PD3 - D3   PWM
// PD4 - D4
// PD5 - D5   PWM
// PD6 - D6   PWM
// PD7 - D7
// PB0 - D8
// PB1 - D9   PWM
// PB2 - D10  PWM
// PB3 - D11  PWM  MOSI
// PB4 - D12       MISO
// PB5 - D13       SCK
// PC0 - D14 / A0
// PC1 - D15 / A1
// PC2 - D16 / A2
// PC3 - D17 / A3
// PC4 - D18 / A4   SDA
// PC5 - D19 / A5   SCL
// PB6 - D20        XTAL1
// PB7 - D21        XTAL2
// PC6 - D22        RESET
// PE0 - D23        328PB
// PE1 - D24        328PB
// PE2 - D25 / A6   328PB
// PE3 - D26 / A7   328PB
// ADC6   -    A6
// ADC7   -    A7

//*********************************************************************************************************************
// Connection pins
//*********************************************************************************************************************
// Analog input pin array for pots (possible combination, max 2)
const byte pins_pots[] = {A0, A1};

// Input battery
#define PIN_BATTERY        A7

// Pins for buttons
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

// Pins for LCD display
//          SDA            A4 Hardware I2C
//          SCL            A5 Hardware I2C
 
