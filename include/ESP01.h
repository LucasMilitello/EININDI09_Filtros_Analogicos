#ifndef ESP01_H
#define ESP01_H

#include <Arduino.h>

/**
 * @brief Biblioteca para controle do ESP-01 em modo transparente (CIPMODE=1) via comandos AT.
 * 
 * Esta classe encapsula os comandos AT necessários para conectar o ESP-01 a uma rede Wi-Fi
 * e iniciar uma conexão TCP em modo transparente, permitindo o envio direto de dados sem usar AT+CIPSEND repetidamente.
 */
class ESP01 {
public:
    /**
     * @brief Construtor.
     */
    ESP01() : _transmissionStarted(false) {}

    /**
     * @brief Inicializa o ESP-01 e entra em modo de transmissão transparente (TCP).
     * 
     * @param ssid Nome da rede Wi-Fi.
     * @param password Senha da rede Wi-Fi.
     * @param ip IP do servidor de destino (ex: "192.168.1.10").
     * @param port Porta TCP do servidor de destino.
     */
    void begin(const char* ssid, const char* password, const char* ip, uint16_t port) {
        Serial.begin(115200);
        delay(2000);

        Serial.println("AT+CWMODE=0");  // Modo estação
        delay(1000);

        Serial.print("AT+CWJAP=\"");
        Serial.print(ssid);
        Serial.print("\",\"");
        Serial.print(password);
        Serial.println("\"");
        delay(5000);

        Serial.println("AT+CIPMUX=0"); // Comando que solicita o IP do ESP
        delay(10);
        
        Serial.println("AT+CIPMODE=1");  // Modo transparente
        delay(1000);

        Serial.print("AT+CIPSTART=\"TCP\",\"");
        Serial.print(ip);
        Serial.print("\",");
        Serial.println(port);
        delay(3000);

        Serial.println("AT+CIPSEND");  // Entra em modo transparente
        delay(3000);

        _transmissionStarted = true;
    }

    /**
     * @brief Envia uma string diretamente pela conexão TCP ativa.
     * 
     * @param data String com os dados (pode incluir '\n' se desejar).
     */
    void send(const String& data) {
        if (_transmissionStarted) {
            Serial.print(data);  // Envio direto
        }
    }

    /**
     * @brief Verifica se a transmissão já foi iniciada com sucesso.
     * 
     * @return true Se o modo transparente foi ativado.
     * @return false Se ainda não iniciou.
     */
    bool isReady() {
        return _transmissionStarted;
    }

private:
    bool _transmissionStarted;
};

#endif
