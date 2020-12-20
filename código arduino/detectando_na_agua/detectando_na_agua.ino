#include <Wire.h>
#include <DS3231.h>

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

DS3231 rtc;              //Criação do objeto do tipo DS3231
RTCDateTime dataehora;   //Criação do objeto do tipo RTCDateTime
//Pinos do NodeMCU: SDA => D1 SCL => D2
// Configure com suas credenciais do FireBase
// Credencial está em configuração do projeto, contas e serviços.
#define FIREBASE_HOST "detectando-na-agua1-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "a73Mo8zCcRorzwlTdkFuW1YzGnfLVABLphrHkBWf"
#define WIFI_SSID "nome da sua rede wifi"
#define WIFI_PASSWORD "senha da sua rede wifi"

WiFiServer server(80);// Porta 80 do webserver

void setup() {
  Serial.begin(9600);
  rtc.begin();            //Inicialização do RTC DS3231
  rtc.setDateTime(__DATE__, __TIME__);   //Configurando valores iniciais do RTC DS3231
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("conectado: ");
  Serial.println(WiFi.localIP());
  //Iniciar Firebase
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  dataehora = rtc.getDateTime();     //Atribuindo valores instantâneos de data e hora à instância dataehora
  Serial.print(dataehora.year);     //Imprimindo o Ano
  Serial.print("-");
  Serial.print(dataehora.month);    //Imprimindo o Mês
  Serial.print("-");
  Serial.print(dataehora.day);      //Imprimindo o Dia
  Serial.print(" ");
  Serial.print(dataehora.hour);     //Imprimindo a Hora
  Serial.print(":");
  Serial.print(dataehora.minute);   //Imprimindo o Minuto
  Serial.print(":");
  Serial.println(dataehora.second);   //Imprimindo o Segundo
  delay(1000);
  Firebase.pushInt("time/hora",dataehora.hour);
  Firebase.pushInt("time/minuto",dataehora.minute);
  Firebase.pushInt("time/segundo",dataehora.second);
  Firebase.pushInt("time/dia",dataehora.day);
  Firebase.pushInt("time/mes",dataehora.month);
  Firebase.pushInt("time/ano",dataehora.year);
}
