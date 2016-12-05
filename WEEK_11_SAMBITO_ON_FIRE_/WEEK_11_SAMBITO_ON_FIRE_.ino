////SERVO+SENSOR
#include <Servo.h>
#include <CapacitiveSensor.h>

int led = 13;

Servo myservo;
int inc = 10;
int pos = 11;
int para;
int cm; //distancia sensor
int bestValue = 10000; //millor distancia sensor
int best;
const int EchoPin = 5;
const int TriggerPin = 6;

int  bestPosition;

/////MOTOR
#define VELOCIDAD 3500

int steps = 7;
int direccion = 3;
int reset = 12;
int pasos = 200;
int moviments = 3500;
int Po = 0;
int dir = 1;
int convert;
int deplacament;
int diferencia;
int i = 1;
int BState = 1;
int button = 8;


////LEDS
int  brightnessValue = 0;
int fadeAmount = 20;
int ledBe = 10;
int ledMal = 11;

////CAPACITIVE SENSOR

CapacitiveSensor cs_4_2 = CapacitiveSensor(4, 2);

// the setup routine runs once when you press reset:
void setup() {

  pinMode(led, OUTPUT);

  ///SERVO+SENSOR
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(pos);

  pinMode(TriggerPin, OUTPUT);
  pinMode(EchoPin, INPUT);

  /// MOTOR
  pinMode(steps, OUTPUT);
  pinMode(direccion, OUTPUT);
  pinMode(reset, OUTPUT);

  pinMode(button, INPUT_PULLUP);

  //Posicio inici
  digitalWrite(reset, LOW);    //Mientras reset este en LOW el motor permanecerá apagado y no sufrirá. El chip apagará todos los puertos y no leerá comandos.
  delayMicroseconds(100);
  digitalWrite(reset, HIGH);   //Cuando reset se encuentre en HIGH el motor arrancará y leerá los comandos enviados.
  digitalWrite(direccion, dir);

  while (BState == 1) { //mentre no s'apreti el botó gira 1 pas i llegeix el botó.

    digitalWrite(steps, HIGH);  // This LOW to HIGH change is what creates the
    delayMicroseconds(100);
    digitalWrite(steps, LOW); // al A4988 de avanzar una vez por cada pulso de energia.
    delayMicroseconds(VELOCIDAD * 2); // Regula la velocidad, cuanto mas bajo mas velocidad.
    BState = digitalRead(button);

  }

  /////LEDS
  pinMode(ledBe, OUTPUT); // Pin PWM para regular la base del transistor
  pinMode(ledMal, OUTPUT);


  ////CAPACITIVE SENSOR
  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);

  Serial.println("Iniciando la fuente");
}

void loop() {
  Sensor();
  //Motor();
  // leds();
  // touch();
}

void Sensor() {
  if (millis() % 200 == 0) { // Cada 500ms:

    //LLEGEIX
    cm = ping(TriggerPin, EchoPin); //mira distància: renova el valor
    // Serial.println(cm);
    
    if (pos >= 170 || pos <= 10) {//si està al final del recorregut
      inc = -inc; //inverteix la direcció
      bestPosition = best; //guarda la posició on hi ha una persona més propera de la 1/2 volta
      bestValue = 10000;
      Serial.print("bestPos ");
      Serial.println(bestPosition);
      Motor();
    }

    //ES MOU
    pos += inc; //incrementa la posició
    //Serial.println(pos);
    // mou el servo fins la posició

    //COMPARA
    if (bestValue > cm) { //compara el valor antic amb l'actual. Si la distància actual és més propera...
      bestValue = cm; // renova la millor distància
      best = pos; // renova la posició amb la millor distància
      Serial.print("Value ");
      Serial.println(bestValue);
    }

    //
    myservo.write(pos);
    // delay(1);
    delayMicroseconds(100);
  }
}


void Motor() {

  moviments = map( bestPosition, 10, 170, 0, 89); //Converteix els graus del servo a passos per l'stepper. Del rang de 160º del servo als equivalents 89 passos de 200.
  diferencia = moviments - Po; //número de passos + o -
  if (diferencia > 0) { //assigna direcció
    dir = 1;
  } if (diferencia <= 0) {
    dir = 0;
  }

  int desplacament = abs(diferencia);
  //MOU STEPPER
  digitalWrite(direccion, dir);
  while (desplacament >= i - 1) {
    digitalWrite(steps, HIGH);
    digitalWrite(steps, LOW);
    i++;
    Serial.print("sambitou! ");
    Serial.println(moviments);
  }
  Po = desplacament ; //renovem posició inici
  i = 1; //refresquem valor

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
  constrain(brightnessValue, 0, 255); //limitem la intensitat de la llum

  if (micros() % 500 == 0) { //cada 1/2ms...
    brightnessValue = brightnessValue + fadeAmount; //agumentem o disminuim 20

    if (cm < 50) { //il·luminem la imatge bona
      Serial.println("good");

      analogWrite(ledBe,  brightnessValue);
      analogWrite(ledMal, 0);
      //Serial.println(fadeAmount);
    }  else if (cm > 50) {
      Serial.println("bad");
      analogWrite(ledMal,  brightnessValue);
      analogWrite(ledBe,  0);
      //Serial.println(fadeAmount);
    }
  }

  if (brightnessValue >= 255 || brightnessValue <= 0) {
    fadeAmount = -fadeAmount;
  }

}


void touch() {
  long start = millis();
  long total1 = cs_4_2.capacitiveSensor(30);

  Serial.print(millis() - start);
  Serial.print("\t");

  Serial.println(total1);

  delay(10);

  if (total1 > 600) {
    digitalWrite(ledBe, brightnessValue);
    digitalWrite(ledMal, 0);
  } else {
    digitalWrite(ledMal, brightnessValue);
    digitalWrite(ledBe, 0);
  }
}

