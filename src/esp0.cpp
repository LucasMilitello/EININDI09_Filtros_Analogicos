#include <iikitmini.h>      // Biblioteca base do framework Arduino
#include "util/AdcDmaEsp.h" // Classe para configuração do ADC e DMA
#define NUMTASKS 1
#include "util/jtask.h"

uint32_t timeDelayMS = 10;
uint32_t expiresDelayMS = 0;

void setup()
{
    IIKit.setup();
    Serial.begin(19200);
}

void loop()
{
    IIKit.loop();
    if ((millis() - expiresDelayMS) >= timeDelayMS)
    {
        expiresDelayMS = millis();
        Serial.print(">graf:");
        Serial.print(expiresDelayMS);
        Serial.print(":");
        Serial.print(analogRead(def_pin_ADC1));
        Serial.println("|g");
    }
}