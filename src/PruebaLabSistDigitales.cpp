#include <ArduinoJson.h>
#include <UIPEthernet.h>

EthernetServer server = EthernetServer(22);

//////// VAriables de json //////////////
// Estado
int num_Lab=0;
bool subLab=true;
bool iniLab=true;
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

//////////// Strings de comunicación /////////////
char status[170] = {0};
char instrucciones[150] = {0};
char operacion[20] = {0};

////////////// Funciones  ////////////////////
void ControlPost(void);
void enciendoled(bool p0,bool p1,bool p2,bool p3);

//////////// declaración de salidas ///////////////////
const int Led_0=7;
const int Led_1=8;
const int Led_2=9;
const int Led_3=10;

/////////// salidas para el motor ////////////
#define IN1  3
#define IN2  4
#define IN3  5
#define IN4  6

void setup() {
  uint8_t mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  IPAddress myIP(172,20,5,140);
  // Initialize serial port
  Serial.begin(9600);
  while (!Serial) continue;
  // Initialize Ethernet libary
  Ethernet.begin(mac,myIP);  
  // Start to listen
  server.begin();
  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());
  
  // declaro salidas para leds
  pinMode(Led_0, OUTPUT);
  pinMode(Led_1, OUTPUT);
  pinMode(Led_2, OUTPUT);
  pinMode(Led_3, OUTPUT);

  digitalWrite(Led_2,LOW);
  digitalWrite(Led_3,LOW);
  }

void loop() {
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
  // Comparo la cadena recibida con las opcciones
    strncpy(operacion,status,15);
    Serial.println("operacion: ");
    Serial.println(operacion);
//obtengo las instrucciones del formato json
    strncpy(instrucciones,&status[15],(sizeof(status)-15));
    Serial.println("instrucciones:");
    Serial.println(instrucciones);   
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
 client.stop();

      }
///////////////////////////// POST ///////////////////////////////////
    if (strstr(status, "POST / HTTP/1.1") !=NULL) {
        Serial.println("Solicitud de escritura recibida");
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

      ControlPost();
    }

    
  }

}

void ControlPost(){
  if(num_Lab==0){
    Serial.println("Laboratorio: Sistemas Digitales");
    enciendoled(pulsador_0,pulsador_1,pulsador_2,pulsador_3);
    delay(1000);
    enciendoled(SW_0,SW_1,SW_2,SW_3);
    delay(1000);
  } 
}



void enciendoled(bool p0,bool p1,bool p2,bool p3){
  if(p0)
    digitalWrite(Led_0,HIGH);
  else
    digitalWrite(Led_0,LOW);
   if(p1)
    digitalWrite(Led_1,HIGH);
   else
    digitalWrite(Led_1,LOW);
   if(p2)
    digitalWrite(Led_2,HIGH);
   else
    digitalWrite(Led_2,LOW);
   if(p3)
    digitalWrite(Led_3,HIGH);
   else
    digitalWrite(Led_3,LOW);
}
