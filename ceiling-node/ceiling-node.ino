#define MY_NODE_ID 50
#define CHILD_ID_TEMP_MIDDLE 1
#define CHILD_ID_LIGHT_INTENSITY 9
#define CHILD_ID_HUMIDITY 12
#define SLEEP_TIME 120000

#define MY_DEBUG 
#define MY_RADIO_NRF24

#include <SPI.h>
#include <MySensors.h>  
#include <DallasTemperature.h>
#include <OneWire.h>
#include <DHT.h>

static const uint8_t FORCE_UPDATE_N_READS = 5;

// Humidity sensor
#define DHT_DATA_PIN 4

float lastHum;
uint8_t nNoUpdatesHum;
MyMessage msgHum(CHILD_ID_HUMIDITY, V_HUM);
DHT dht;


// Temperature sensor
#define ONE_WIRE_BUS 3 // Pin where dallase sensor is connected 
OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 

float lastTemperature;
uint8_t nNoUpdatesTemp;
MyMessage tempMsg(CHILD_ID_TEMP_MIDDLE,V_TEMP);

#define LIGHT_SENSOR_PIN A1
int lightLevel = 0;
int lastLightLevel;
uint8_t nNoUpdatesLight;

MyMessage lightMsg(CHILD_ID_LIGHT_INTENSITY,V_LIGHT_LEVEL);

void before()
{
  sensors.begin();
}

void setup()  
{ 
  // requestTemperatures() will not block current thread
  sensors.setWaitForConversion(false);
  dht.setup(DHT_DATA_PIN);
  sleep(SLEEP_TIME);
}

void presentation() {
  sendSketchInfo("Ceiling Node", "1.0");
  present(CHILD_ID_TEMP_MIDDLE,S_TEMP);
  present(CHILD_ID_LIGHT_INTENSITY,V_LIGHT_LEVEL);
  present(CHILD_ID_HUMIDITY, S_HUM);
}

void loop()     
{     
  processLight();
  processTemperature();
  processHumidity();
  sleep(SLEEP_TIME);
  
}

void processHumidity()
{
// Get humidity from DHT library
  float humidity = dht.getHumidity();
  // Only send humidity if it changed since the last measurement or if we didn't send an update for n times  
  if (humidity != lastHum || nNoUpdatesHum == FORCE_UPDATE_N_READS) {
    lastHum = humidity;
    nNoUpdatesHum = 0;
    send(msgHum.set(humidity, 1));
  } else {
    nNoUpdatesHum++;
  }  
  
}

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

void processLight()
{
  lightLevel = analogRead(LIGHT_SENSOR_PIN);
  if(lastLightLevel != lightLevel || nNoUpdatesLight == FORCE_UPDATE_N_READS){
    lastLightLevel = lightLevel;
    nNoUpdatesLight = 0;
    send(lightMsg.set(lightLevel)); 
  } else {
    nNoUpdatesLight++;
  }
  
  
}




