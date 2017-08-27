
/*******************************************************************************
* dependancies
********************************************************************************/
// load user settings
#include "config.h"

// load MySensors library
#include <MySensors.h>

// load NodeManager library
#include "NodeManager.h"

#ifndef UNIT_TEST
//#include <Arduino.h>

/*******************************************************************************
* instances
********************************************************************************/
NodeManager nodeManager; // create a NodeManager instance

//int interrupt_pin_1 = getInterruptPin();
/*******************************************************************************
* before
********************************************************************************/
void before()
{
	Serial.begin(MY_BAUD_RATE); // setup the serial port baud rate

	/****************************
	* Register below your sensors
	****************************/

  // NodeManager-sensor:[2], sensor-id:[1], child-id:101
	nodeManager.registerSensor(SENSOR_LDR, 			SENSOR_1, LDR_1_ID);

	// NM-sensor:[2], sensor-id:[2], child-id:102
	nodeManager.registerSensor(SENSOR_LDR, 			SENSOR_2, LDR_2_ID);

	// NM-sensor:[13], sensor-id:[3], child-id:103
	nodeManager.registerSensor(SENSOR_MOTION, 	SENSOR_3, PIR_1_ID);

	// NM-sensor:[14], sensor-id:[4], child-id:104
	nodeManager.registerSensor(SENSOR_DS18B20, 	SENSOR_4, DS18_1_ID);

	// NM-sensor:[9], sensor-id:[5], child-id:105
	nodeManager.registerSensor(SENSOR_DHT22, 		SENSOR_5, DHT_1_ID);

	/****************************
	* Register above your sensors
	****************************/
	nodeManager.before();

	nodeManager.setSleepMode(SLEEP);
	nodeManager.setSleepTime(SLEEP_TIME_IN_SECONDS);
	nodeManager.setSleepUnit(SECONDS);
}


/*******************************************************************************
* presentation
********************************************************************************/
void presentation()
{
	// Send the sketch version information to the gateway and Controller
	sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);
	// call NodeManager presentation routine
	nodeManager.presentation();
}


/*******************************************************************************
* setup
********************************************************************************/
void setup()
{
	// call NodeManager setup routine
	nodeManager.setup();

	Serial.println("----");
	Serial.println("..Systems ready..");

	//get the address of the DS18B20
	//((SensorDs18b20*)nodeManager.getSensor(SENSOR_2))->getDeviceAddress();
	//((SensorDs18b20*)nodeManager.getSensor(SENSOR_2))->getResolution();
}


/*******************************************************************************
* loop
********************************************************************************/
void loop()
{
	// call NodeManager loop routine
	nodeManager.loop();
}


/*******************************************************************************
* receive
********************************************************************************/
void receive(const MyMessage &message)
{
	// call NodeManager receive routine
	nodeManager.receive(message);
}

#endif //define UNIT_TEST
