
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

//@override, remove // to use custom implementation of sensors
//#define CUSTOM_LDR
//#define CUSTOM_DHT22
//#define CUSTOM_DS18B20

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


	nodeManager.setSleepMode(SLEEP);
	nodeManager.setSleepTime(SLEEP_TIME_IN_SECONDS);
	nodeManager.setSleepUnit(SECONDS);

	/****************************
	* Register below your sensors
	****************************/
	//TODO Remove hardcoded pin_numbers
	nodeManager.registerSensor(SENSOR_LDR, A0); //LDR_1_ID
	//nodeManager.registerSensor(SENSOR_LDR, A1); //LDR_2_ID
	//nodeManager.registerSensor(SENSOR_MOTION, 	SENSOR_3, PIR_1_ID);
	nodeManager.registerSensor(SENSOR_DS18B20, 	5);
	nodeManager.registerSensor(SENSOR_DHT22, 4); //, DHT_1_ID
	/****************************
	* Register above your sensors
	****************************/
	nodeManager.before();

	int sensor_ldr = nodeManager.registerSensor(SENSOR_LDR,A1);
 ((SensorLDR*)nodeManager.getSensor(sensor_ldr))->setSamples(3);

 	//TODO: change position of sleep funtions inside the before() loop
	/*
	nodeManager.setSleepMode(SLEEP);
	nodeManager.setSleepTime(SLEEP_TIME_IN_SECONDS);
	nodeManager.setSleepUnit(SECONDS);
	*/
	//TODO
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

	#ifdef CUSTOM_DHT22
		initializeDHT();
	#endif

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

	//processTemperature();
	//procesLight();
	//procesHumidity();
}


/*******************************************************************************
* receive
********************************************************************************/
void receive(const MyMessage &message)
{
	// call NodeManager receive routine
	nodeManager.receive(message);
}



//CUSTOM IMPLEMENTATIONS
/*******************************************************************************
* DHT22
********************************************************************************/
#ifdef CUSTOM_DHT22
	#define DHTTYPE    DHT22     // DHT 22 (AM2302)
	DHT_Unified dht(4, DHTTYPE);

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
		dht.humidity().getEvent(&event);
		send(humMsg.set(event.relative_humidity,2));
		//((SensorDht22*)nodeManager.getSensor(DHT_1_ID))->getValueInt();
	}
#endif //Custom dht22
/*******************************************************************************
* LDR SENSORS (BEAMER + ROOM)
********************************************************************************/
#ifdef CUSTOM_LDR
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
#endif //CUSTOM LDR
/*******************************************************************************
* DS18B20 Waterproof (1meter)
********************************************************************************/

#ifdef CUSTOM_DS18B20

	#define CHILD_ID_TEMP_DOOR 1
	#define ONE_WIRE_BUS 5 // Pin where dallase sensor is connected
	#define FORCE_UPDATE_N_READS 5

	OneWire oneWire(ONE_WIRE_BUS);
	DallasTemperature sensors(&oneWire);

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
#endif //CUSTOM DSB
#endif //define UNIT_TEST
