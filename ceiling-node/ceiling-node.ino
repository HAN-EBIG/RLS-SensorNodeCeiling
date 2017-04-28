#define MY_NODE_ID 50
#define CHILD_ID_TEMP_MIDDLE 1
#define CHILD_ID_LIGHT_INTENSITY 9
#define SLEEP_TIME 30000

#define MY_DEBUG 
#define MY_RADIO_NRF24

#include <SPI.h>
#include <MySensors.h>  
#include <DallasTemperature.h>
#include <OneWire.h>


// Temperature sensor
#define COMPARE_TEMP 0 // Send temperature only if changed? 1 = Yes 0 = No
#define ONE_WIRE_BUS 3 // Pin where dallase sensor is connected 

OneWire oneWire(ONE_WIRE_BUS); 
DallasTemperature sensors(&oneWire); 

float lastTemperature;
MyMessage tempMsg(CHILD_ID_TEMP_MIDDLE,V_TEMP);

// bool receivedConfig = false;
// bool metric = true;

#define LIGHT_SENSOR_PIN A1
int lightLevel = 0;

MyMessage lightMsg(CHILD_ID_LIGHT_INTENSITY,V_LIGHT_LEVEL);



void before()
{
  sensors.begin();
}

void setup()  
{ 
  // requestTemperatures() will not block current thread
  sensors.setWaitForConversion(false);
}

void presentation() {
  sendSketchInfo("Ceiling Node", "1.0");
  present(CHILD_ID_TEMP_MIDDLE,S_TEMP);
  present(CHILD_ID_LIGHT_INTENSITY,V_LIGHT_LEVEL);
}

void loop()     
{     
  processLight();
  processTemperature();
  sleep(SLEEP_TIME);
}

void processLight()
{
  lightLevel = analogRead(LIGHT_SENSOR_PIN);
  send(lightMsg.set(lightLevel)); 
}


void processTemperature()
{
  sensors.requestTemperatures();
  float temperature =  sensors.getTempCByIndex(0); 

  // Only send data if temperature has changed and no error
  #if COMPARE_TEMP == 1
    if (lastTemperature != temperature && temperature != -127.00 && temperature != 85.00) {
  #else
    if (temperature != -127.00 && temperature != 85.00) {
  #endif

    send(tempMsg.set(temperature,1));
    lastTemperature=temperature;
  }  
}

