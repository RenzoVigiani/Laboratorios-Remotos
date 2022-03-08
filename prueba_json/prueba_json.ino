#include <ArduinoJson.h>
//#include <Ethernet.h>
//#include <SPI.h>
#include <UIPEthernet.h>
//EthernetServer server(22);
EthernetServer server = EthernetServer(22);
int L1=0;
int L2=1;
int L3=0;
int M1=0;
int M2=90;
int M3=180;
int value=0;
byte dato=0x00;
char status[100] = {0};
char operacion[100] = {0};
char valores_recibidos[100] = {0};


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
  }

void loop() {
  // Wait for an incomming connection
  EthernetClient client = server.available();
  
  // Do we have a client?
  if (!client) return;
  Serial.println(F("New client"));
  
  // Read the request (we ignore the content in this example)
  while (client.available()) 
    client.readBytesUntil('\r', status, sizeof(status));
    Serial.println(status);
// Comparo la cadena recibida con las opcciones
    strncpy(valores_recibidos,&status[15],sizeof(status));
    strncpy(operacion,status,15);

    Serial.println(operacion);    
    Serial.println(valores_recibidos);
    
    if (strcmp(operacion, "GET / HTTP/1.1") == 0) {
          // Allocate a temporary JsonDocument
          // Use arduinojson.org/v6/assistant to compute the capacity.
          StaticJsonDocument<500> doc;     
          // Create the "analog" array
          JsonArray analogValues = doc.createNestedArray("Leds");
          value = L1;
          analogValues.add(value);
          value = L2;
          analogValues.add(value);
          value = L3;
          analogValues.add(value);
          // Create the "digital" array
          JsonArray digitalValues = doc.createNestedArray("Position");
          value = M1;
          digitalValues.add(value);
          value = M2;
          digitalValues.add(value);
          value = M3;
          digitalValues.add(value);    
    
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
    if (strcmp(operacion, "POST / HTTP/1.1") == 0) {
        Serial.println("Solicitud de escritura recibida");
        client.println(F("HTTP/1.1 200 OK"));
        client.println();
        
        StaticJsonDocument<96> doc;

        DeserializationError error = deserializeJson(doc, valores_recibidos);
        
        if (error) {
          Serial.print(F("deserializeJson() failed: "));
          Serial.println(error.f_str());
          return;
        }
        
        JsonArray Leds = doc["Leds"];
        L1 = Leds[0]; // 1
        L2 = Leds[1]; // 0
        L3 = Leds[2]; // 1
        
        JsonArray Position = doc["Position"];
        M1 = Position[0]; // 180
        M2 = Position[1]; // 90
        M3 = Position[2]; // 0
        }
  // Disconnect
  //  client.stop();
}
