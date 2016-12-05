////SERVO+SENSOR
#include <Servo.h>

Servo myservo;
int inc = 10;
int pos = 11;
int para;
int cm; //distancia sensor
int bestValue; //millor distancia sensor
int best;
const int EchoPin = 5;
const int TriggerPin = 6;
//const int LedPin = 13;


/////MOTOR
#define VELOCIDAD 3500


int steps = 2;
int direccion = 3;
int reset = 12;
int pasos = 200;
int moviments = 3500;
int Po = 0;
int i=1;


int dir = 1;
int convert;

int button = 8;
int buttonState = 1;

// the setup routine runs once when you press reset:
void setup() {

  ///SERVO+SENSOR
  Serial.begin(9600);
  myservo.attach(9);

  //pinMode(LedPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  /// MOTOR
  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);
  pinMode(reset, OUTPUT);
  pinMode(button, INPUT_PULLUP);

  //Posicio inici

  digitalWrite(reset, LOW);    //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delay(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  digitalWrite(direccion, dir);
  while (buttonState == 1) {
    i++;   //Equivale al numero de vueltas (200 es 360º grados) o micropasos
    digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
    digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
    delayMicroseconds(VELOCIDAD * 2); // Regula la velocidad, cuanto mas bajo mas velocidad.

    buttonState = digitalRead(button);
  }
}

void loop() {
  Sensor();
}

void Sensor() {

  if (millis() % 5 == 0) {
    // llegir
    // tell servo to go to position in variable 'pos'
    cm = bestValue; //inicialitza el valor
    Serial.print(bestValue);

    cm = ping(TriggerPin, EchoPin);
    Serial.print("Distancia: ");
    Serial.println(cm);
    delay(1000);

    // new pos... escriure...
    pos += inc;
    Serial.println(pos);
    if (pos > 170 || pos < 10) {
      inc = -inc;
      Motor();
    }

    myservo.write(pos);

    if (bestValue > cm) {
      bestValue = cm;
      best = pos;
    }

    // Serial.println(bestValue);
  }
  //  for (pos = 10; pos <= 170; pos += 5) { // goes from 0 degrees to 180 degrees
  // in steps of 1 degree


  //  Serial.println(best);
}

void Motor() {
  moviments = map(best, 10, 170, 0, 200);
  int diferencia = moviments - Po;
  if (diferencia > 0) {
    dir = 1;
  } if (diferencia <= 0) {
    dir = 0;
  }
  digitalWrite(reset, LOW);    //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delay(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  digitalWrite(direccion, dir);

  int desplacament = abs(diferencia);

  for (int i = 0; i < desplacament; i++)     //Equivale al numero de vueltas (200 es 360º grados) o micropasos
  {
    digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
    digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
    delayMicroseconds(VELOCIDAD);     // Regula la velocidad, cuanto mas bajo mas velocidad.

  }
  Po = moviments;
  bestValue = 10000;
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





