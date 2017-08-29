# 1 "/var/folders/8s/bqmvbwfs6v70kbxf76d39w5m0000gn/T/tmpI6mkfE"
#include <Arduino.h>
# 1 "/Users/jornbrouwer/Programeren/RLS-SensorNodeCeiling/src/SensorNodeCeiling.ino"

#ifndef UNIT_TEST




#include "config.h"


#include <MySensors.h>


#include "NodeManager.h"

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTTYPE DHT22
DHT_Unified dht(4, DHTTYPE);
static const uint8_t FORCE_UPDATE_N_READS = 5;

int delayMS = 10;




NodeManager nodeManager;
void before();
void presentation();
void setup();
void loop();
void receive(const MyMessage &message);
void initializeDHT();
void procesHumidity();
void procesLight();
void processTemperature();
#line 34 "/Users/jornbrouwer/Programeren/RLS-SensorNodeCeiling/src/SensorNodeCeiling.ino"
void before()
{
 Serial.begin(MY_BAUD_RATE);






 nodeManager.registerSensor(SENSOR_LDR, A0, LDR_1_ID);



 nodeManager.registerSensor(SENSOR_LDR, A1, LDR_2_ID);




 nodeManager.registerSensor(SENSOR_DS18B20, 5);







 nodeManager.before();

 nodeManager.setSleepMode(SLEEP);
 nodeManager.setSleepTime(SLEEP_TIME_IN_SECONDS);
 nodeManager.setSleepUnit(SECONDS);
}




void presentation()
{

 sendSketchInfo(SKETCH_NAME, SKETCH_VERSION);

 nodeManager.presentation();
}





void setup()
{

 nodeManager.setup();

 Serial.println("----");
 Serial.println("..Systems ready..");

 initializeDHT();




}





void loop()
{

 nodeManager.loop();

 processTemperature();
 procesLight();
 procesHumidity();
}





void receive(const MyMessage &message)
{

 nodeManager.receive(message);
}

void initializeDHT()
{
 dht.begin();
 sensor_t sensor;

 dht.humidity().getSensor(&sensor);
}

int humidity =0;
MyMessage humMsg(DHT_1_ID, V_HUM);
sensors_event_t event;

void procesHumidity()
{


 dht.humidity().getEvent(&event);
 send(humMsg.set(event.relative_humidity,2));
}




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





#define ONE_WIRE_BUS 5
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define CHILD_ID_TEMP_DOOR 1


float lastTemperature;
uint8_t nNoUpdatesTemp;
MyMessage tempMsg(CHILD_ID_TEMP_DOOR,V_TEMP);

void processTemperature()
{
  sensors.requestTemperatures();
  float temperature = sensors.getTempCByIndex(0);

  if ((lastTemperature != temperature && temperature != -127.00 && temperature != 85.00) || nNoUpdatesTemp == FORCE_UPDATE_N_READS) {
    lastTemperature=temperature;
    nNoUpdatesTemp = 0;
    send(tempMsg.set(temperature,1));
  } else {
    nNoUpdatesTemp++;
  }
}

#endif