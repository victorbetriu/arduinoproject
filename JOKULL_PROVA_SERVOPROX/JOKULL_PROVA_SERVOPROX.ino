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



//Setup the variables for the HC-SR04

const int trigPin = 6;

const int echoPin = 5;

// create servo object to control a servo

// a maximum of eight servo objects can be created

Servo myservo;



// variable to store the servo position

int pos = 0;

int lastpos = 0;

void setup() {

  // initialize serial communication:

  Serial.begin(9600);



  // attaches the servo on pin 9 to the servo object

  myservo.attach(9);



}

void loop()

{

  // establish variables for duration of the ping,

  // and the distance result in inches and centimeters:

  long duration, cm;



  // The sensor is triggered by a HIGH pulse of 10 or
  // more microseconds.

  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:

  pinMode(trigPin, OUTPUT);

  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);



  // Read the signal from the sensor: a HIGH pulse whose

  // duration is the time (in microseconds) from the sending

  // of the ping to the reception of its echo off of an object.

  pinMode(echoPin, INPUT);

  duration = pulseIn(echoPin, HIGH);



  // convert the time into a distance

  cm = microsecondsToCentimeters(duration);



  //Tell the Arduino to print the measurement in the serial console

  Serial.print(cm);

  Serial.print("cm");

  Serial.println();



  // This if-else statement tells the Arduino at what distance

  // it should trigger the servo, what the servo should do,

  // and what it should do if the distance is too far away.

  if (cm <= 20) {
    myservo.write(pos);
  } else if (cm >= 20) {
    sweep();
  }



  // Tell the Arduino to wait 0.10 seconds before pinging the

  // Ultrasonic Sensor again.

  delay(100);

}

//Converts the Microseconds Reading to Centimeters

long microsecondsToCentimeters(long microseconds) {

  // The speed of sound is 340 m/s or 29 microseconds per centimeter.

  // The ping travels out and back, so to find the distance of the

  // object we take half of the distance travelled.

  return microseconds / 29 / 2;

}

//This sub-routein is what dictates the movement of the servo

void sweep() {
/*
  pos = lastpos;
 // pos = myservo.read();

  if (lastpos < pos && pos <= 170) {
    pos+=10;
    if(pos=170){
      p=1;
    }
  }

  if (lastpos > pos && pos >= 10) {
    pos-=10;
    if(pos=10){
      lastpos=9;
    }
  }

  myservo.write(pos);
*/

  // Tells the Arduino to start this loop at 0 and incriment it by 1

  // each time the loop completes. This is how the Arduino knows to

  // stop the loop when a specific number of the
  // Sweep routein has been ran.

  // goes from 0 degrees to 180 degrees
  for (pos = 10; pos < 170; pos += 1) {                // in steps of 1 degree
    // tell servo to go to position in variable 'pos'
    myservo.write(pos);
    // waits 15ms for the servo to reach the position delay(10); }
    // goes from 180 degrees to 0 degrees
    for (pos = 170; pos >= 11; pos -= 1) {
      // tell servo to go to position in variable 'pos'
      myservo.write(pos);
      // waits 15ms for the servo to reach the position
      delay(10);
    }
  }
  
}
