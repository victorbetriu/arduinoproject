#include <NewPing.h>

#include <Servo.h>

#define trigPin 6

#define echoPin 5

#define MAX_DISTANCE 400



NewPing sonar(trigPin, echoPin, MAX_DISTANCE);



int greenLed = 3, redLed = 2;

//int pos = 20;


Servo myservo;


void setup() {

  Serial.begin (115200);

  pinMode(trigPin, OUTPUT);

  pinMode(echoPin, INPUT);

  pinMode(greenLed, OUTPUT);

  pinMode(redLed, OUTPUT);

  myservo.attach(9);

}



void loop() {

  int duration, distance, pos = 0, i;

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = (duration / 2) / 29.1;

  Serial.print(distance);

  Serial.println(" cm");



  if (distance <= 15)

  {

    digitalWrite(greenLed, LOW);

    digitalWrite(redLed, HIGH);

    myservo.write(170);

    delay(450);

    digitalWrite(redLed, LOW);

    myservo.write(90);

    delay(450);

    digitalWrite(redLed, HIGH);

    myservo.write(0);

    delay(450);

    digitalWrite(redLed, LOW);

    myservo.write(90);

  }

  else {

    digitalWrite(redLed, LOW);

    digitalWrite(greenLed, HIGH);

    myservo.write(90);

  }

  delay(450);

}
