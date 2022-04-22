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
//String inputString = "";         // a String to hold incoming data
//bool stringComplete = false;  // whether the string is complete
//String recibido="";
//String enviado="";
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);

//void mySerialFunction();
    
void setup() {
///////////////////////////////////////////////////
// Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;
  // Initialize SoftwareSerial port
  mySerial.begin(9600);
 // pinMode(rxPin, INPUT);
 // pinMode(txPin, OUTPUT);
}
 
void loop() { 
  char mensaje[20]={0};
  char recibe[20]={0};
  
  if(Serial.available()){
    while(Serial.available()){
    char c=Serial.read();
    mySerial.print(c);
    }
  }
  if(mySerial.available()){
    while(mySerial.available()){
    char d=mySerial.read();
    Serial.print(d);
    }
  }
}
