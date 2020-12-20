#include<SD.h>
#include<SPI.h>

File myFile;

int CS = 10; //Pin 10 para UNO

void setup() {
  Serial.begin(9600); 
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
    myFile.println("coluna1\tcoluna2\tcoluna3\tcoluna4\tcoluna5"); // Escreve no Arquivo
    myFile.println("unidade1\tunidade2\tunidade3\tunidade4\tunidade5"); // Escreve no Arquivo
    myFile.close(); // Fecha o Arquivo após escrever
    Serial.println("Terminado."); // Imprime na tela
    Serial.println(" ");
  }

  else {     // Se o Arquivo não abrir
    Serial.println("Erro ao Abrir Arquivo .csv"); // Imprime na tela
  }
}

void loop() {
 if (myFile = SD.open("LAIS.csv", FILE_WRITE)) {//abre o arquivo para salvar dados 
  myFile.print("data");//escreve no arquivo
  myFile.print("\t");//tabulação
}
