int  brightnessValue = 0;
int fadeAmount = 20;

void setup()
{ Serial.begin(9600);



  pinMode( 10, OUTPUT);      // Pin PWM para regular la base del transistor

  delay(1000);   // Pequeño retraso para asegurarnos de que la tension es estable
  Serial.println("Iniciando la fuente");
}

void loop() {
  constrain(brightnessValue, 0, 255);
  if (millis() % 1 == 0) {

   brightnessValue = brightnessValue + fadeAmount;
    delay(1);
  }

int clau = 510/fadeAmount;

  if (millis() % clau >= 0) {
    if (brightnessValue >= 255 || brightnessValue <= 0) {
      fadeAmount = -fadeAmount;
    }
    delay(1);
  }




  analogWrite(10,  brightnessValue);
  Serial.println(fadeAmount);
}


