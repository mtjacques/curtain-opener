#include <AccelStepper.h>

AccelStepper stepper(1, 6, 7);
const byte numChars = 32;

char recievedChars[numChars];

boolean newData = false;

char currentPlace = 'C';

void setup() {
  Serial.begin(9600);
  Serial3.begin(9600);
  stepper.setMaxSpeed(2200);
  stepper.setAcceleration(1100);
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
        if (stepper.distanceToGo() == 0) {
        stepper.moveTo(41000);
                currentPlace = 'O';
        }
        stepper.run();
      }
      else if (currentPlace == 'H') {
        if (stepper.distanceToGo() == 0) {
        stepper.moveTo(41000);
                currentPlace = 'O';
        }

        stepper.run();;
      }
      else if (currentPlace == 'O') {
        Serial.println("Curtain is already Open");
        stepper.run();
      }
    }
    else if (letter == 'C') {
      if (currentPlace == 'O') {
        if (stepper.distanceToGo() == 0) {
          stepper.moveTo(0);
                    currentPlace = 'C';
        }

          stepper.run();
      }
      else if (currentPlace == 'H') {
        if (stepper.distanceToGo() == 0) {
        stepper.moveTo(0);
                currentPlace = 'C';
        }

        stepper.run();      
      }
      else if (currentPlace == 'C') {
        Serial.println("Curtain is already Closed");
        stepper.run();
      }
    }
    else if (letter == 'H') {
      if (currentPlace == 'O') {
        if (stepper.distanceToGo() == 0) {
            stepper.moveTo(20500);
                    currentPlace = 'H';
        }
        stepper.run();      
      }
      else if (currentPlace == 'C') {
        if (stepper.distanceToGo() == 0) {
        stepper.moveTo(20500);
                currentPlace = 'H';
        }
        stepper.run();
      }
      else if (currentPlace == 'H') {
        Serial.println("Curtain is already Halfway");
        stepper.run();
      }
    }
    newData = false;
  }
  stepper.run();
}

void loop() {
  recvWithEndMarker();
  spinMotor();
}
