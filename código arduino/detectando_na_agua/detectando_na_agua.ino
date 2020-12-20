#include<SD.h>
#include<SPI.h>
#include <Wire.h>
#include <DS3231.h>

File myFile;
DS3231 rtc;              //Criação do objeto do tipo DS3231
RTCDateTime dataehora;   //Criação do objeto do tipo RTCDateTime

int CS = 10; //Pin 10 para UNO

void setup() {
  Serial.begin(9600);
  rtc.begin();            //Inicialização do RTC DS3231
  rtc.setDateTime(__DATE__, __TIME__);   //Configurando valores iniciais do RTC DS3231
  pinMode(CS, OUTPUT); // Declara pino CS/SS como saída

  if (SD.begin(CS)) { // Inicializa o SD Card
    Serial.println("SD Card pronto para uso."); // Imprime na tela
  }
  else {
    Serial.println("Falha na inicialização do SD Card.");
    return;
  }
  myFile = SD.open("LAIS.csv", FILE_WRITE); // Cria / Abre arquivo .csv

  if (myFile) { // Se o Arquivo abrir imprime:
    Serial.println("Escrevendo no Arquivo .csv"); // Imprime na tela
    myFile.println("Data\tHorario\tcoluna3\tcoluna4\tcoluna5"); // Escreve no Arquivo
    myFile.println("dd/mm/aaaa\tHH:MM:SS\tunidade3\tunidade4\tunidade5"); // Escreve no Arquivo
    myFile.close(); // Fecha o Arquivo após escrever
    Serial.println("Terminado."); // Imprime na tela
    Serial.println(" ");
  }

  else {     // Se o Arquivo não abrir
    Serial.println("Erro ao Abrir Arquivo .csv"); // Imprime na tela
  }
}

void loop() {
  dataehora = rtc.getDateTime();     //Atribuindo valores instantâneos de data e hora à instância dataehora
  if (myFile = SD.open("LAIS.csv", FILE_WRITE)) {//abre o arquivo para salvar dados
    myFile.print(dataehora.day);//escreve no arquivo
    myFile.print("/");//escreve no arquivo
    myFile.print(dataehora.month);//escreve no arquivo
    myFile.print("/");//escreve no arquivo
    myFile.print(dataehora.year);//escreve no arquivo
    myFile.print("\t");//tabulação
    myFile.print(dateehora.hour);//escreve no arquivo
    myFile.print(":");//escreve no arquivo
    myFile.print(dateehora.minute);//escreve no arquivo
    myFile.print(":");//escreve no arquivo
    myFile.print(dateehora.second);//escreve no arquivo
  }
