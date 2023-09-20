/*
  ESP8266 --> ThingSpeak Channel via MKR1000 Wi-Fi

  This sketch sends the Wi-Fi Signal Strength (RSSI) of an ESP8266 to a ThingSpeak
  channel using the ThingSpeak API (https://www.mathworks.com/help/thingspeak).

  Requirements:

     ESP8266 Wi-Fi Device
     Arduino 1.6.9+ IDE
     Additional Boards URL: http://arduino.esp8266.com/stable/package_esp8266com_index.json
     Library: esp8266 by ESP8266 Community

  ThingSpeak Setup:

     Sign Up for New User Account - https://thingspeak.com/users/sign_up
     Create a new Channel by selecting Channels, My Channels, and then New Channel
     Enable one field
     Note the Channel ID and Write API Key

  Setup Wi-Fi:
    Enter SSID
    Enter Password

  Tutorial: http://nothans.com/measure-wi-fi-signal-levels-with-the-esp8266-and-thingspeak

  Created: Feb 1, 2017 by Hans Scharler (http://nothans.com)
*/

#include <ESP8266WiFi.h>
#include <Adafruit_AHT10.h>

#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

const float SEA_LEVEL_PRESSURE_HPA = 1013.25;
const int DELAY = 2000;
const int STARTUP_DELAY = 500;

//Adafruit_BMP280 bme;

Adafruit_AHT10 sensor;
// Wi-Fi Settings
const char* ssid = "Dolphitech-wlan"; // your wireless network name (SSID)
//const char* ssid = "TT"; // your wireless network name (SSID)

const char* password = "DpHtK2019WLan4us"; // your Wi-Fi network password

//const char* password = "123456788"; // your Wi-Fi network password
char response = '1';
WiFiClient client;

// ThingSpeak Settings
//const int channelID = 1662213;
//String writeAPIKey = "T9W8949KHJRDCYC6"; // write API key for your SvartHaugen Channel
String writeAPIKey = "Z35BF0FCHXN47J6E";// write API key for new cleanroom Channel
String body;
const char* server = "api.thingspeak.com";
IPAddress staticIP(192, 168, 0, 99); //ESP static ip
IPAddress gateway(192, 168, 0, 1);   //IP Address of your WiFi Router (Gateway)
IPAddress subnet(255, 255, 255, 0);  //Subnet mask
sensors_event_t humidity, temp;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);    // LED pin as output.
  digitalWrite(LED_BUILTIN, LOW); // turn the LED on.
  Serial.begin(115200);
   Serial.println("Start:");
  Wire.begin(D6, D5);// sda,  scl
  WiFi.mode( WIFI_STA );
  //WiFi.config( staticIP, gateway, subnet );
  WiFi.begin(ssid, password);
  Serial.println("OK:");
  if (! sensor.begin()) {
    Serial.println("Could not find AHT? Check wiring");
    while (1) delay(10);
  }
  Serial.println("AHT10 or AHT20 found");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  while (!updateData())
  {
    Serial.println("Update failed, try again after 5s");
    delay(5000);

  }
  // delay(3000);
  digitalWrite(LED_BUILTIN, HIGH); // turn the LED off.

  Serial.println("Go to sleep");
   ESP.deepSleep(120e6, WAKE_RF_DEFAULT); // Sleep for the time set by 'UpdateInterval'
  //ESP.deepSleep(5e6, WAKE_RF_DEFAULT); // Sleep for the time set by 'UpdateInterval'
  // wait and then post again
}

void loop() {
  delay(5000);
  while (!updateData())
  {
    Serial.println("Update failed,  try again after 5s");
    delay(5000);

  }

}
int updateData()
{
  sensor.getEvent(&humidity, &temp);// populate temp and humidity objects with fresh data
  Serial.print("Temperature: "); Serial.print(temp.temperature); Serial.println(" degrees C");
  Serial.print("Humidity: "); Serial.print(humidity.relative_humidity); Serial.println("% rH");

  // Construct API request body
  body = "field1=";
  body += String(temp.temperature);
  body += "&field2=";
  body += String(humidity.relative_humidity);
  Serial.println(body);
  if (client.connect(server, 80)) {

    // Construct API request body

    Serial.println("sending");
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
    int len = 0;
    //      Serial.println("receiveing");
    while (client.available() > 0)
    {
      response = client.read();
      client.flush();
      len++;
    }
    //    Serial.println("received");
    //    Serial.println();
    //    Serial.println(len - 640);
    //    Serial.println(response);
    client.stop();
    if (len - 640 <= 0 && response == '0')
    {

      Serial.println("not ok");
      return 0;
    }
    else
    { Serial.println("ok");
      return 1;
    }
  }
}
