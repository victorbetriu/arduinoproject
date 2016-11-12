

long distance;
long time;

#define ledPin        6
#define stripPin      2

int outState = LOW;
long previousMillis = 0;

long interval = 1000;

void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT); //Activación del pin 9 como salida: emisión del pulso ultraso.
  pinMode(8, INPUT); //Activación del pin 8 como entrada: tiempo del rebote del pulso.


  pinMode(ledPin, OUTPUT);
  pinMode(stripPin, OUTPUT);  
}

void loop(){


  digitalWrite(9, LOW); //Estabilización del sensor
  delayMicroseconds(5);
  digitalWrite(9, HIGH); //Envío del pulso ultrasónico
  delayMicroseconds(10);


  time = pulseIn(8, HIGH); //Función para medir la longitud del pulso entrante. Mide el tiempo que ha transcurrido entre el envío del pulso ultrasónico y cuendo el sensor recibe el rebote. 


  distance = int(0.017*time); // Fórmula para calcular la distancia obteniendo un valor entero


  //Serial.println(“Distancia  ”); //Monitorización en centímetros
  Serial.println(distance);
//  Serial.println(“  cm”);
  delay(1000);

///////////////////////////////////////
///////////////////////////////////////

  int proxValue = analogRead(distance);
  interval = map(proxValue, 30, 3000, 50, 2000);  
  
  unsigned long currentMillis = millis();
 
  if(currentMillis - previousMillis > interval) {

    previousMillis = currentMillis;   

    if (outState == LOW)
      outState = HIGH;
    else
      outState = LOW;

    digitalWrite(ledPin, outState);
    digitalWrite(stripPin, outState);
  }


  
}
