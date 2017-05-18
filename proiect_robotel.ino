#include <IRremote.h>

#define trigPin 10
#define echoPin 8
#define led1 0
#define led2 1
#define led3 2
#define buzzer 7
#define RECV_PIN1 11
#define RECV_PIN2 4
#define MOTOR2_PIN1 3
#define MOTOR2_PIN2 5
#define MOTOR1_PIN1 6
#define MOTOR1_PIN2 9
#define ledS 12 //semnalizare stanga
#define ledD 13 //semnalizare dreapta
#define sound 300

IRrecv irrecv1(RECV_PIN1);
IRrecv irrecv2(RECV_PIN2);
decode_results results;

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(ledS, OUTPUT);
  pinMode(ledD, OUTPUT);
  pinMode(MOTOR1_PIN1, OUTPUT);
  pinMode(MOTOR1_PIN2, OUTPUT);
  pinMode(MOTOR2_PIN1, OUTPUT);
  pinMode(MOTOR2_PIN2, OUTPUT);
  irrecv1.enableIRIn(); // Start the receiver
  irrecv2.enableIRIn(); // Start the receiver
  Serial.begin(9600);
}

void blink(int led){

  digitalWrite(led, HIGH);   
  delay(500);                       
  digitalWrite(led, LOW);   
  delay(500);                       
}

//void myTone(byte pin, uint16_t frequency, uint16_t duration)
void myTone(byte pin, uint16_t frequency)
{
  unsigned long startTime=millis();
  unsigned long halfPeriod= 1000000L/frequency/2;
  pinMode(pin,OUTPUT);
//  while (millis()-startTime< duration)
//  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin,LOW);
    delayMicroseconds(halfPeriod);
  //}
  pinMode(pin,INPUT);
}

void go(int speedLeft, int speedRight) {
  if (speedLeft > 0) {
    analogWrite(MOTOR1_PIN1, speedLeft);
    analogWrite(MOTOR1_PIN2, 0);
  } 
  else {
    analogWrite(MOTOR1_PIN1, 0);
    analogWrite(MOTOR1_PIN2, -speedLeft);
  }
 
  if (speedRight > 0) {
    analogWrite(MOTOR2_PIN1, speedRight);
    analogWrite(MOTOR2_PIN2, 0);
  }else {
    analogWrite(MOTOR2_PIN1, 0);
    analogWrite(MOTOR2_PIN2, -speedRight);
  }
}

void directii(){
  if( (results.value == 1033561079) || (results.value == 718639610))
      go(255,255);
  if( (results.value == 465573243) || (results.value == 16730805))
      go(-255,-255);
  if( (results.value == 71952287) || (results.value == 16734885))
      {
        go(150,255);
        blink(ledD);
        blink(ledD);
        blink(ledD);
      }
  if( (results.value == 2351064443) || (results.value == 16716015))
      {
        go(255,200);
        blink(ledS);
        blink(ledS);
        blink(ledS);       
      }
  if( (results.value == 3855596927) || (results.value == 1701525988))
      go(0,0);
}

void loop() {

  long duration, distance, distance1;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration/2) / 29.1; //range 0-30
  distance1 = 8;
  
 if (distance <= 7) {
   go(0,0);
   myTone(buzzer,sound);
   distance1 = distance; 
  }
 else{
    if (distance1 <= 7) go(255,200);
    myTone(buzzer,0);
    }
  
  if ((irrecv1.decode(&results)) || (irrecv2.decode(&results))){
      /*
    switch (results.value) {
      case 1033561079:
        go(255,255);
        break;
      case 718639610:
        go(255,255);
        break;
      case 465573243:
        go(-255,-255);
        break;
      case 16730805:
        go(-255,-255);
        break;
      case 71952287:
        go(150,255);
        blink(ledS);
        blink(ledS);
        blink(ledS);
        break;
      case 16734885:
        go(150,255);
        blink(ledS);
        blink(ledS);
        blink(ledS);
        break;
      case 16716015:
        go(255,150);
        blink(ledD);
        blink(ledD);
        blink(ledD);
        break;
      case 2351064443:
        go(255,150);
        blink(ledD);
        blink(ledD);
        blink(ledD);
        break;
      default: 
        go(0,0);
      break; 
     }
*/
      directii();
      irrecv1.resume(); // Receive the next value
      irrecv2.resume(); // Receive the next value
      
    }
    //delay(100);
}


