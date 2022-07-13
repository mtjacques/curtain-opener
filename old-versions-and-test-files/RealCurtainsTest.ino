#define ENABLE 5
#define DIRA 3
#define DIRB 4

const byte numChars = 32;

char recievedChars[numChars];

boolean newData = false;

char currentPlace = 'C';

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);

  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);
  Serial.println("Arduino is ready");
  delay(5000);

}

void recvWithEndMarker() {
  static byte i = 0;
  char endMarker = '\n';
  char rc;

  while (Serial3.available() > 0 && newData == false) {
    rc = Serial3.read();

    if (rc !=  endMarker) {
      recievedChars[i] = rc;
      i++;
      if (i >= numChars) {
        i = numChars - 1;
      }
    }
    else {
      recievedChars[i] = '\0';
      i = 0;
      newData = true;
    }
  }
}

void spinMotor() {
  if (newData == true) {
    Serial.println(recievedChars);

    char letter = recievedChars[7];
    if (letter == 'O') {
      if (currentPlace == 'C') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB, LOW);
        currentPlace = 'O';
        delay(3000);
        digitalWrite(ENABLE, LOW);
      }
      else if (currentPlace == 'H') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB, LOW);
        currentPlace = 'O';
        delay(1500);
        digitalWrite(ENABLE, LOW);
      }
      else if (currentPlace == 'O') {
        Serial.println("Curtain is already open");
      }
    }
    else if (letter == 'C') {
      if (currentPlace == 'O') {
          digitalWrite(ENABLE, HIGH);
          digitalWrite(DIRA, LOW);
          digitalWrite(DIRB, HIGH);
          currentPlace = 'C';
          delay(3000);
          digitalWrite(ENABLE, LOW);
      }
      else if (currentPlace == 'H') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, LOW);
        digitalWrite(DIRB, HIGH);
        currentPlace = 'C';
        delay(1500);
        digitalWrite(ENABLE, LOW);       
      }
      else if (currentPlace == 'C') {
        Serial.println("Curtain is already closed");
      }
    }
    else if (letter == 'H') {
      if (currentPlace == 'O') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, LOW);
        digitalWrite(DIRB, HIGH);
        currentPlace = 'H';
        delay(1500);
        digitalWrite(ENABLE, LOW);        
      }
      else if (currentPlace == 'C') {
        digitalWrite(ENABLE, HIGH);
        digitalWrite(DIRA, HIGH);
        digitalWrite(DIRB, LOW);
        currentPlace = 'H';
        delay(1500);
        digitalWrite(ENABLE, LOW);
      }
      else if (currentPlace == 'H') {
        Serial.println("Curtain is already halfway");
      }
    }
    else {
      Serial.println("Error: letter = " + letter);
    }
    newData = false;
  }
}

void loop() {
  recvWithEndMarker();
  spinMotor();
}
