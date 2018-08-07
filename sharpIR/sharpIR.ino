#define sensor A0 // Sharp IR GP2Y0A41SK0F (4-30cm, analog)

void setup() {
  Serial.begin(9600); // start the serial port
  pinMode(2,OUTPUT);
}

void loop() {
  digitalWrite(2,HIGH);
  // 5v
  float volts = analogRead(sensor)*0.0048828125;  // value from sensor * (5/1024)
  int distance = 13*pow(volts, -1); // worked out from datasheet graph
  delay(1000); // slow down serial port 
  
  if (distance <= 30){
    Serial.println(distance);   // print the distance
  }
}
