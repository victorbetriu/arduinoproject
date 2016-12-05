#include <CapacitiveSensor.h>

CapacitiveSensor cs_4_2 = CapacitiveSensor(4,2);

int led1 = 3;

void setup() {
  // put your setup code here, to run once:

  cs_4_2.set_CS_AutocaL_Millis(0xFFFFFFFF);
  Serial.begin(9600);

  pinMode(led1, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  long start = millis();
  long total1 = cs_4_2.capacitiveSensor(30);

  Serial.print(millis() - start);
  Serial.print("\t");

  Serial.println(total1);

  delay(10);

  if(total1 > 600){
    digitalWrite(led1, HIGH);
  } else {
    digitalWrite(led1, LOW);
  }
 
}
