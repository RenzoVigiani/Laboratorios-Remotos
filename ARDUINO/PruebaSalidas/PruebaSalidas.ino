#include <ArduinoJson.h>
//#include <Ethernet.h>
//#include <SPI.h>
#include <UIPEthernet.h>
//EthernetServer server(22);
EthernetServer server = EthernetServer(22);
int L1=0;
int L2=0;
int L3=1;
int M1=0;
int M2=90;
int M3=180;
int value=0;
byte dato=0x00;
char status[100] = {0};
char instrucciones[100] = {0};
char operacion[100] = {0};
char valores_recibidos[100] = {0};
const int led5=5;
const int led6=6;
const int led7=7;
void enciendoled(void);
void setup() {
  uint8_t mac[6] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
  IPAddress myIP(172,20,5,140);
  
  // Initialize serial port
  Serial.begin(115200);
  while (!Serial) continue;
 
  // Initialize Ethernet libary
  Ethernet.begin(mac,myIP);  

  // Start to listen
  server.begin();
  Serial.println(F("Server is ready."));
  Serial.print(F("Please connect to http://"));
  Serial.println(Ethernet.localIP());
  // declaro salidas
  pinMode(led5, OUTPUT);
  pinMode(led6, OUTPUT);
  pinMode(led7, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(led5,LOW);
  digitalWrite(led6,LOW);
  digitalWrite(led7,LOW);
  }

void loop() {
  // Wait for an incomming connection
  EthernetClient client = server.available();
  
  // Do we have a client?
  if (!client) return;
  Serial.println();
  Serial.println(F("New client"));
  
  // Read the request (we ignore the content in this example)
  while (client.available()) 
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
        // Allocate a temporary JsonDocument
        // Use arduinojson.org/v6/assistant to compute the capacity.
            StaticJsonDocument<500> doc;     
        // Create the "analog" array
          JsonArray digitalValues = doc.createNestedArray("Leds");
          value = L1;
          digitalValues.add(value);
//          value = L2;
//          analogValues.add(value);
//          value = L3;
//          analogValues.add(value);
//        // Create the "digital" array
//          JsonArray digitalValues = doc.createNestedArray("Position");
//          value = M1;
//          digitalValues.add(value);
//          value = M2;
//          digitalValues.add(value);
//          value = M3;
//          digitalValues.add(value);    
          Serial.print("ENTRO EN UN GET\n");
          Serial.print(F("Sending: "));
          serializeJson(doc, Serial);
          Serial.println();
          
          // Write response headers
          
          client.println(F("HTTP/1.0 200 OK"));
          client.println(F("Content-Type: application/json"));
//          client.println(F("Connection: close"));
          client.print(F("Content-Length: "));
          client.println(measureJsonPretty(doc));
          client.println(); 
                   
          // Write JSON document
          serializeJsonPretty(doc, client);
          }
    //if (strcmp(operacion, "POST / HTTP/1.1") == 0) {
    if (strstr(status, "POST / HTTP/1.1") !=NULL) {
        Serial.println("Solicitud de escritura recibida");
        client.println(F("HTTP/1.1 200 OK"));
        client.println();
        
        StaticJsonDocument<96> doc;

       // Serial.println("ENTRO EN UN POST");
        DeserializationError error = deserializeJson(doc, instrucciones);
        
        
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }
        
        JsonArray Leds = doc["Leds"];
        L1 = Leds[0]; // 1
        L2 = Leds[1]; // 0
        L3 = Leds[2]; // 1
        //Serial.print("L1=");
        //Serial.println(L1);
        enciendoled();
        
//        JsonArray Position = doc["Position"];
//        M1 = Position[0]; // 180
//        M2 = Position[1]; // 90
//        M3 = Position[2]; // 0
        }
  // Disconnect
  //  client.stop();
}
void enciendoled(void){
  if(L1==1)
    digitalWrite(led5,HIGH);
  else
    digitalWrite(led5,LOW);
   if(L2==1)
    digitalWrite(led6,HIGH);
   else
    digitalWrite(led6,LOW);
   if(L3==1)
    digitalWrite(led7,HIGH);
   else
    digitalWrite(led7,LOW);
}
