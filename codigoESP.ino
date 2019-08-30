

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "projeto-arduino-749e4.firebaseio.com"
#define FIREBASE_AUTH "nt6sQAFSp38qXz5a1lDx84gWFg0fVwRvvheHH5PA"
#define WIFI_SSID "arduino"
#define WIFI_PASSWORD "54321abc"

void setup() {
  Serial.begin(9600);

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}



void loop() {
 //Recebe os dados enviados pelo arduino
   while( Serial.available() == 0){ }
   byte z = Serial.read();
   delay(100);
   while( Serial.available() == 0){ }
   byte m = Serial.read();
   int pot = word( z, m);
  
  // define o valor
  Firebase.setInt("Sala1/potenciometro", pot);
  // informa erros
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(5000);
}
