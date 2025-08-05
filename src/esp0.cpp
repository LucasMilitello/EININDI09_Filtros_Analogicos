#include <iikitmini.h>      // Biblioteca base do framework Arduino
#include "util/AdcDmaEsp.h" // Classe para configuração do ADC e DMA
#define  NUMTASKS 1
#include "util/jtask.h"

void setup()
{
    IIKit.setup();
}

void loop()
{
    IIKit.loop();
}