// load user settings
#include "config.h"

// load MySensors library
#include <MySensors.h>

// load NodeManager library
#include "NodeManager"

// create a NodeManager instance
NodeManager nodeManager;

// before
void before() {

	// setup the serial port baud rate
	Serial.begin(MY_BAUD_RATE);

	/****************************
	* Register below your sensors
	****************************/
	nodeManager.registerSensor(SENSOR_LDR, SENSOR_1);  			// Registers a Light intensity sensor onto analog pin 0 
	nodeManager.registerSensor(SENSOR_MOTION, SENSOR_2); 		// Registers a PIR motion sensor to digital on digital pin 2 (interrupt) 
	nodeManager.registerSensor(SENSOR_DS18B20, SENSOR_3); 		// Registers a DS18B20 Temperature sensor on Digital pin 3
	nodeManager.registerSensor(SENSOR_DHT22, SENSOR_4); 		// Registers a DHT22 temperature/humidity sensor on digital 4
	/****************************
	* Register above your sensors
	****************************/

	nodeManager.before();
}

// presentation
void presentation() {
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);
	// call NodeManager presentation routine
	nodeManager.presentation();
}

// setup
void setup() 
{
	// call NodeManager setup routine
	nodeManager.setup();
}

// loop
void loop() {
	// call NodeManager loop routine
	nodeManager.loop();
}

// receive
void receive(const MyMessage &message) {
	// call NodeManager receive routine
	nodeManager.receive(message);
}