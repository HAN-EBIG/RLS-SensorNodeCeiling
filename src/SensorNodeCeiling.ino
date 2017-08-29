
#ifndef UNIT_TEST
/*******************************************************************************
* dependancies
********************************************************************************/
// load user settings
#include "config.h"

// load MySensors library
#include <MySensors.h>

// load NodeManager library
#include "NodeManager.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE    DHT22     // DHT 22 (AM2302)
DHT_Unified dht(4, DHTTYPE);
static const uint8_t FORCE_UPDATE_N_READS = 5;

int delayMS = 10;
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
	nodeManager.registerSensor(SENSOR_LDR, A0, LDR_1_ID);

	// NM-sensor:[2], sensor-id:[2], child-id:102
	//nodeManager.registerSensor(SENSOR_LDR, 			SENSOR_2, LDR_2_ID);
	nodeManager.registerSensor(SENSOR_LDR, A1, LDR_2_ID);
	// NM-sensor:[13], sensor-id:[3], child-id:103
	//nodeManager.registerSensor(SENSOR_MOTION, 	SENSOR_3, PIR_1_ID);

	// NM-sensor:[14], sensor-id:[4], child-id:104
	nodeManager.registerSensor(SENSOR_DS18B20, 	5);

	// NM-sensor:[9], sensor-id:[5], child-id:105
	//nodeManager.registerSensor(SENSOR_DHT22, 4); //, DHT_1_ID

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

	initializeDHT();

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

	processTemperature();
	procesLight();
	procesHumidity();
}


/*******************************************************************************
* receive
********************************************************************************/
void receive(const MyMessage &message)
{
	// call NodeManager receive routine
	nodeManager.receive(message);
}

void initializeDHT()
{
	dht.begin();
	sensor_t sensor;
	//dht.temperature().getSensor(&sensor);
	dht.humidity().getSensor(&sensor);
}

int humidity =0;
MyMessage humMsg(DHT_1_ID, V_HUM);
sensors_event_t event;

void procesHumidity()
{
	//
	//sleep(delayMS);
	dht.humidity().getEvent(&event);
	send(humMsg.set(event.relative_humidity,2));
}

/***
** Light Sensor
**/
int lightValue = 0;
int lightValue2 = 0;

MyMessage lightMsg(LDR_1_ID,V_LIGHT_LEVEL);
MyMessage lightMsg2(LDR_2_ID,V_LIGHT_LEVEL);

void procesLight()
{
		lightValue = analogRead(SENSOR_1);
		lightValue2 = analogRead(SENSOR_2);

		send(lightMsg.set(lightValue));
		send(lightMsg2.set(lightValue2));
}


/**
*** Temperature sensor
**/
#define ONE_WIRE_BUS 5 // Pin where dallase sensor is connected
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define CHILD_ID_TEMP_DOOR 1


float lastTemperature;
uint8_t nNoUpdatesTemp;
MyMessage tempMsg(CHILD_ID_TEMP_DOOR,V_TEMP);

void processTemperature()
{
  sensors.requestTemperatures();
  float temperature =  sensors.getTempCByIndex(0);

  if ((lastTemperature != temperature && temperature != -127.00 && temperature != 85.00) || nNoUpdatesTemp == FORCE_UPDATE_N_READS) {
    lastTemperature=temperature;
    nNoUpdatesTemp = 0;
    send(tempMsg.set(temperature,1));
  } else {
    nNoUpdatesTemp++;
  }
}

#endif //define UNIT_TEST
