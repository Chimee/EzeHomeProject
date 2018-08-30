#include "SPI.h"
#include "MFRC522.h"
#include "WiFi.h"
#include "HTTPClient.h"


#define panel_1   32
#define panel_2   33
#define panel_3   25
 
const int RST_PIN = 22;                 // Configurable, see typical pin layout above
const int SS_PIN = 21;                  // Configurable, see typical pin layout above
const char* ssid = "RoQweiler1911";
const char* password =  "ABCDEF1911";


 
MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance
 
void setup() {
  pinMode(panel_1, INPUT_PULLUP);
  pinMode(panel_2, INPUT_PULLUP);
  pinMode(panel_3, INPUT_PULLUP);
  
  Serial.begin(9600);   // Initialize serial communications 
  SPI.begin();      // Init SPI bus
  WiFi.begin(ssid, password);
  mfrc522.PCD_Init();   // Init MFRC522
  mfrc522.PCD_DumpVersionToSerial();  // Show MFRC522 Card Reader details
  Serial.println(F("Scan PICC to see UID, SAK, type, and data blocks..."));
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
   
  }

  if ((WiFi.status() == WL_CONNECTED)){
  Serial.println("Connected to WiFi!");
  
  }

}
 
void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
 
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
 //UIDS = F6 A1 A8 89 and E7 1C 06 89
  // Dump debug info about the card; PICC_HaltA() is automatically called
  mfrc522.PICC_DumpToSerial(&(mfrc522.uid));


 //RFID Interface 
//Check for correct UID bfore sending request to falcon
if (mfrc522.uid.uidByte[0] == 0xf6 && 
     mfrc522.uid.uidByte[1] == 0xa1 &&
     mfrc522.uid.uidByte[2] == 0xa8 &&
     mfrc522.uid.uidByte[3] == 0x89) {
     //send get request to falcon


  if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;
    http.begin("http://192.168.0.109:8080/trin");
    int httpCode = http.GET();

    if (httpCode > 0) {

      //check for return code 
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
     
    }
    else {

      Serial.println("Error on HTTP request, check wifi connection");
    }

    http.end(); //
    
  }
  
}



if (mfrc522.uid.uidByte[0] == 0xe7 && 
     mfrc522.uid.uidByte[1] == 0x1c &&
     mfrc522.uid.uidByte[2] == 0x06 &&
     mfrc522.uid.uidByte[3] == 0x89) {
     //send get request to falcon for captain


  if ((WiFi.status() == WL_CONNECTED)) {

    HTTPClient http;
    http.begin("http://192.168.0.109:8080/captain");
    int httpCode = http.GET();

    if (httpCode > 0) {

      //check for return code 
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
     
    }
    else {

      Serial.println("Error on HTTP request, check wifi connection");
    }

    http.end(); //
    
  }
  
}


//Panel Button Interface 

 if (digitalRead(panel_1) == HIGH) {
  
   HTTPClient http;
    http.begin("http://192.168.0.109:8080/all");
    int httpCode = http.GET();

    if (httpCode > 0) {

      //check for return code 
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
     
    }
    else {

      Serial.println("Error on HTTP request, check wifi connection");
    }

    http.end(); //

  }


 if (digitalRead(panel_2) == HIGH) {
  
   HTTPClient http;
    http.begin("http://192.168.0.109:8080/stairs");
    int httpCode = http.GET();

    if (httpCode > 0) {

      //check for return code 
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
     
    }
    else {

      Serial.println("Error on HTTP request, check wifi connection");
    }

    http.end(); //

  }


  
 if (digitalRead(panel_3) == HIGH) {
  
   HTTPClient http;
    http.begin("http://192.168.0.109:8080/living");
    int httpCode = http.GET();

    if (httpCode > 0) {

      //check for return code 
      String payload = http.getString();
      Serial.println(httpCode);
      Serial.println(payload);
     
    }
    else {

      Serial.println("Error on HTTP request, check wifi connection");
    }

    http.end(); //

  }

  

}
