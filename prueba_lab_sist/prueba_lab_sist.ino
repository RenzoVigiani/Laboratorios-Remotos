#include <ArduinoJson.h>
#include <UIPEthernet.h>
#include <SoftwareSerial.h>
//////////// declaración de salidas ///////////////////
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
SoftwareSerial mySerial =  SoftwareSerial(rxPin, txPin);
///////////////////////////////////////////////////

// funciones
void ControlLlaves(bool sw0,bool sw1,bool sw2,bool sw3);
void ControlPost(bool pulsador_0,bool pulsador_1,bool pulsador_2,bool pulsador_3,bool SW_0,bool SW_1,bool SW_2,bool SW_3);
void ControlPulsadores(bool p0,bool p1,bool p2,bool p3);

EthernetServer server = EthernetServer(22);

void setup() {
///////////////////////////////////////////////////
// Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;
  mySerial.begin(9600);
///////////////////////////////////////////////////
// INICIALIZO MAC E IP
  uint8_t mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  IPAddress myIP(172,20,5,140);
// Initialize Ethernet libary
  Ethernet.begin(mac,myIP);  
// Start to listen
  server.begin();
  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());
///////////////////////////////////////////////////
// Declaro tipo  y estado de las salidas  
//  pinMode(Pul_0, OUTPUT);
//  digitalWrite(Pul_0,LOW);
//  pinMode(Pul_1, OUTPUT);
//  digitalWrite(Pul_1,LOW);
  pinMode(Pul_2, OUTPUT);
  digitalWrite(Pul_2,LOW);
  pinMode(Pul_3, OUTPUT);
  digitalWrite(Pul_3,LOW);
  pinMode(Switch_0, OUTPUT);
  digitalWrite(Switch_0,LOW);
  pinMode(Switch_1, OUTPUT);
  digitalWrite(Switch_1,LOW);
  pinMode(Switch_2, OUTPUT);
  digitalWrite(Switch_2,LOW);
//  pinMode(Switch_3, OUTPUT);
//  digitalWrite(Switch_3,LOW);
}

void loop(){  
//////////// Strings de comunicación /////////////
char status[190] = {0};
char instrucciones[170] = {0};
//char operacion[20] = {0};

//////// VAriables Locales de json //////////////
// Estado
  int num_Lab=0;
  bool subLab=true;
  bool iniLab=false;
// Pulsadores
  bool pulsador_0=false;
  bool pulsador_1=false;
  bool pulsador_2=false;
  bool pulsador_3=false;
// Llaves
  bool SW_0=false;
  bool SW_1=false;
  bool SW_2=false;
  bool SW_3=false;
// UART
  char UART[20]={0};

  // Wait for an incomming connection
  EthernetClient client = server.available(); 
  // Do we have a client?
  if (!client) return;
  Serial.println();
  Serial.println(F("New client"));
  // Read the request (we ignore the content in this example)
  while (client.available()) {
    client.readBytesUntil('\r', status, sizeof(status));
    Serial.println("status:");
    Serial.println(status);
/*  // Comparo la cadena recibida con las opcciones
    strncpy(operacion,status,15);
    Serial.println("operacion: ");
    Serial.println(operacion);
*/
//obtengo las instrucciones del formato json
    strncpy(instrucciones,&status[15],(sizeof(status)-15));
/*    Serial.println("instrucciones:");
    Serial.println(instrucciones);
*/
/////////////////////////////  GET  ///////////////////////////////////    
    if (strstr(status, "GET / HTTP/1.1") != NULL) {
      
      StaticJsonDocument<256> doc;     
      JsonArray Estado = doc.createNestedArray("Estado");
      Estado.add(num_Lab);
      Estado.add(subLab);
      Estado.add(iniLab);

      JsonArray Pulsadores = doc.createNestedArray("Pulsadores");
      Pulsadores.add(pulsador_0);
      Pulsadores.add(pulsador_1);
      Pulsadores.add(pulsador_2);
      Pulsadores.add(pulsador_3);

      JsonArray Llaves = doc.createNestedArray("Llaves");
      Llaves.add(SW_0);
      Llaves.add(SW_1);
      Llaves.add(SW_2);
      Llaves.add(SW_3);

      mySerial.readBytesUntil('\n', UART, sizeof(UART));     
      doc["UART"][0] = UART;
      
      Serial.print(F("Sending: "));
      serializeJson(doc, Serial);
      Serial.println();
// Write response headers
      client.println(F("HTTP/1.0 200 OK"));
      client.println(F("Content-Type: application/json"));
// client.println(F("Connection: close"));
      client.print(F("Content-Length: "));
      client.println(measureJsonPretty(doc));
      client.println(); 
// Write JSON document
      serializeJsonPretty(doc, client);
// Disconnect
//      client.stop();
      }
///////////////////////////// POST ///////////////////////////////////
    if (strstr(status, "POST / HTTP/1.1") !=NULL) {
        Serial.println("Solicitud de escritura recibida");        
        client.println();
        client.println(F("HTTP/1.1 200 OK"));
        client.println();
        StaticJsonDocument<256> doc;
        // Deserializo
        DeserializationError error = deserializeJson(doc, instrucciones);
        
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }
        
        JsonArray Estado = doc["Estado"];
        num_Lab = Estado[0]; // 0 [Sist Dig], 1 [Sist Control], 2[Telecomunicaciones], 3[Fisica]
        subLab = Estado[1]; // true[SubLab 1], false [SubLab 2]
        iniLab = Estado[2]; // true[Inicia Experimento], false[Finaliza Experimento]

        JsonArray Pulsadores = doc["Pulsadores"];
        pulsador_0 = Pulsadores[0]; // false
        pulsador_1 = Pulsadores[1]; // false
        pulsador_2 = Pulsadores[2]; // false
        pulsador_3 = Pulsadores[3]; // false

        JsonArray Llaves = doc["Llaves"];
        SW_0 = Llaves[0]; // 
        SW_1 = Llaves[1]; // 
        SW_2 = Llaves[2]; // 
        SW_3 = Llaves[3]; //  
        
        if(num_Lab==0){
          ControlPost(pulsador_0,pulsador_1,pulsador_2,pulsador_3,SW_0,SW_1,SW_2,SW_3);
          Serial.println("Salidas asignadas");
        }else{
          Serial.println("Laboratorio incorrecto");    
        }
    }
  }
}

void ControlPost(bool pulsador_0,bool pulsador_1,bool pulsador_2,bool pulsador_3,bool SW_0,bool SW_1,bool SW_2,bool SW_3){
  Serial.println("Laboratorio: Sistemas Digitales");
  Serial.println("Escribo Pulsadores...");
  ControlPulsadores(pulsador_0,pulsador_1,pulsador_2,pulsador_3);
  Serial.println("Escribo Llaves...");
  ControlLlaves(SW_0,SW_1,SW_2,SW_3);
  

}

void ControlPulsadores(bool p0,bool p1,bool p2,bool p3){
  //digitalWrite(Pul_0,p0);
  //digitalWrite(Pul_1,p1);
  digitalWrite(Pul_2,p2);
  digitalWrite(Pul_3,p3);
}

void ControlLlaves(bool sw0,bool sw1,bool sw2,bool sw3){
  digitalWrite(Switch_0,sw0);
  digitalWrite(Switch_1,sw1);
  digitalWrite(Switch_2,sw2);
  //  digitalWrite(Pul_3,p3);
}
