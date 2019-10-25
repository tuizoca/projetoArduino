//ultimo update 25/10/2019
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
// Set these to run example.
#define FIREBASE_HOST "projeto-arduino-749e4.firebaseio.com"
#define FIREBASE_AUTH "nt6sQAFSp38qXz5a1lDx84gWFg0fVwRvvheHH5PA"
#define WIFI_SSID "arduino"
#define WIFI_PASSWORD "54321abc"

int ano, co2, mes, dia, hora, minuto, umidade, gases;
float temp;
String sala = "Laboratorio_De_Fisica";

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

  temp = read16biteTemp();
  ano = read16bite();
  co2 = read16bite();
  gases = read16bite();
  mes = read8bite();
  dia = read8bite();
  hora = read8bite();
  minuto = read8bite();
  umidade = read8bite();

  temp/=100;

  Serial.println(temp);
  Serial.println(co2);
  Serial.println(gases);
  Serial.println(umidade);
  Serial.print(ano);
  Serial.print("/");
  Serial.print(mes);
  Serial.print("/");
  Serial.println(dia);
  Serial.print(hora);
  Serial.print(":");
  Serial.println(minuto);
  
//negocio que funciona

  Firebase.setInt(sala+"/"+ano+"/"+mes+"/"+dia+"/"+hora+"/"+minuto+"/co2", co2);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  
  delay(1000);

    Firebase.setInt(sala+"/"+ano+"/"+mes+"/"+dia+"/"+hora+"/"+minuto+"/umidade", umidade);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  Firebase.setInt(sala+"/"+ano+"/"+mes+"/"+dia+"/"+hora+"/"+minuto+"/gases", gases);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);

  Firebase.setFloat(sala+"/"+ano+"/"+mes+"/"+dia+"/"+hora+"/"+minuto+"/temp", temp);
  // handle error
  if (Firebase.failed()) {
      Serial.print("setting /number failed:");
      Serial.println(Firebase.error());  
      return;
  }
  delay(1000);
  
}



int read8bite() {
  while (Serial.available() == 0) {}
  int val = Serial.read();
  return val;
}

int read16bite() {
  while ( Serial.available() == 0) { }
  byte z = Serial.read();
  delay(50);
  while ( Serial.available() == 0) { }
  byte m = Serial.read();
  int val = word(m, z);
  return val;
}

float read16biteTemp() {
  while ( Serial.available() == 0) { }
  byte z = Serial.read();
  delay(50);
  while ( Serial.available() == 0) { }
  byte m = Serial.read();
  float val = word(m, z);
  return val;
}
