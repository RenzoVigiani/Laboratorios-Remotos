#include <ArduinoJson.h>
#include <UIPEthernet.h>
 
void setup() {
  Serial.begin(9600);
}
 
void loop() {
  Serial.print("LedRedON_");
  delay(2000);
  Serial.print("LedRedOFF_");
  delay(2000);
  Serial.print("LedGreenON_");
  delay(1000);
  Serial.print("LedGreenOFF_");
  delay(1000);
}