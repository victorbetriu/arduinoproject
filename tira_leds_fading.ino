
void setup()
{ Serial.begin(9600);



  pinMode( 6, OUTPUT);      // Pin PWM para regular la base del transistor

  delay(1000);   // Pequeño retraso para asegurarnos de que la tension es estable
  Serial.println("Iniciando la fuente");
}

void loop() {
  if (millis() % 1000 == 0) {
    for (int i = 0; i < 256; i++) {
      analogWrite (6, i);       // Ponemos la tension de control
      int iinversa=map(i,0,255,255,0);
      analogWrite(6, iinversa);
      delay(1);
    }
  }

  
}

