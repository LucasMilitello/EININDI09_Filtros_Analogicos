#include <Arduino.h>
#include "IiKit.h"

#define TIME_DELAY 10.0 // Time em microsegundos
// #define configTICK_RATE_HZ uint32_t(1.0/(TIME_DELAY/1000000.0))
// #define portTICK_PERIOD_US (1.0/TIME_DELAY)

void plotWave(void *)
{
  AsyncDelayUS_c delayPlotWave(TIME_DELAY); // time in micro second
  for (;;)
  {
    if (delayPlotWave.isExpired())
    {
      delayPlotWave.repeat();
      const uint16_t vlPOT1 = map(analogRead(def_pin_POT1), 0, 4095, 0, 255);      
      dacWrite(def_pin_DAC1,vlPOT1);
      //vTaskDelay(10*portTICK_PERIOD_US);
    }
  }
}

void setup()
{
  IIKit.setup();

  xTaskCreate(
      plotWave,    // Function name
      "Task Wave", // Task name
      5000,        // Stack size
      NULL,        // Task parameters
      1,           // Task priority
      NULL         // Task handle
  );
}

void loop()
{
  IIKit.loop();
}