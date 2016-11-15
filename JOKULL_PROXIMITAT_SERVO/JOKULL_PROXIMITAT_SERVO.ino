
#include <Servo.h>

Servo myservo;
int pos = 10;    // variable to store the servo position
int lastpos = 0; // variable to memorize the position

const int EchoPin = 5;
const int TriggerPin = 6;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {

  //pos = lastpos;

  int cm = ping(TriggerPin, EchoPin);
  Serial.print("Distancia: ");
  Serial.println(cm);
  delay(1000);

  if (cm > 20) {

    for (pos = 10; pos <= 170; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 170; pos >= 10; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(5);                       // waits 15ms for the servo to reach the position
    }
    
  }

  if (cm < 20) {
    myservo.write(pos);
    //myservo.read(9);
  }

}

int ping(int TriggerPin, int EchoPin) {
  long duration, distanceCm;

  digitalWrite(TriggerPin, LOW);  //para generar un pulso limpio ponemos a LOW 4us
  delayMicroseconds(4);
  digitalWrite(TriggerPin, HIGH);  //generamos Trigger (disparo) de 10us
  delayMicroseconds(10);
  digitalWrite(TriggerPin, LOW);

  duration = pulseIn(EchoPin, HIGH);  //medimos el tiempo entre pulsos, en microsegundos

  distanceCm = duration * 10 / 292 / 2;  //convertimos a distancia, en cm
  return distanceCm;
}
