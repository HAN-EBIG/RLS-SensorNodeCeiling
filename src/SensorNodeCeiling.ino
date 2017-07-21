/*Dependancies*/
// load user settings
#include "config.h"

// load MySensors library
#include <MySensors.h>

// load NodeManager library
#include "NodeManager.h"

#ifndef UNIT_TEST
//#include <Arduino.h>

// create a NodeManager instance
NodeManager nodeManager;

// before
void before()
{

	// setup the serial port baud rate
	Serial.begin(MY_BAUD_RATE);

	/****************************
	* Register below your sensors
	****************************/
	nodeManager.setSleepMode(ALWAYS_ON);
	//nodeManager.setSleepBetweenSend(10000);
  nodeManager.registerSensor(SENSOR_LDR, 			SENSOR_1, LDR_1_ID);
	nodeManager.registerSensor(SENSOR_LDR, 			SENSOR_2, LDR_2_ID);
	nodeManager.registerSensor(SENSOR_MOTION, 	SENSOR_3, PIR_1_ID);
	nodeManager.registerSensor(SENSOR_DS18B20, 	SENSOR_4, DS18_1_ID);
	nodeManager.registerSensor(SENSOR_DHT22, 		SENSOR_5, DHT_1_ID);
	/****************************
	* Register above your sensors
	****************************/
	nodeManager.before();
}

// presentation
void presentation()
{
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

#endif //define UNIT_TEST
