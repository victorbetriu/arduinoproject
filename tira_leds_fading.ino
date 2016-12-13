int  brightnessValue;
int fadeAmount = 20;
int ledPin =3;

void setup()
{ Serial.begin(9600);
  pinMode( ledPin, OUTPUT); 
  delay(1000);   // Pequeño retraso para asegurarnos de que la tension es estable
  Serial.println("Iniciando la fuente");
}

void loop() {
  constrain(brightnessValue, 0, 255); //limit the value (0 - 255)
  //INCREASE or DECREASES THE BRIGHTNESS EVERY MILLI
  if (millis() % 1 == 0) {
   brightnessValue = brightnessValue + fadeAmount;
    delay(1);
  } 
   int clau = 510/fadeAmount; //255*2/fadeAmount: the millis when the brightness is max. or min.
  //CHANGE THE SIGN: + OR -
  if (millis() % clau >= 0) { //When brightess value is max. or min. it changes the sign
    if (brightnessValue >= 255 || brightnessValue <= 0) {
      fadeAmount = -fadeAmount;
    }
    delay(1);
  }
  analogWrite(10,  brightnessValue);
  Serial.println(fadeAmount);
}



