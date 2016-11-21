int brightnessValue;
int pinLeds = 3;

void setup() {
  Serial.begin(9600);
  pinMode( pinLeds, OUTPUT);      // Pin PWM para regular la base del transistor
  delay(1000);   // Pequeño retraso para asegurarnos de que la tension es estable
  Serial.println("Iniciando la fuente");
}

void loop() {
  constrain(brightnessValue, 0, 255);

  if (millis() % 1 == 0) {
    if (millis() % 560 < 256) {
      brightnessValue ++;
      delay(1);
    }
    if (millis() % 560 > 255) {
      brightnessValue --;
      delay(1);
    }
    delay(1);
  }
  /* if (millis() % 500 == 0,5) {
     brightnessValue --;
     delay(10);
    }*/
  analogWrite(pinLeds, brightnessValue);
}
