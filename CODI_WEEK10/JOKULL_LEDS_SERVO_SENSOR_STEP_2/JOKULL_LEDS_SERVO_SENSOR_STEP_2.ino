////SERVO+SENSOR
#include <Servo.h>

Servo myservo;
int inc = 10;
int pos=11;
int para;
int cm; //distancia sensor
int bestValue; //millor distancia sensor
int best;
const int EchoPin = 5;
const int TriggerPin = 6;


/////MOTOR
#define VELOCIDAD 3500

int steps = 2;
int direccion = 3;
int reset = 12;
int pasos = 200;
int moviments = 3500;
int Po = 0;
int dir = 1;
int convert;
int deplacament;
int diferencia;
int i = 0;
int BState = 1;
int button = 8;


////LEDS
int  brightnessValue = 0;
int fadeAmount = 20;
int ledBe = 10;
int ledMal = 11;




// the setup routine runs once when you press reset:
void setup() {

  ///SERVO+SENSOR
  Serial.begin(9600);
  myservo.attach(9);
myservo.write(11);

  //pinMode(LedPin, OUTPUT);
  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  /// MOTOR
  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);
  pinMode(reset, OUTPUT);

  //pinMode(button, INPUT_PULLUP);

  //Posicio inici

  digitalWrite(reset, LOW);    //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delayMicroseconds(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  digitalWrite(direccion, dir);


  while (BState == 1) {
    digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
    delayMicroseconds(100);
    digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
    delayMicroseconds(VELOCIDAD * 2); // Regula la velocidad, cuanto mas bajo mas velocidad.
    BState = digitalRead(button);
  }




  /////LEDS
  pinMode(ledBe, OUTPUT); // Pin PWM para regular la base del transistor
  pinMode(ledMal, OUTPUT);

  Serial.println("Iniciando la fuente");
}

void loop() {
  Sensor();
  //Motor();
  //leds();
}

void Sensor() {
  if (millis() % 5 == 0) {
    // llegir
    // tell servo to go to position in variable 'pos'
    cm = bestValue; //inicialitza el valor
    //Serial.print(bestValue);

    cm = ping(TriggerPin, EchoPin);
    //Serial.print("Distancia: ");
    //Serial.println(cm);

  if (pos >= 170 || pos <= 10) {
    inc = -inc;
  }
    // new pos... escriure...
    pos += inc;
    //Serial.println(pos);


    myservo.write(pos);

    if (bestValue > cm) {
      bestValue = cm;
      best = pos;
    }

    Serial.print("cm ");
    Serial.println(cm);
    delay(1);
  }


}


void Motor() {

  if (millis() % 80 == 0) {
    moviments = map(best, 10, 170, 0, 89); //Converteix els graus del servo a passos per l'stepper. Del rang de 160º del servo als equivalents 89 passos de 200.
    diferencia = moviments - Po;
    if (diferencia > 0) { //direcció
      dir = 1;
    } if (diferencia <= 0) {
      dir = 0;
    }

    int desplacament = abs(diferencia);

    //Refresquem els valor

    Po = moviments;
    bestValue = 10000;

  }

  digitalWrite(direccion, dir);
  while (abs(diferencia) > i) {

    digitalWrite(steps, HIGH);
    digitalWrite(steps, LOW);
    i++;
  }

  i = 0;

  ///// RESET DEL MOTOR
  //  digitalWrite(reset, LOW);    //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  //  delayMicroseconds(100);
  //  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  //  digitalWrite(direccion, dir);

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


void leds() {
  constrain(brightnessValue, 0, 255);

  if (micros() % 5000 == 0) {
    brightnessValue = brightnessValue + fadeAmount;

    if (cm < 50) {
      Serial.println("FUNCIONA");

      analogWrite(ledBe,  brightnessValue);
      //Serial.println(fadeAmount);
    }  else {
      //Serial.println("HOLA");
      analogWrite(ledMal,  brightnessValue);
      //Serial.println(fadeAmount);
    }
  }

  if (brightnessValue >= 255 || brightnessValue <= 0) {
    fadeAmount = -fadeAmount;
  }

}


