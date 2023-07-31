#include <TridentTD_7Segs74HC595.h>

#define SCLK D5
#define RCLK D6
#define DIO D7
#define IDLE_SENSOR_VAL 600 // smaller ~futher, bigger = closer
#define IDLE 0
#define OBJECT_DETECTING 1
#define WAIT_FOR_IDLE 2

TridentTD_7Segs74HC595 my7SEGMENT(SCLK, RCLK, DIO);

const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
int sensorValue = 0;         // value read from the pot
int counter = 0;
int state = IDLE;
int object_confirm=0;
int idle_confirm = 0;
void setup() {
  Serial.begin(115200);
  Serial.println();

  my7SEGMENT.init();
  // my7SEGMENT.init(INVERT_MODE);   // 

  my7SEGMENT.setTextScroll("TRAI GA HOANG LAN");
}

void loop() {
    sensorValue = analogRead(analogInPin);
    switch (state) {
      case IDLE:
        if (sensorValue > IDLE_SENSOR_VAL) {    // distance get closer, detecting an object
        state = OBJECT_DETECTING;
        }
        break;
      case OBJECT_DETECTING:
        if (sensorValue > IDLE_SENSOR_VAL) {    // distance get closer, detecting an object
          object_confirm = object_confirm + 1;  // object_confirm 3 times
          if (object_confirm > 3) {
            object_confirm = 0;     // reset object_confirm
            counter++;              // increase counter
            state = WAIT_FOR_IDLE;  //change state
          }
        }
        else
        {
          object_confirm = 0;     // reset object_confirm, just noise
          state = IDLE;  //back ti idle state
        }
        break;
      case WAIT_FOR_IDLE:
      if (sensorValue < IDLE_SENSOR_VAL) {    // distance get further, object out
          idle_confirm = idle_confirm + 1;  // object_confirm 3 times
          if (idle_confirm > 3) {
            idle_confirm = 0;     // reset idle_confirm
            state = IDLE;  //change state
          }
        }
        else
        {
          idle_confirm = 0;     // reset idle_confirm, just noise
        }
      break;
      default:
      break;
    }

    Serial.print("sensor = ");
    Serial.print(sensorValue);
    Serial.print("  ** state = ");
    Serial.println(state);
    my7SEGMENT.setNumber(counter, 0);
    delay(100);
}
