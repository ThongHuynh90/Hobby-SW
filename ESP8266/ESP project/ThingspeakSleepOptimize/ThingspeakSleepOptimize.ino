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
#include <Adafruit_BMP280.h>

const float SEA_LEVEL_PRESSURE_HPA = 1013.25;
const int DELAY = 2000;
const int STARTUP_DELAY = 500;

Adafruit_BMP280 bme;
// Wi-Fi Settings
const char* ssid = "Dolphitech-wlan"; // your wireless network name (SSID)
//const char* ssid = "TT"; // your wireless network name (SSID)

const char* password = "DpHtK2019WLan4us"; // your Wi-Fi network password

//const char* password = "123456788"; // your Wi-Fi network password
char response ='1';
WiFiClient client;

// ThingSpeak Settings
//const int channelID = 1662213;
String writeAPIKey = "T9W8949KHJRDCYC6"; // write API key for your SvartHaugen Channel
String body;
const char* server = "api.thingspeak.com";
IPAddress staticIP(192, 168, 0, 98); //ESP static ip
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
Serial.println("OK:");
bme.begin(0x76);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  bme.wakeup();
    float tempC = bme.readTemperature();
   float press_mB = bme.readPressure() / 100;
 //  Serial.println("Temperature:");
//    Serial.print(tempC);
    bme.sleep();
 //   Serial.println("");
  if (client.connect(server, 80)) {
    
    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();

    // Construct API request body
    body = "field1=";
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
    delay(1000);
    response=client.read();
    delay(1000);
    Serial.println(response);
  }
 
// client.stop();
// delay(3000);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED on.
// ESP.deepSleep(120e6, WAKE_RF_DEFAULT); // Sleep for the time set by 'UpdateInterval'
  // wait and then post again
}

void loop() {
  delay(1000);
client.println("POST /update HTTP/1.1");
    client.println("Host: api.thingspeak.com");
    client.println("User-Agent: ESP8266 (nothans)/1.0");
    client.println("Connection: close");
    client.println("X-THINGSPEAKAPIKEY: " + writeAPIKey);
    client.println("Content-Type: application/x-www-form-urlencoded");
    client.println("Content-Length: " + String(body.length()));
    client.println("");
    client.print(body);
    delay(1000);
    response=client.read();
    delay(1000);
    Serial.println(response);
//
}
