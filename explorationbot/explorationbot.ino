#define BLYNK_PRINT Serial
#include <SPI.h>
#include <SoftwareSerial.h>
SoftwareSerial SerialBLE(10,11); // RX, TX
#include <BlynkSimpleSerialBLE.h>

char auth[] = "89c6f85111344502acd50d7b5a21b488";
const int trigPin = 12;                                              
const int echoPin = 13;
const int motorR=6;
const int motorL=5;
// defines variables
long duration;
int distance;
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos=0;

void setup()
{
  pinMode(motorR, OUTPUT);
  pinMode(motorL, OUTPUT);
  Serial.begin(9600);
  Blynk.begin(SerialBLE, auth);
  SerialBLE.begin(9600);
   myservo.attach(3);  
  Serial.println("Waiting for connections...");
}

void loop()
{
  Blynk.run();
 for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  }

