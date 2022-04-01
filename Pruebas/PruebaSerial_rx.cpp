#include <ArduinoJson.h>
#include <UIPEthernet.h>

String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
 
void setup() {
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  Serial.begin(9600);
  inputString.reserve(200);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);

}
 
void loop() {
  if (stringComplete) {
    Serial.println("Se recibió: " + inputString);
    if (inputString == "LedRedON_") {
        Serial.println("Enviando Rojo");
        digitalWrite(8, HIGH);
    }
    else if (inputString == "LedRedOFF_") {
      digitalWrite(8, LOW);
    }
    if (inputString == "LedGreenON_") {
      Serial.println("Enviando Verde");
      digitalWrite(7, HIGH);
    }
    else if (inputString == "LedGreenOFF_") {
      digitalWrite(7, LOW);
    }
    inputString = "";
    stringComplete = false;
    
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '_') {
      stringComplete = true;
    }
  }
}