#include <ArduinoJson.h>
#include <UIPEthernet.h>
#include <SoftwareSerial.h>

//////////// declaración de GPIO ///////////////////
#define rxPin 3
#define txPin 4
//#define Pul_0  3
//#define Pul_1  4
#define Pul_2  5
#define Pul_3  6
#define Switch_0  7
#define Switch_1  8
#define Switch_2  9
//#define Switch_3  10
///////////////////////////////////////////////////
String inputString = "";         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
String recibido="";
String enviado="";
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

void mySerialFunction();

void setup() {
// declaro tipo salidas  
/*  pinMode(Pul_0, INPUT);
  pinMode(Pul_1, INPUT);
*/
  pinMode(Pul_2, INPUT);
  pinMode(Pul_3, INPUT);
  pinMode(Switch_0, INPUT);
  pinMode(Switch_1, INPUT);
  pinMode(Switch_2, INPUT);
//  pinMode(Switch_3, INPUT);
  Serial.begin(9600);
  inputString.reserve(100);
  while (!Serial) continue;
  mySerial.begin(9600);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  digitalWrite(txPin, LOW);
}
 
void loop() { 
  if (mySerial.available()) {
    mySerialFunction();
  }
  Serial.println(recibido);
}

void mySerialFunction() {
    Serial.write(mySerial.read());
    recibido = mySerial.readString();
      
    if(recibido == "Enviar"){
    mySerial.println("Pulsadores: ");
/*    if(digitalRead(Pul_0)) mySerial.println("0: ON");
    else mySerial.println("0: OFF");
    if(digitalRead(Pul_1)) mySerial.println("1: ON");
    else mymySerial.println("1: OFF");
*/
    if(digitalRead(Pul_2)) mySerial.println("2: ON");
    else mySerial.println("2: OFF");
    if(digitalRead(Pul_3)) mySerial.println("3: ON");
    else mySerial.println("3: OFF");
    mySerial.println("Llaves: ");
    if(digitalRead(Switch_0)) mySerial.println("0: ON");
    else mySerial.println(" Llave 0: OFF");
    if(digitalRead(Switch_1)) mySerial.println("1: ON");
    else mySerial.println("1: OFF");
    if(digitalRead(Switch_2)) mySerial.println("2: ON");
    else mySerial.println("2: OFF");
/*    if(digitalRead(Switch_3)) mySerial.println("3: ON");
    else mySerial.println("3: OFF");
*/     
    }
    else  {
     mySerial.println("La palabra no es enviar");
      }
}
