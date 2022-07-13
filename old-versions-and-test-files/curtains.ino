#include "IRremote.h"

int receiver = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11


IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'


#define ENABLE 5
#define DIRA 3
#define DIRB 4

int i;

void setup() {
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver

  pinMode(ENABLE,OUTPUT);
  pinMode(DIRA,OUTPUT);
  pinMode(DIRB,OUTPUT);
}

void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{
  String input;
  switch(results.value)

  {
  case 0xFFA25D: Serial.println("POWER"); input = "POWER"; break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); input = "FUNC/STOP";break;
  case 0xFF629D: Serial.println("VOL+"); input = "VOL+";break;
  case 0xFF22DD: Serial.println("FAST BACK");  input = "FAST BACK";  break;
  case 0xFF02FD: Serial.println("PAUSE");  input = "PAUSE";  break;
  case 0xFFC23D: Serial.println("FAST FORWARD"); input = "FAST FORWARD";  break;
  case 0xFFE01F: Serial.println("DOWN");  input = "DOWN";  break;
  case 0xFFA857: Serial.println("VOL-");  input = "VOL-";  break;
  case 0xFF906F: Serial.println("UP");   input = "UP"; break;
  case 0xFF9867: Serial.println("EQ");   input = "EQ"; break;
  case 0xFFB04F: Serial.println("ST/REPT");  input = "ST/REPAIR";  break;
  case 0xFF6897: Serial.println("0");  input = "0" ; break;
  case 0xFF30CF: Serial.println("1");      Serial.println("One way, then reverse");
    digitalWrite(ENABLE,HIGH); // enable on
    for (i=0;i<5;i++) {
    digitalWrite(DIRA,HIGH); //one way
    digitalWrite(DIRB,LOW);
    delay(500);
    digitalWrite(DIRA,LOW);  //reverse
    digitalWrite(DIRB,HIGH);
    delay(500);
  }
  digitalWrite(ENABLE,LOW); // disable
  delay(2000);  break;
  case 0xFF18E7: Serial.println("2") ;  Serial.println("fast Slow example");
  //---fast/slow stop example
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(3000);
  digitalWrite(ENABLE,LOW); //slow stop
  delay(1000);
  digitalWrite(ENABLE,HIGH); //enable on
  digitalWrite(DIRA,LOW); //one way
  digitalWrite(DIRB,HIGH);
  delay(3000);
  digitalWrite(DIRA,LOW); //fast stop
  delay(2000); break;
  case 0xFF7A85: Serial.println("3");    Serial.println("PWM full then slow");
  //---PWM example, full speed then slow
  analogWrite(ENABLE,255); //enable on
  digitalWrite(DIRA,HIGH); //one way
  digitalWrite(DIRB,LOW);
  delay(2000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,50); //half speed
  delay(2000);
  analogWrite(ENABLE,128); //half speed
  delay(2000);
  analogWrite(ENABLE,180); //half speed
  delay(2000);
  analogWrite(ENABLE,255); //half speed
  delay(2000);
  digitalWrite(ENABLE,LOW); //all done
  delay(10000); break;
  case 0xFF10EF: Serial.println("4"); break;
  case 0xFF38C7: Serial.println("5");  input = "5"  ;break;
  case 0xFF5AA5: Serial.println("6");  input = "6" ; break;
  case 0xFF42BD: Serial.println("7");  input = "7" ; break;
  case 0xFF4AB5: Serial.println("8");  input = "8";  break;
  case 0xFF52AD: Serial.println("9");  input = "9";  break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case
  delay(500); // Do not get immediate repeat
  return input;

} //END translateIR


void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  if (irrecv.decode(&results)) // have we received an IR signal?

  {
        translateIR(); 

    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */
