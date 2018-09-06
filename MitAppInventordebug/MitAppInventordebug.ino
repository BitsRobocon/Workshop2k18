#include <Servo.h> 
Servo myservo;
int tx=1;
int rx=0;
char inSerial[15];
int powpin=8;
int motorR1= 3, motorR2=5 , motorL1=9 , motorL2=6;

int trigpin=12;
int echopin=13;

long duration;
int distance;

void frwd()
{
    analogWrite(motorR1, 200);
    analogWrite(motorL1, 200);
    analogWrite(motorR2, 0);
    analogWrite(motorL2, 0);
}
void bkwd()
{
    analogWrite(motorR1, 0);
    analogWrite(motorL1, 0);
    analogWrite(motorR2, 200);
    analogWrite(motorL2, 200);
}
void stp()
{
    analogWrite(motorR1, 0);
    analogWrite(motorL1, 0);
    analogWrite(motorR2, 0);
    analogWrite(motorL2, 0);
}
void rt()
{
    analogWrite(motorR1, 200);
    analogWrite(motorL1, 0);
    analogWrite(motorR2, 0);
    analogWrite(motorL2, 200);
}

void lt()
{
    analogWrite(motorR1, 0);
    analogWrite(motorL1, 200);
    analogWrite(motorR2, 200);
    analogWrite(motorL2, 0);
}
int ultsnd()
{
  digitalWrite(trigpin,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin,LOW);
  duration=pulseIn(echopin,HIGH);
  distance=duration*.03412;

  Serial.print("Distance: ");
  Serial.println(distance);
  
  return distance;
}

void Check_Protocol(char inStr[]){
int i=0;
int m=0;
Serial.println(inStr);
if(!strcmp(inStr,"forward"))
{ //Forward
  frwd();
for(m=0;m<11;m++){
inStr[m]=0;}
i=0;}
if(!strcmp(inStr,"backward"))
{ //backward
  bkwd();
for(m=0;m<11;m++){
inStr[m]=0;}
i=0;}
if(!strcmp(inStr,"right"))
{ //right
  rt();
for(m=0;m<11;m++){
inStr[m]=0;}
i=0;}
if(!strcmp(inStr,"left"))
{ //left
  lt();
for(m=0;m<11;m++){
inStr[m]=0;}
i=0;}

if(!strcmp(inStr,"stop"))
{ //stop
  stp();
for(m=0;m<11;m++){
inStr[m]=0;}
i=0;}

if(atoi(inStr)>=-90 && atoi(inStr)<=90)
{ //servo
  int pos=atoi(inStr);
  pos=map(pos,-90,90,255,0);
  myservo.write(pos);
for(m=0;m<11;m++){
inStr[m]=0;}
i=0;}

else{
for(m=0;m<11;m++){
inStr[m]=0;
}
i=0;
}}

void setup(){
    pinMode(2, OUTPUT);
  digitalWrite(2 , HIGH);
  pinMode(powpin,OUTPUT);
  digitalWrite(powpin,HIGH);
Serial.begin(9600);
pinMode(tx, OUTPUT);
pinMode(rx, INPUT);
}
void loop(){
int i=0;
int m=0;
myservo.attach(10);
delay(500);
if (Serial.available() > 0) {
  Serial.println("Available");
while (Serial.available() > 0) {
inSerial[i]=Serial.read();
i++;
Serial.println(i);
}
inSerial[i]='\0';
//Check_Protocol(inSerial);
}
//Serial.print(distance);
}



