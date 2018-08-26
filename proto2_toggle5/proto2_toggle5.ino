#define BLYNK_PRINT Serial

#include <BlynkSimpleSerialBLE.h>

#include <SoftwareSerial.h>

SoftwareSerial SerialBLE(4,7); // RX, TX

#include <Servo.h> 

Servo myservo;



BlynkTimer timer;

int motorR1= 3, motorR2=5 , motorL1=9 , motorL2=6;

const int trigPin = 12;

const int echoPin = 13;

long duration;

int distance;

char auth[] = "89c6f85111344502acd50d7b5a21b488";

#define BLYNK_MAX_READBYTES 99999

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

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;

Serial.print("Distance: ");

Serial.println(distance);

Blynk.virtualWrite(V5, distance);

}





BLYNK_WRITE(V2)

{

   int pos = param[0].asInt();

   pos=map(pos , -90 ,90 , 255, 0);

   myservo.write(pos); 

digitalWrite(trigPin, LOW);

delayMicroseconds(2);

digitalWrite(trigPin, HIGH);

delayMicroseconds(10);

digitalWrite(trigPin, LOW);

duration = pulseIn(echoPin, HIGH);

distance= duration*0.034/2;

Serial.print("Distance: ");

Serial.println(distance);

Blynk.virtualWrite(V5, distance);

}




#define BLYNK_MAX_READBYTES 99999
void setup()

{

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output

  pinMode(echoPin, INPUT);

  pinMode(motorR1 , OUTPUT);

  pinMode(motorR2 , OUTPUT);

  pinMode(motorL1 , OUTPUT);

  pinMode(motorL2 , OUTPUT);

  pinMode(2, OUTPUT);

  digitalWrite(2 , HIGH);

  myservo.attach(11); 

  Serial.begin(9600);

  SerialBLE.begin(9600);

  Blynk.begin(SerialBLE, auth);

  Serial.println("Waiting for connections...");

}

/*void myTimerEvent()

{

 

}

*/

void loop()

{

  Blynk.run();

  timer.run();



}
