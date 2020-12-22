#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <MCP3008.h>
#include<SPI.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into digital pin 2 on the Arduino
#define ONE_WIRE_BUS D3

// Setup a oneWire instance to communicate with any OneWire device
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to DallasTemperature library
DallasTemperature sensors(&oneWire);

//Pinos do NodeMCU: SDA => D1 SCL => D2
// Configure com suas credenciais do FireBase
// Credencial está em configuração do projeto, contas e serviços.
#define FIREBASE_HOST "detectando-na-agua1-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "a73Mo8zCcRorzwlTdkFuW1YzGnfLVABLphrHkBWf"
#define WIFI_SSID "nome da sua rede wifi" //nome da sua rede wifi
#define WIFI_PASSWORD "senha da sua rede wifi" //senha da sua rede wifi

// Definindo pinos do ADC externo
#define CS_PIN D5
#define CLOCK_PIN D8
#define MOSI_PIN D6
#define MISO_PIN D7

WiFiServer server(80);// Porta 80 do webserver

MCP3008 adc(CLOCK_PIN, MOSI_PIN, MISO_PIN, CS_PIN);
const float ArduinoVoltage = 3.3; // CHANGE THIS FOR 3.3v Arduinos
const float ArduinoResolution = ArduinoVoltage / 1024;
const float resistorValue = 10000.0;
int threshold = 3;

void setup() {
  Serial.begin(9600);
  sensors.begin();  // Start up the library
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
  int inputPin = adc.readADC(1);
  int ouputPin = adc.readADC(0);
  
  int analogValue = 0;
  int oldAnalogValue = 1000;
  float returnVoltage = 0.0;
  float resistance = 0.0;
  double Siemens;
  float TDS = 0.0;
  while (((oldAnalogValue - analogValue) > threshold) || (oldAnalogValue < 50))
  {
    oldAnalogValue = analogValue;
    delay(10); // allow ringing to stop
    analogValue = inputPin ;
  }
  Serial.print("Return voltage = ");
  returnVoltage = analogValue * ArduinoResolution;
  Serial.print(returnVoltage);

  Serial.println(" volts");
  Serial.print("That works out to a resistance of ");
  resistance = ((3.3 * resistorValue) / returnVoltage) - resistorValue;
  Serial.print(resistance);
  Serial.println(" Ohms.");
  Serial.print("Which works out to a conductivity of ");
  Siemens = 1.0 / (resistance / 1000000);
  Serial.print(Siemens);
  Serial.println(" microSiemens.");
  Serial.print("Total Dissolved Solids are on the order of ");
  TDS = 500 * (Siemens / 1000);
  Serial.print(TDS);
  Serial.println(" PPM.");
  sensors.requestTemperatures();
   //print the temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(sensors.getTempCByIndex(0));
  Serial.print((char)176);//shows degrees character
  Serial.print("C  |  ");
  Firebase.pushInt("tensão", returnVoltage);
  Firebase.pushInt("resistencia", resistance);
  Firebase.pushInt("siemens", Siemens);
  Firebase.pushInt("tds", TDS);
  Firebase.pushInt("temperatura", sensors.getTempCByIndex(0));
}
