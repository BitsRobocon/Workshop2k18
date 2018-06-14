#define mxspd 255
#define factor=255/8

int mpin1=11;
int mpin2=10;
int mpin3=5;
int mpin4=6;

int spdf=mxspd;
int spdb=mxspd;

const int trigpin=3;
const int echopin=A0;

long duration;
int distance;

const int trigpin1=9;
const int echopin1=A1;

long duration1;
int distance1;
 
void frwd()
{
  analogWrite(mpin1,0);
  analogWrite(mpin2,spdf);
  analogWrite(mpin3,0);
  analogWrite(mpin4,spdf);
}
void bkwd()
{
  analogWrite(mpin2,0);
  analogWrite(mpin1,spdb);
  analogWrite(mpin4,0);
  analogWrite(mpin3,spdb);
}
void stp()
{
  analogWrite(mpin2,0);
  analogWrite(mpin1,0);
  analogWrite(mpin4,0);
  analogWrite(mpin3,0);
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
int ultsnd1()
{
  digitalWrite(trigpin1,LOW);
  delayMicroseconds(2);
  digitalWrite(trigpin1,HIGH);
  delayMicroseconds(10);
  digitalWrite(trigpin1,LOW); 
  duration1=pulseIn(echopin1,HIGH);
  distance1=duration1*.03412;

  Serial.print("Distance1: ");
  Serial.println(distance1);
  
  return distance1;
}
void setup() 
{    
  pinMode(mpin1,OUTPUT);
  pinMode(mpin2,OUTPUT);
  pinMode(mpin3,OUTPUT);
  pinMode(mpin4,OUTPUT);
  
  pinMode(trigpin,OUTPUT);
  pinMode(echopin,INPUT);
  pinMode(trigpin1,OUTPUT);
  pinMode(echopin1,INPUT);

  Serial.begin(9600);

}

void loop() {
  //frwd();
  if(ultsnd1()<10 or ultsnd()<10)
  {
    stp();
  }
  bkwd();

  
 

}

