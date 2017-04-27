// Enable debug prints to serial monitor
#define MY_DEBUG 

// Enable and select radio type attached
#define MY_RADIO_NRF24

#define MY_NODE_ID 50
#define CHILD_ID_TEMP_MIDDLE 1
#define CHILD_ID_LIGHT_INTENSITY 9

#include <SPI.h>
#include <MySensors.h>  
#include <DallasTemperature.h>
#include <OneWire.h>

#define COMPARE_TEMP 0 // Send temperature only if changed? 1 = Yes 0 = No

#define ONE_WIRE_BUS 3 // Pin where dallase sensor is connected 

unsigned long SLEEP_TIME = 30000; // Sleep time between reads (in milliseconds)
OneWire oneWire(ONE_WIRE_BUS); // Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
DallasTemperature sensors(&oneWire); // Pass the oneWire reference to Dallas Temperature. 

int LIGHT_SENSOR_PIN  = A1;
int lightLevel = 0;

float lastTemperature;


bool receivedConfig = false;
bool metric = true;
// Initialize temperature message
MyMessage tmpMsg(0,V_TEMP);
MyMessage lightMsg(CHILD_ID_LIGHT_INTENSITY,V_LIGHT_LEVEL);

void before()
{
  // Startup up the OneWire library
  sensors.begin();
}

void setup()  
{ 
  // requestTemperatures() will not block current thread
  sensors.setWaitForConversion(false);
}

void presentation() {
  // Send the sketch version information to the gateway and Controller
  sendSketchInfo("Ceiling Node", "1.0");

  // Present sensor to controller
  present(CHILD_ID_TEMP_MIDDLE,S_TEMP);
  present(CHILD_ID_LIGHT_INTENSITY,V_LIGHT_LEVEL);
}

void loop()     
{     

  // Send light level
  
  lightLevel = analogRead(LIGHT_SENSOR_PIN);
  send(lightMsg.set(lightLevel));
  
  // Fetch temperatures from Dallas sensors
  sensors.requestTemperatures();

  // Read temperatures and send them to controller 
  float temperature =  sensors.getTempCByIndex(0); 

  // Only send data if temperature has changed and no error
  #if COMPARE_TEMP == 1
    if (lastTemperature != temperature && temperature != -127.00 && temperature != 85.00) {
  #else
    if (temperature != -127.00 && temperature != 85.00) {
  #endif

    send(tmpMsg.setSensor(CHILD_ID_TEMP_MIDDLE).set(temperature,1));
    lastTemperature=temperature;
  }

  sleep(SLEEP_TIME);
}
