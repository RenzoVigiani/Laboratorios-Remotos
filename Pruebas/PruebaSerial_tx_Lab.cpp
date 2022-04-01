#include <ArduinoJson.h>
#include <UIPEthernet.h>

const int Led_0=4;
const int Led_1=5;
const int pul_0=2;
const int pul_1=3;
void setup() {
  pinMode(Led_0, OUTPUT);
  pinMode(Led_1, OUTPUT);
  digitalWrite(Led_0,LOW);
  digitalWrite(Led_1,LOW);
  Serial.begin(9600);
}
 
void loop() {
  if(pul_0==HIGH){
    digitalWrite(Led_0,HIGH);
    Serial.print("LedRedON_");
    delay(2000);
  }
  else{
    digitalWrite(Led_0,LOW);
    Serial.print("LedRedOFF_");
    delay(2000);
  }   
  if(pul_1==HIGH){
    digitalWrite(Led_1,HIGH);
    Serial.print("LedGreenON_");
    delay(2000);
  }
  else{
    digitalWrite(Led_1,LOW);
    Serial.print("LedGreenOFF_");
    delay(2000);
  } 
}