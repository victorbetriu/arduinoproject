// AServo activated by an HC-SR04 via Arduino.
/*
  This sketch reads a HC-SR04 ultrasonic rangefinder and returns the
  distance to the closest object in range. To do this, it sends a pulse
  to the sensor to initiate a reading, then listens for a pulse
  to return. The length of the returning pulse is proportional to
  the distance of the object from the sensor.

  The Arduino then takes this information and initiates a series of
  sweeps. A sweep is defined as the servo moving its horn from the
  0 position to 180 and back to 0 then to -180 and back to 0.

  This code was developed partially from Ping))) code found in the
  public domain written by David A. Mellis, and adapted to the HC-SRO4
  by Tautvidas Sipavicius, servo code was provided the sweep example
  that is include in the Arduino IDE, while other portions were written
  by Charles Gantt and Curtis Gauger from
  http://www.themakersworkbench.com.

  This code was written for a tutorial on http://www.themakersworkbench.com,
  and was designed for use in a project built by
  The Young Makers of Greater Augusta.
*/

//Tell the Arduino Ide to include the Servo.h library.

#include <Servo.h>

const int trigPin = 6;
const int echoPin = 5;
Servo myservo;
int pos = 0;
int lastpos = 0;
int greenLed = 3, redLed = 2;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);// attaches the servo on pin 9 to the servo object
}

void loop() {
  // and the distance result in centimeters:
  long duration, cm;
  //ultrasensor working
  pinMode(trigPin, OUTPUT);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
  // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
//move the servo   
  if (distance <= 15)  {
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
  } else {
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH); 
  }

long microsecondsToCentimeters(long microseconds) {
return microseconds / 29 / 2;
}
}
