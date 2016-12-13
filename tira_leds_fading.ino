int brightnessValue;
int ledPin = 3;

void setup()
{ Serial.begin(9600);
  pinMode( ledPin, OUTPUT); 
  delay(1000);   // Pequeño retraso para asegurarnos de que la tension es estable
  Serial.println("Iniciando la fuente");
}

void loop() {
  constrain(brightnessValue, 0, 255); //limit the value (0 - 255)
  //INCREASE THE BRIGHTNESS
  if (millis() % 1 == 0) { //Everytime...
    if (millis() % 560 < 256) { //If the residu is lower than 256 (max. brightess value of a led)
      brightnessValue ++; //increase 1 the brightness
      delay(1); //do it once per milli
    }
    //DECREASE THE BRIGHTNESS
    if (millis() % 560 > 255) { //If the residu is higher than 255...
      brightnessValue --; //decrease 1 the brightness
      delay(1); 
    }
    delay(1);
  }
  analogWrite(pinLeds, brightnessValue); //Make led show the corresponent brightness
}



