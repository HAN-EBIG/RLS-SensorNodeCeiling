#ifndef config_h
#define config_h

//#define UNIT_TEST

/*********************************
// * SensorNodeCeiling
// ** sensorpins:
*/
#define SENSOR_1 A0 // LDR
#define SENSOR_2 A1 // LDR
//#define SENSOR_3 2 // PIR SENSOR_MOTION
//#define SENSOR_4 4 // DS18B20
//#define SENSOR_5 5 // DHT22

// ** child-id's :
#define LDR_1_ID 20
#define LDR_2_ID 21
//#define PIR_1_ID 103
#define DS18_1_ID 1
#define DHT_1_ID 35

/**********************************
 * Sketch configuration
 */
#define SKETCH_NAME "Ceiling Node D1.04 "
#define SKETCH_VERSION "1.9"
#define SLEEP_TIME_IN_SECONDS 1

/**********************************
 * MySensors configuration
 */
#define MY_BAUD_RATE 115200
//#define MY_DEBUG
//#define MY_NODE_ID 12 /*  [V]  */
#define MY_NODE_ID 22 /*  []  */
//#define MY_NODE_ID 32 /*  []  */
//#define MY_NODE_ID 42 /*  []  */
//#define MY_NODE_ID 52 /*  []  */

#define MY_RADIO_NRF24
//#define MY_RF24_ENABLE_ENCRYPTION
//#define MY_RF24_CHANNEL 76

/***********************************
 * NodeManager configuration
 */

// if enabled, enable debug messages on serial port
#define DEBUG 0

// if enabled, will load the sleep manager library. Sleep mode and sleep interval have to be configured to make the board sleeping/waiting
#define SLEEP_MANAGER 1

// if enabled, enable the capability to power on sensors with the arduino's pins to save battery while sleeping
#define POWER_MANAGER 1

// if enabled, will load the battery manager library to allow the battery level to be reported automatically or on demand
#define BATTERY_MANAGER 0

// if enabled, allow modifying the configuration remotely by interacting with the configuration child id
#define REMOTE_CONFIGURATION 0

// if enabled, persist the remote configuration settings on EEPROM
#define PERSIST 0

// if enabled, send a SLEEPING and AWAKE service messages just before entering and just after leaving a sleep cycle and STARTED when starting/rebooting
#define SERVICE_MESSAGES 0

// if enabled, a battery sensor will be created at BATTERY_CHILD_ID and will report vcc voltage together with the battery level percentage
#define BATTERY_SENSOR 0

// Enable this module to use one of the following sensors: SENSOR_ANALOG_INPUT, SENSOR_LDR, SENSOR_THERMISTOR, SENSOR_MQ, SENSOR_ML8511
#define MODULE_ANALOG_INPUT 1
// Enable this module to use one of the following sensors: SENSOR_DIGITAL_INPUT
#define MODULE_DIGITAL_INPUT 0
// Enable this module to use one of the following sensors: SENSOR_DIGITAL_OUTPUT, SENSOR_RELAY, SENSOR_LATCHING_RELAY
#define MODULE_DIGITAL_OUTPUT 0
// Enable this module to use one of the following sensors: SENSOR_DHT11, SENSOR_DHT22
#define MODULE_DHT 1
// Enable this module to use one of the following sensors: SENSOR_SHT21
#define MODULE_SHT21 0
// Enable this module to use one of the following sensors: SENSOR_SWITCH, SENSOR_DOOR, SENSOR_MOTION
#define MODULE_SWITCH 0
// Enable this module to use one of the following sensors: SENSOR_DS18B20
#define MODULE_DS18B20 1
// Enable this module to use one of the following sensors: SENSOR_BH1750
#define MODULE_BH1750 0
// Enable this module to use one of the following sensors: SENSOR_MLX90614
#define MODULE_MLX90614 0
// Enable this module to use one of the following sensors: SENSOR_BME280
#define MODULE_BME280 0

#endif
