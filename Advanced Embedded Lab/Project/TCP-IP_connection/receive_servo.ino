#include <SoftwareSerial.h>
#include <Servo.h>

int pos = 0;
Servo servo_9;

//float val, voltage, temp;
String ssid     = "Simulator Wifi";  // SSID to connect to
String password = ""; //virtual wifi has no password 
String host     = "api.thingspeak.com"; // Open Weather Map API
const int httpPort   = 80;
String url     = "/channels/1635450/fields/1/last.json?api_key=MWXFEWZ2REP36I4H";
//Replace XXXXXXXXXXXXXXXX by your ThingSpeak Channel API Key


void setupESP8266(void) {
  
  // Start our ESP8266 Serial Communication
  Serial.begin(115200);   // Serial connection over USB to computer
  Serial.println("AT");   // Serial connection on Tx / Rx port to ESP8266
  delay(10);        // Wait a little for the ESP to respond
  if (Serial.find("OK"))
    Serial.println("ESP8266 OK!!!");
    
  // Connect to Simulator Wifi
  Serial.println("AT+CWJAP=\"" + ssid + "\",\"" + password + "\"");
  delay(10);        // Wait a little for the ESP to respond
  if (Serial.find("OK"))
    Serial.println("Connected to WiFi!!!");
  
  // Open TCP connection to the host:
  //ESP8266 connects to the server as a TCP client. 

  Serial.println("AT+CIPSTART=\"TCP\",\"" + host + "\"," + httpPort);
  delay(50);        // Wait a little for the ESP to respond
  if (Serial.find("OK")) 
   Serial.println("ESP8266 Connected to server!!!") ;
 
}

int anydata(void) 
{
   
  // Construct our HTTP call
  String httpPacket = "GET " + url + " HTTP/1.1\r\nHost: " + host + "\r\n\r\n";
  //String httpPacket = "GET https://api.thingspeak.com/channels/1635450/fields/1.json?api_key=MWXFEWZ2REP36I4H&results=20";
  int length = httpPacket.length();
  
  // Send our message length
  Serial.print("AT+CIPSEND=");
  Serial.println(length);
  delay(10); // Wait a little for the ESP to respond if (!Serial.find(">")) return -1;

  // Send our http request
  Serial.print(httpPacket);
  delay(10); // Wait a little for the ESP to respond
  
  while(!Serial.available()) delay(5);	
  String saida = "";
  
  if (Serial.find("\r\n\r\n")){	
    	delay(5);
    
    	unsigned int i = 0; 
    	
  		while (!Serial.find("\"field1\":")){} 
    
  		while (i<60000) { 
            if(Serial.available()) {
                  int c = Serial.read(); 
                  if (c == '.') 
                      break; 
                  if (isDigit(c)) {
                    saida += (char)c; 
                  }   
            }
      		i++;
        }
    }
  if (Serial.find("SEND OK\r\n")){
    	Serial.println("ESP8266 sends data to the server\n");
  		Serial.println("..........\n");
  }
  
    return saida.toFloat();
  
  
  

}

void setup() {
  servo_9.attach(9, 500, 2500);
  setupESP8266();
               
}

void loop() {
  
  anydata();
  int temperature = anydata();
  Serial.print(temperature);
    // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  if(temperature > 50){
    for (pos = 0; pos <= 180; pos += 1) {
      // tell servo to go to position in variable 'pos'
      servo_9.write(pos);
      // wait 15 ms for servo to reach the position
      delay(15); // Wait for 15 millisecond(s)
    }
  }
  else{
    for (pos = 180; pos >= 0; pos -= 1) {
      // tell servo to go to position in variable 'pos'
      servo_9.write(pos);
      // wait 15 ms for servo to reach the position
      delay(15); // Wait for 15 millisecond(s)
    }
  } 
  
  delay(1000);
}
