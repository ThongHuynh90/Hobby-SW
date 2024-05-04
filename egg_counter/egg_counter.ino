// #include <TridentTD_7Segs74HC595.h>
#include "NTPClient.h"
#include "ESP8266WiFi.h"
#include "WiFiUdp.h"



#define SCLK D5
#define RCLK D6
#define DIO D1
#define DETECT_SENSOR_VAL 0  // detect:0 ; idle: 1
#define IDLE 0
#define OBJECT_DETECTING 1
#define WAIT_FOR_IDLE 2
#define OBJECT_DETECT_CONFIRM 0  // detect 3 times. confirm
#define NO_OBJECT_CONFIRM 0      // detect 3 times. confirm


//TridentTD_7Segs74HC595 my7SEGMENT(SCLK, RCLK, DIO);

//const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;  // value read from the pot
int counter = 0;
int state = IDLE;
int object_confirm = 0;
int idle_confirm = 0;
uint idle_count = 0;  // counting to detect if the system is free -> sent report
const char *ssid = "Trump";
const char *password = "P@831888";
const uint idle_count_max = 36000;// rest after 30min
const uint counter_max = 6000;  //30000; //20 cay

const long utcOffsetInSeconds = 25200;
String line;
char daysOfTheWeek[7][12] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
WiFiClient client;
void setup() {
  Serial.begin(115200);
  Serial.println();

  Serial.print("sensor = ");
  Serial.print("sensor = ");

  //  my7SEGMENT.init();
  pinMode(DIO, INPUT);
  // my7SEGMENT.init(INVERT_MODE);   //

  //  my7SEGMENT.setTextScroll("TRAI GA HOANG LAN");
}

void loop() {
  // Serial.println(idle_count);
  if (idle_count > idle_count_max && counter > counter_max) {  // if idle and has more than 20 cay trung
    if (getTime_task() >= 16) {                                // get time, if time is later than 11.00 pm
      thinkSpeak_report_task();
    }

    idle_count = 0;
  } else {
    count_task();
  }
  delay(50);
}

int getTime_task() {
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();

  timeClient.update();

  Serial.print(daysOfTheWeek[timeClient.getDay()]);
  Serial.print(", ");
  Serial.print(timeClient.getHours());
  Serial.print(":");
  Serial.print(timeClient.getMinutes());
  Serial.print(":");
  Serial.println(timeClient.getSeconds());
  //Serial.println(timeClient.getFormattedTime());
  return timeClient.getHours();
}

void count_task() {
  sensorValue = digitalRead(DIO);
  switch (state) {
    case IDLE:
      if (sensorValue == DETECT_SENSOR_VAL) {  // detecting an object
      counter++;   
        state = WAIT_FOR_IDLE;
        idle_count = 0;
      } else {
        idle_count++;
      }
      break;
    case OBJECT_DETECTING:
      if (sensorValue == DETECT_SENSOR_VAL) {  // distance get closer, detecting an object
        object_confirm = object_confirm + 1;   // object_confirm 3 times
        if (object_confirm > OBJECT_DETECT_CONFIRM) {
          object_confirm = 0;     // reset object_confirm
          counter++;              // increase counter
          state = WAIT_FOR_IDLE;  //change state
        }
      } else {
        object_confirm = 0;  // reset object_confirm, just noise
        state = IDLE;        //back ti idle state
      }
      break;
    case WAIT_FOR_IDLE:
      if (sensorValue != DETECT_SENSOR_VAL) {  // no object
        idle_confirm = idle_confirm + 1;       // confirm 3 times
        if (idle_confirm > NO_OBJECT_CONFIRM) {
          idle_confirm = 0;  // reset idle_confirm
          state = IDLE;      //change state
          Serial.print("  ** count = ");
          Serial.println(counter);
        }
      } else {
        idle_confirm = 0;  // reset idle_confirm, just noise
      }
      break;
    default:
      break;
  }
}

void thinkSpeak_report_task() {
  Serial.println("Reporting to ThinkSpeak");
  String writeAPIKey = "3DNC5I3FMOSCR2HK";  // write API key for channel Trai ga

  const char *server = "api.thingspeak.com";
  IPAddress staticIP(192, 168, 0, 198);  //ESP static ip
  IPAddress gateway(192, 168, 0, 1);     //IP Address of your WiFi Router (Gateway)
  IPAddress subnet(255, 255, 255, 0);    //Subnet mask
  if (client.connect(server, 80)) {

    // Measure Signal Strength (RSSI) of Wi-Fi connection
    long rssi = WiFi.RSSI();

    // Construct API request body
    String body = "field1=";
    body += String(counter);
    body += "&field2=";
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
    while (client.connected())
   {    
    line = client.readStringUntil('\r');
    if (line.equals("HTTP/1.1 200 OK")) {
      Serial.println(line);
    counter=0;
    break;
}
   }

  } else {
    Serial.println("Fail to send");
  }
  client.stop();
}
