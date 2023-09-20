/*
 ESP8266 --> ThingSpeak Channel via MKR1000 Wi-Fi
 
 This sketch sends the Wi-Fi Signal Strength (RSSI) of an ESP8266 to a ThingSpeak
 channel using the ThingSpeak API (https://www.mathworks.com/help/thingspeak).
 
 Requirements:
 
   * ESP8266 Wi-Fi Device
   * Arduino 1.6.9+ IDE
   * Additional Boards URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
   * Library: esp8266 by ESP8266 Community
 
 ThingSpeak Setup:
 
   * Sign Up for New User Account - https://thingspeak.com/users/sign_up
   * Create a new Channel by selecting Channels, My Channels, and then New Channel
   * Enable one field
   * Note the Channel ID and Write API Key
    
 Setup Wi-Fi:
  * Enter SSID
  * Enter Password
  
 Tutorial: http://nothans.com/measure-wi-fi-signal-levels-with-the-esp8266-and-thingspeak
   
 Created: Feb 1, 2017 by Hans Scharler (http://nothans.com)
*/

#include <ESP8266WiFi.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>

#include "Adafruit_SHT31.h"
const float SEA_LEVEL_PRESSURE_HPA = 1013.25;
const int DELAY = 2000;
const int STARTUP_DELAY = 500;


Adafruit_SHT31 sht31 = Adafruit_SHT31();
// Wi-Fi Settings
//const char* ssid = "TT"; // your wireless network name (SSID)
//const char* password = "123456788"; // your Wi-Fi network password
const char* ssid = "Dolphitech-wlan"; // your wireless network name (SSID)
const char* password = "DpHtK2019WLan4us"; // your Wi-Fi network password

WiFiClient client;

// ThingSpeak Settings
//const int channelID = 448069;
//String writeAPIKey = "OZCKFAQEBBGTNVOX"; // write API key for your ThingSpeak Channel htt990:use for Dolphitech
//String writeAPIKey = "0VOQ2QPGP3JF67RZ"; // write API key for your ThingSpeak Channel dolphitech
//String writeAPIKey = "T9W8949KHJRDCYC6"; // write API key for your SvartHaugen Channel
String writeAPIKey = "Z35BF0FCHXN47J6E";// write API key for new cleanroom Channel

const char* server = "api.thingspeak.com";
IPAddress staticIP(192, 168, 0, 94); //ESP static ip
IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);    // LED pin as output.
  digitalWrite(LED_BUILTIN, LOW); // turn the LED on.
Serial.begin(115200);
  Wire.begin(D6, D5);
WiFi.mode( WIFI_STA );
//WiFi.config( staticIP, gateway, subnet );
WiFi.begin(ssid, password);
 if (! sht31.begin(0x44)) {   // Set to 0x45 for alternate i2c addr
    Serial.println("Couldn't find SHT31");
    while (1) delay(1);
  }
  
//bme.begin(0x76);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
//  bme.wakeup();
 Serial.println("up");
float tempC = sht31.readTemperature();
  float press_mB = sht31.readHumidity();

  if (! isnan(tempC)) {  // check if 'is not a number'
    Serial.print("Temp *C = "); Serial.print(tempC); Serial.print("\t\t");
  } else { 
    Serial.println("Failed to read temperature");
  }
 if (! isnan(press_mB)) {  // check if 'is not a number'
    Serial.print("Hum. % = "); Serial.println(press_mB);
  } else { 
    Serial.println("Failed to read humidity");
  }

  delay(1000);

//  
//    float tempC = bme.readTemperature();
//   float press_mB = bme.readPressure() / 100;
 //  Serial.println("Temperature:");
//    Serial.print(tempC);
//    bme.sleep();
 //   Serial.println("");
  if (client.connect(server, 80)) {
    
    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();

    // Construct API request body
    String body = "field1=";
           body += String(tempC);
           body += "&field2=";
           body += String(press_mB);
           body += "&field3=";
           body += String(rssi);
  Serial.println(body);

    client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);

  }
  else
  {
    Serial.println("Fail to send");
    }
 
    Serial.println("Go to sleep");
client.stop();
delay(3000);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on.
 ESP.deepSleep(120e6, WAKE_RF_DEFAULT); // Sleep for the time set by 'UpdateInterval'
  // wait and then post again
}

void loop() {
  delay(1000);
 Serial.println("Temperature:");
//
}
