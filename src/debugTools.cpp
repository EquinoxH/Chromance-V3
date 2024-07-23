#include <Arduino.h>

#include "debugTools.h"

void DebugTools::blink() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(250);
    digitalWrite(LED_BUILTIN, LOW);
    delay(250);
}

void DebugTools::blinkNumTimes(int num) {
    for (int i = 0; i < num; i++) {
        blink();
    }
}
