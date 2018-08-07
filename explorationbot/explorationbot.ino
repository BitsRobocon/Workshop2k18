#define BLYNK_PRINT Serial
#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial SerialBLE(0 ,1); // RX, TX
#include <BlynkSimpleSerialBLE.h>

char auth[] = " ef8b08b97c7d459fa76ed473977e0984";
const int trigPin = 12;                                              
const int echoPin = 13;
const int motorR=10;
const int motorL=11;
// defines variables
long duration;
int distance;
int green, blue;

BLYNK_WRITE(V1) 
{
  green = param[0].asInt();
  blue = param[1].asInt();
}

void setup()
{
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  Serial.begin(9600);
  SerialBLE.begin(9600);
  Blynk.begin(SerialBLE, auth);
  Serial.println("Waiting for connections...");
 // Blynk.begin(auth);
}

void loop()
{
  Blynk.run();
  switch(green)
  {
    case 0: //turn left
    analogWrite(motorL, 0);
    analogWrite(motorR, 128);
    delay(100);
    break; 
    case 6: // turn right
    analogWrite(motorL, 128);
    analogWrite(motorR, 0);
    delay(100);
    break;
    default : // put the analog values of the blue in pwm pins 
    blue= blue-128;
    if(blue <= 0)
    blue=0;
    blue=blue*2;
    analogWrite(motorR, blue);
    analogWrite(motorR, blue);
    delay(100);
    break;
    
  }
}
