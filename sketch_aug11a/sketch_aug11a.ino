int trigpin=12;
int echopin=13;
long duration;
int distance;
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

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
