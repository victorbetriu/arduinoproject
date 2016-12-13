int ledPin = 3;

void setup()
{ Serial.begin(9600);
  pinMode( ledPin, OUTPUT); 
  delay(1000);   // Pequeño retraso para asegurarnos de que la tension es estable
  Serial.println("Iniciando la fuente");
}

void loop() {
  if (millis() % 1000 == 0) {
    for (int i = 0; i < 256; i++) {
      analogWrite (6, i);
    }
  } 
  if (millis()%1000==500){
     for(int i=255; i>0;i--){
      analogWrite(6, i);
    }
  }  
}
