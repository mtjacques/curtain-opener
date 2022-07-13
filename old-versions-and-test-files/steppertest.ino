const int stepPin = 6;
const int dirPin = 7;
const int enPin = 8;

void setup() {

  pinMode(stepPin,OUTPUT);
  pinMode(dirPin,OUTPUT);
  pinMode(enPin,OUTPUT);
  digitalWrite(enPin,LOW);
}

void loop() {
  digitalWrite(dirPin,HIGH);

  for(int x = 0; x < 800; x++) {
    digitalWrite(stepPin,HIGH);
    delayMicroseconds(500);
    digitalWrite(stepPin,LOW);
    delayMicroseconds(500);
    
  }
  delay(1000);

  
}
