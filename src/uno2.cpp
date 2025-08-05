#include<Arduino.h>

float t = 0.0;
float dt = 0.1;

void setup() {
  Serial.begin(115200);
  delay(200);

  // Configura o Wi-Fi
  Serial.println("AT+CWMODE=1");
  delay(10);
  Serial.println("AT+CWJAP=\"APJosue\",\"josue32154538\"");
  delay(10);
  Serial.println("AT+CIPMUX=0"); // Comando que solicita o IP do ESP
  delay(10);
  // Conecta ao servidor Python (IP público ou IP local fixo que você definir)
  Serial.println("AT+CIPSTART=\"TCP\",\"200.19.148.219\",4000");
  //Serial.println("AT+CIPSTART=\"UDP\",\"200.19.148.219\",47269,1234,0");
  delay(1000);
}

void loop() {
  float valor = sin(t);
  
  char valorStr[10];
  dtostrf(valor, 5, 2, valorStr);  // largura 5, 2 casas decimais

  char msg[32];
  sprintf(msg, "seno:%s\n", valorStr);  // monta a string final

  // Envia o comando de envio
  Serial.print("AT+CIPSEND=");
  Serial.println(strlen(msg));

  // Aguarda até aparecer o caractere '>' na serial
  unsigned long timeout = millis();
  while (millis() - timeout < 2000) {
    if (Serial.available()) {
      char c = Serial.read();
      if (c == '>') {
        Serial.print(msg); // envia o dado em si
        break;
      }
    }
  }
  t += dt;
}