#define BLYNK_PRINT Serial
#include <BlynkSimpleSerialBLE.h>
#include <SoftwareSerial.h>

SoftwareSerial SerialBLE(4,7); // RX, TX
#include <Servo.h> 
Servo myservo;
int motorR1= 3, motorR2=5 , motorL1=9 , motorL2=6;
int powpin=8;
int trigpin=12;
int echopin=13;
long duration;
int distance;
char auth[] = "89c6f85111344502acd50d7b5a21b488";
#define BLYNK_MAX_READBYTES 99999
void ultsnd()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  
  duration=pulseIn(echopin,HIGH);
  distance=(duration/2)/29;

  Serial.print("Distance: ");
  Serial.println(distance);
 
  
}
BLYNK_WRITE(V1) {
  int x = param[0].asInt();
  int y = param[1].asInt();

  // Do something with x and y
  Serial.print("X = ");
  Serial.print(x);
  Serial.print("; Y = ");
  Serial.println(y);
int a;
if(0<=y && y<=37)
a=0;
else if(219<=y && y<=255)
a=1;
if(0<=x && x<=37)
a=2;
else if(219<=x && x<=255)
a=3;
else if(x==128 && y==128)
a=4;
switch(a)
{
  case 0: //turn back
    analogWrite(motorR1, 255-y);
    analogWrite(motorL1, 255-y);
    analogWrite(motorR2, 0);
    analogWrite(motorL2, 0);
    break;
 case 1: //go straight
    analogWrite(motorR2, y);
    analogWrite(motorL2, y);
    analogWrite(motorR1, 0);
    analogWrite(motorL1, 0);
    break;

 case 2: // turn left x(0-37)
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 255-x);
    analogWrite(motorR1, 255-x);
    analogWrite(motorR2, 0);
    break;
 
 case 3: // turn right x(219-255)
    analogWrite(motorR1, 0);
    analogWrite(motorR2, x);
    analogWrite(motorL1, x);
    analogWrite(motorL2, 0);
    break;
case 4:
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 0);
    analogWrite(motorR1, 0);
    analogWrite(motorR2, 0);
    break;
default:
    analogWrite(motorL1, 0);
    analogWrite(motorL2, 0);
    analogWrite(motorR1, 0);
    analogWrite(motorR2, 0);
    break;

}
}

BLYNK_WRITE(V2)
{
   int pos = param[0].asInt();
   pos=map(pos,-90,90,255,0);
   myservo.write(pos);
}

BLYNK_WRITE(V3)
{
  int buttonState=param.asInt();
  Serial.println(buttonState);
  
  if(buttonState==1)
  {
  ultsnd();
  Blynk.virtualWrite(V5,distance);
  Serial.println(buttonState);
  Blynk.run();
  buttonState=param.asInt();

  }
}
BLYNK_CONNECTED()
{
  Blynk.syncVirtual(V1);
  Blynk.syncVirtual(V2);
  Blynk.syncVirtual(V3);
}
void setup()
{
  pinMode(powpin,OUTPUT);
  pinMode(motorR1 , OUTPUT);
  pinMode(motorR2 , OUTPUT);
  pinMode(motorL1 , OUTPUT);
  pinMode(motorL2 , OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(trigpin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echopin, INPUT);
  digitalWrite(2 , HIGH);
  digitalWrite(powpin,HIGH);
  myservo.attach(10); 
  // Debug console
  Serial.begin(9600);

  SerialBLE.begin(9600);
  Blynk.begin(SerialBLE, auth);

  Serial.println("Waiting for connections...");
  
}

void loop()
{
  
  Blynk.run();
  
}

