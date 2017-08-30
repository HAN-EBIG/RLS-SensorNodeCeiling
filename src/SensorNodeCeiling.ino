
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

//TODO check if the 3 includes below are indeed obsolete
//#include <Adafruit_Sensor.h>
//#include <DHT.h>
//#include <DHT_U.h>

//Define Sensors, normal way of registering the sensors on the ceiling node
#define LDR_ROOM
#define LDR_BEAMER
#define DHT_CEILING
#define DS18B20_CEILING
//#define PIR_CEILING


//@override, remove commenting to use custom implementation of sensors
//#define CUSTOM_LDR
//#define CUSTOM_DHT22
//#define CUSTOM_DS18B20

/*******************************************************************************
* instances
********************************************************************************/
NodeManager nodeManager; // create a NodeManager instance

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
	#ifdef LDR_ROOM
		//int sensor_ldr_room = nodeManager.regis§terSensor(SENSOR_LDR, A0, LDR_1_ID); //LDR_1_ID
		nodeManager.registerSensor(SENSOR_LDR, A0, LDR_1_ID);
		//int sensor_ldr = nodeManager.registerSensor(SENSOR_LDR,A1);
		//((SensorLDR*)nodeManager.getSensor(sensor_ldr))->setSamples(3);
	#endif

	#ifdef LDR_BEAMER
		//int sensor_ldr_beamer = nodeManager.registerSensor(SENSOR_LDR, A1, LDR_2_ID); //LDR_2_ID
		nodeManager.registerSensor(SENSOR_LDR, A1, LDR_2_ID);
	#endif

	#ifdef PIR_CEILING
		nodeManager.registerSensor(SENSOR_MOTION, 	SENSOR_3, PIR_1_ID);
	#endif

	// #ifdef DS18B20_CEILING
		//float sensor_ds18b20 = nodeManager.registerSensor(SENSOR_DS18B20, 	5);
		nodeManager.registerSensor(SENSOR_DS18B20, 	4);
	// #endif

	#ifdef DHT_CEILING
		// TODO CANNOT Get THE CORRECT CHILD-ID'S
		//int sensor_dht22 = nodeManager.registerSensor(SENSOR_DHT22, 4); //, DHT_1_ID
		nodeManager.registerSensor(SENSOR_DHT22, 3, 35);
		//((SensorDHT*)nodeManager.getSensor(sensor_dht22)->getType();
	#endif

	/****************************
	* Register above your sensors
	****************************/
	nodeManager.before();
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
	//int deviceAdress = ((SensorDs18b20*)nodeManager.getSensor(SENSOR_2))->getDeviceAddress();
	//((SensorDs18b20*)nodeManager.getSensor(SENSOR_2))->getResolution();
}


/*******************************************************************************
* loop
********************************************************************************/
void loop()
{
	// call NodeManager loop routine
	nodeManager.loop();

	#ifdef CUSTOM_DS18B20
		processTemperature();
	#endif

	#ifdef CUSTOM_LDR
		procesLight();
	#endif

	#ifdef CUSTOM_DHT22
		procesHumidity();
	#endif
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
