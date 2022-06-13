#include <ArduinoMqttClient.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Servo.h>


#define DHTPIN 2
#define DHTTYPE    DHT11     // DHT 11

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

int servoPin = 9;
Servo servo;
int angle = 0; //The initial position of the servo in degree

///////please enter your sensitive data in the Secret tab/arduino_secrets.h
char ssid[] = SECRET_SSID;        // your network SSID (name)
char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

WiFiClient wifiClient;
MqttClient mqttClient(wifiClient);

const char broker[] = "192.168.59.196";
int        port     = 1883;
const char topic[]  = "light_sensor";
const char topic2[]  = "light_sensor_command";
const char topic3[]  = "temperature_sensor";
const char topic4[] = "temperature_sensor_command";

//set interval for sending messages (milliseconds)
const long interval = 8000;
unsigned long previousMillis = 0;

int count = 0;
int sensorPin = A5; // Declare the input pin here
// int tempPin = A7;
int red = 4;
int green = 7;


// Serial output in 9600 baud
void setup()
{
  Serial.begin(9600);

  servo.attach(servoPin);

  dht.begin();

  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  delayMS = sensor.min_delay / 1000;

  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);

  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  // attempt to connect to Wifi network:
  Serial.print("Attempting to connect to WPA SSID: ");
  Serial.println(ssid);
  while (WiFi.begin(ssid, pass) != WL_CONNECTED) {
    // failed, retry
    Serial.print(".");
    delay(5000);
  }

  Serial.println("You're connected to the network");
  Serial.println();

  Serial.print("Attempting to connect to the MQTT broker: ");
  Serial.println(broker);

  if (!mqttClient.connect(broker, port)) {
    Serial.print("MQTT connection failed! Error code = ");
    Serial.println(mqttClient.connectError());

    while (1);
  }

  Serial.println("You're connected to the MQTT broker!");
  Serial.println();

  // setup for the subscriber part
  // set the message receive callback
  mqttClient.onMessage(onMqttMessage);

  Serial.print("Subscribing to topic: ");
  Serial.println(topic2);
  Serial.println();

  Serial.print("Subscribing to topic: ");
  Serial.println(topic4);
  Serial.println();

  // subscribe to a topic
  mqttClient.subscribe(topic2);
  mqttClient.subscribe(topic4);

  // topics can be unsubscribed using:
  // mqttClient.unsubscribe(topic);

  Serial.print("Topic: ");
  Serial.println(topic2);
  Serial.print("Topic: ");
  Serial.println(topic4);

}

// The program measures the current voltage value at the sensor,
// calculates from this and the known series resistance the current
// resistance value of the sensor and outputs the results to the serial output

void loop()
{
  // call poll() regularly to allow the library to send MQTT keep alive which
  // avoids being disconnected by the broker
  mqttClient.poll();

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // save the last time a message was sent
    previousMillis = currentMillis;


    //-------------Light sensor-----------------
    //    //record random value from A5
    //    int Rvalue = analogRead(A5);

    // Current voltage value is measured...
    int rawValue = analogRead(sensorPin);
    float voltage = rawValue * (5.0 / 1023) * 1000;

    float resistance = 10000 * ( voltage / ( 5000.0 - voltage) );

    //  if(resistance >= 2000){
    //    resistance = 1000;
    //  }
    //  else{
    //    resistance = 500;
    //  }

    Serial.print("Sending message to topic: ");
    Serial.println(topic);
    Serial.println(resistance);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic);
    mqttClient.print(resistance);
    mqttClient.endMessage();

    //--------End light sensor-----------------

    //------------Temperature sensor-----------
    // Delay between measurements.
    delay(delayMS);
    // Get temperature event and print its value.
    sensors_event_t event;
    dht.temperature().getEvent(&event);
    if (isnan(event.temperature)) {
      Serial.println(F("Error reading temperature!"));
    }
    else {
      Serial.print(F("Temperature: "));
      Serial.print(event.temperature);
      Serial.println(F("°C"));
    }





    Serial.print("Sending message to topic: ");
    Serial.println(topic3);
    Serial.println(event.temperature);

    // send message, the Print interface can be used to set the message contents
    mqttClient.beginMessage(topic3);
    mqttClient.print(event.temperature);
    mqttClient.endMessage();

    //--------End temperature sensor-----------

    //--------Servo motor----------------
    // We will scan the angle from 0 to 180 degree. As we 
  // have to enable our motor to open the curtain 
  // in both direction, the angles are important

  for(angle = 0; angle < 180; angle++){
    servo.write(angle);
    delay(15); 
  }

  // Now we will rotate the servo towards other direction
  // for that we will consider the angle from 180 to 0 degree
  
  for (angle = 180; angle > 0; angle--) {
    servo.write(angle);
    delay(15);
  }
    //--------End servo motor------------

    Serial.println();

    // ... and here output to the serial interface
    Serial.print("Voltage value:"); Serial.print(voltage); Serial.print("mV");
    Serial.print(", resistance value:"); Serial.print(resistance); Serial.println("Ohm");
    Serial.println("---------------------------------------");

    // ... and here output to the serial interface
    //    Serial.print("Voltage value:"); Serial.print(voltage); Serial.print("mV");
    //    Serial.print(", temperature value:"); Serial.print(temperature); Serial.println("Celcius degree");
    //    Serial.println("---------------------------------------");

    delay(500);
  }
}

void onMqttMessage(int messageSize) {
  // we received a message, print out the topic and contents
  Serial.println("Received a message with topic '");
  Serial.print(mqttClient.messageTopic());
  String msgTopic = mqttClient.messageTopic();
  Serial.print("', length ");
  Serial.print(messageSize);
  Serial.println(" bytes:");

  String led = "";
  // use the Stream interface to print the contents
  while (mqttClient.available()) {
    char msg = (char)mqttClient.read();
    Serial.print(msg);
    led += msg;
  }
  Serial.print(led);
  //if (msgTopic == "light_sensor_command") {
  if (led == "on") {
    digitalWrite(red, HIGH);
  }
  if (led == "off") {
    digitalWrite(red, LOW);
  }
  //}
  //  } else if (mqttClient.messageTopic() == "temperature_sensor_command") {
  if (led == "On") {
    digitalWrite(green, HIGH);
  }
  if (led == "Off") {
    digitalWrite(green, LOW);
  }
  //  }



  Serial.println();
  Serial.println();
}
