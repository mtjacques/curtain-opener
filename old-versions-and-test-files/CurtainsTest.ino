

#define ENABLE 5
#define DIRA 3
#define DIRB 4

char currentPlace = 'C';


void setup() {
Serial.begin(9600);
Serial3.begin(9600);

pinMode(ENABLE, OUTPUT);
pinMode(DIRA, OUTPUT);
pinMode(DIRB, OUTPUT);
Serial.println("Starting");
delay(5000);
}

void spinMotor() {

    String IncomingString = "";
    char letter;
boolean StringReady = false;

while (Serial3.available()) {
  IncomingString = Serial3.readString();
  StringReady = true;
}

if (StringReady) {
  Serial.println(IncomingString);
  letter = IncomingString.charAt(7);
  }
if (letter == 'O') {
        if (currentPlace == 'C'){
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB, LOW);
        delay(3000);
        digitalWrite(ENABLE, LOW);
        currentPlace = 'O';
        return;
      }

      else if(currentPlace == 'H') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB, LOW);
        delay(1500);
        digitalWrite(ENABLE, LOW);
        currentPlace = 'O';
        return;
      }

      else if(currentPlace == 'O') {
        Serial.println("Curtain is already open");
        return;
      }
}

if (IncomingString == 'C') {
if (currentPlace == 'O'){
          digitalWrite(ENABLE, HIGH);
          digitalWrite(DIRA, LOW);
          digitalWrite(DIRB, HIGH);
          delay(3000);
          digitalWrite(ENABLE, LOW);
        currentPlace = 'C';
        return;
      }

      else if(currentPlace == 'H') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, LOW);
        digitalWrite(DIRB, HIGH);
        delay(1500);
        digitalWrite(ENABLE, LOW);
        currentPlace = 'C';
        return;
      }

      else if(currentPlace == 'C') {
        Serial.println("Curtain is already closed");
        return;
      }
  }

 if (IncomingString == 'H'){
if (currentPlace == 'O'){
          digitalWrite(ENABLE, HIGH);
          digitalWrite(DIRA, LOW);
          digitalWrite(DIRB, HIGH);
          delay(1500);
          digitalWrite(ENABLE, LOW);
        currentPlace = 'H';
        return;
      }

      else if(currentPlace == 'C') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB, LOW);
        delay(1500);
        digitalWrite(ENABLE, LOW);
        currentPlace = 'H';
        return;
      }

      else if(currentPlace == 'H') {
        Serial.println("Curtain is already halfway");
        return;
      }
    
  }
  Serial.println(currentPlace);
  return;
}

void loop() {
//  String IncomingString = "";
//boolean StringReady = false;

//while (Serial3.available()) {
  //IncomingString = Serial3.readString();
 // StringReady = true;
//}

//if (StringReady) {
  //Serial.println(IncomingString);
  //spinMotor(IncomingString);
  //Serial.println(currentPlace);
//}
while (Serial3.available()) {
  spinMotor();
}

}
