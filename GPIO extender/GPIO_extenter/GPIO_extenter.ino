/*
  Serial Event example

 When new serial data arrives, this sketch adds it to a String.
 When a newline is received, the loop prints the string and
 clears it.

 A good test for this is to try it with a GPS receiver
 that sends out NMEA 0183 sentences.

 Created 9 May 2011
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialEvent

 */

char inputString = ' ';         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(115200);
  // reserve 200 bytes for the inputString:
for(int i=5;i<14;i++)
{
  pinMode(i, OUTPUT);
}
Serial.println(LED_BUILTIN);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    
    switch (inputString)
    {
 case '1':
          digitalWrite(12, HIGH); 
          break;
 case '2':
          digitalWrite(11, HIGH); 
          break;
  case '3':
          digitalWrite(10, HIGH); 
          break;
  case '4':
          digitalWrite(9, HIGH); 
          break;
  case '5':
          digitalWrite(8, HIGH); 
          break;
  case '6':
          digitalWrite(7, HIGH); 
          break;
  case '7':
          digitalWrite(6, HIGH); 
          break;
  case '8':
          digitalWrite(5, HIGH); 
          break;
 case 'q':
          digitalWrite(12, LOW); 
          break;
 case 'w':
          digitalWrite(11, LOW); 
          break;
  case 'e':
          digitalWrite(10, LOW); 
          break;
  case 'r':
          digitalWrite(9, LOW); 
          break;
  case 't':
          digitalWrite(8, LOW); 
          break;
  case 'y':
          digitalWrite(7, LOW); 
          break;
  case 'u':
          digitalWrite(6, LOW); 
          break;
  case 'i':
          digitalWrite(5, LOW); 
          break;
 default:
          digitalWrite(13, LOW); 
          Serial.println(inputString);
    };
    // clear the string:
    inputString = ' ';
    stringComplete = false;

  }
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString = inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
   // if (inChar == '\n') {
      stringComplete = true;
 //   }
  }
}


