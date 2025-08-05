#include "ESP01.h"

ESP01 esp;
float t = 0.0;
float dt = 0.1;

void setup() {
  esp.begin("APJosue", "josue32154538", "200.19.148.219", 4000);
}

void loop() {
  if (esp.isReady()) {
    float valor = sin(t);
    char valorStr[10];
    dtostrf(valor, 5, 2, valorStr);

    String msg = "seno:";
    msg += valorStr;
    msg += "\n";

    esp.send(msg);
    t += dt;
    delay(100);  // taxa de 10 Hz
  }
}
