//ultimo update 25/10/2019
#include <SparkFunCCS811.h>     //Click here to get the library: http://librarymanager/All#SparkFun_CCS811
#include <ClosedCube_HDC1080.h>
#include <Wire.h>
#include "RTClib.h"
#define CCS811_ADDR 0x5A

ClosedCube_HDC1080 myHDC1080;
CCS811 myCCS811(CCS811_ADDR);
RTC_DS1307 RTC;

//variaveis
int ano, co2, mes, dia, hora, minuto, umidade, gases;
double temp;
byte m, z;
int minut = -1;
//Determina o intervalo entre cada leitura
int intervaloLeitura = 1;

void setup() {
  Serial.begin(9600);
  myHDC1080.begin(0x40);
  myCCS811.begin();
  Wire.begin();
  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
   // RTC.adjust(DateTime(__DATE__, __TIME__));
  }
  delay(5000);
}

void loop() {


  delay(5000);
  
  //Leitura do tempo do RTC
  DateTime now = RTC.now();
  minuto = now.minute();
  
  if ((minuto % intervaloLeitura) == 0 && minuto != minut) {
    minut = minuto;
    //Sensor CCS811
    myCCS811.readAlgorithmResults();

    myCCS811.setEnvironmentalData(myHDC1080.readHumidity(), myHDC1080.readTemperature());

    //Leitura do Co2
    co2 = myCCS811.getCO2();
    //Leitura de gases em geral
    gases = myCCS811.getTVOC();

    //Leitura da temperatura
    temp = myHDC1080.readTemperature();
    //Leitura de umidade
    umidade = myHDC1080.readHumidity();

    //Leitura das datas
    ano = now.year();
    mes = now.month();
    dia = now.day();
    hora = now.hour();
    temp*=100;

    envio();
/*
      Serial.println("");
      Serial.println(temp);
      Serial.println(co2);
      Serial.println(umidade);
      Serial.print(ano);
      Serial.print(":");
      Serial.print(mes);
      Serial.print(":");
      Serial.print(dia);
      Serial.print(":");
      Serial.print(hora);
      Serial.print(":");
      Serial.println(minuto);
  */
  }
}


void envio() {
    delay(20);
  _16bits(temp);
    delay(20);
  _16bits(ano);
    delay(20);
  _16bits(co2);
    delay(20);
  _16bits(gases);
    delay(20);
  _8bits(mes);
    delay(20);
  _8bits(dia);
    delay(20);
  _8bits(hora);
    delay(20);
  _8bits(minuto);
    delay(20);
  _8bits(umidade);

  
  //envia o co2


  
}

//Função 16 bits
void _16bits(int x) {
  m = highByte(x);
  z = lowByte(x);
  Serial.write(z);
  delay(100);
  Serial.write(m);
}

//Função 8 bits
void _8bits(int x) {
  delay(100);
  Serial.write(x);
}
