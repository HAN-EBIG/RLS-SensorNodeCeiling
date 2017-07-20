// load user settings
#include "config.h"

// load MySensors library
#include <MySensors.h>

// load NodeManager library
#include "NodeManager.h"

// create a NodeManager instance
NodeManager nodeManager;

// before
void before() {

	// setup the serial port baud rate
	Serial.begin(MY_BAUD_RATE);

	/****************************
	* Register below your sensors
	****************************/

	//nodeManager.registerSensor(SENSOR_DOOR, SENSOR_1); 		// Registers a magnetic reed switch sensor onto digital pin 2 (interupt)
	//nodeManager.registerSensor(SENSOR_DOOR, SENSOR_2); 		// Registers a magnetic reed switch sensor onto digital pin 3  (interupt)
	//nodeManager.registerSensor(SENSOR_DS18B20, SENSOR_3);  	// Registers a DS18B20 Temperature sensor on Digital pin 4
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
