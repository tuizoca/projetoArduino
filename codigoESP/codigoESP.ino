

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "qualidade-do-ar-57113.firebaseio.com/"
#define FIREBASE_AUTH "AIzaSyAd8UKdvZ05jZJMbnXTAqKf721-QIrKXz8"
#define WIFI_SSID "Ar_do_ino"
#define WIFI_PASSWORD "123pin45pin"

  String ano = "2019";
  String mes = "8";
  String dia = "1";
  String hora = "1";
  int minuto = 5;
  String co2= "5.5";
  String go = "6666";
  String humidade = "77.5";
  String temp = "29.7";

  
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
  
  String local = ano+"/"+mes+"/"+dia+"/"+hora+"/"+minuto+"/";
  minuto+=5;
  //envia o co2
  Firebase.setString(local+"co2",co2);
  //envia o gases-organicos
  Firebase.setString(local+"gases-organicos",go);
  //envia o humildade
  Firebase.setString(local+"humidade",humidade);
  //envia o temperatura
  Firebase.setString(local+"temperatura", temp);

  // informa erros
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(5000);
}
