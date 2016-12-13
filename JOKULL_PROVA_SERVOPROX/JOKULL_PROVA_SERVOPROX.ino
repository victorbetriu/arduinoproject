#include <Servo.h>

const int trigPin = 6;
const int echoPin = 5;
Servo myservo;
int pos;
int para;
int cm;
int bestValue;
int best;

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  Serial.print("Start");
  for (pos = 10; pos <= 170; pos += 5) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);       // tell servo to go to position in variable 'pos'
    cm = bestValue;
    cm = ping(TriggerPin, EchoPin);
    Serial.print("Distancia: ");
    Serial.println(cm);
    delay(5);

    if (bestValue > cm) {
      bestValue = cm;
      best = pos;
    }
  }

  // back to start
  myservo.write(best);              // tell servo to go to position in variable 'pos'
  delay(1000);
  bestValue = 1000000;
  Serial.println(best);
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
