#include <ArduinoJson.h>
#include <UIPEthernet.h>
//////////// declaración de entradas ///////////////////
const int Pul_0=3;
const int Pul_1=4;
const int Pul_2=5;
const int Pul_3=6;
const int Switch_0=7;
const int Switch_1=8;
const int Switch_2=9;
const int Switch_3=10;

void setup() {
// declaro tipo salidas  
  pinMode(Pul_0, INPUT);
  pinMode(Pul_1, INPUT);
  pinMode(Pul_2, INPUT);
  pinMode(Pul_3, INPUT);
  pinMode(Switch_0, INPUT);
  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
  pinMode(Switch_3, INPUT);
  Serial.begin(115200);
}
 
void loop() {
  delay(5000);
  Serial.println("Pulsadores: ");
  if(digitalRead(Pul_0)) Serial.println(" Pulsador 0: ON");
  else Serial.println(" Pulsador 0: OFF");
  if(digitalRead(Pul_1)) Serial.println(" Pulsador 1: ON");
  else Serial.println(" Pulsador 1: OFF");
  if(digitalRead(Pul_2)) Serial.println(" Pulsador 2: ON");
  else Serial.println(" Pulsador 2: OFF");
  if(digitalRead(Pul_3)) Serial.println(" Pulsador 3: ON");
  else Serial.println(" Pulsador 3: OFF");
  Serial.println("Llaves: ");
  if(digitalRead(Switch_0)) Serial.println("  Llave 0: ON");
  else Serial.println(" Llave 0: OFF");
  if(digitalRead(Switch_1)) Serial.println("  Llave 1: ON");
  else Serial.println(" Llave 1: OFF");
  if(digitalRead(Switch_2)) Serial.println("  Llave 2: ON");
  else Serial.println(" Llave 2: OFF");
  if(digitalRead(Switch_3)) Serial.println("  Llave 3: ON");
  else Serial.println(" Llave 3: OFF");
  Serial.println("_");  
}
