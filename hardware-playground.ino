#include <Arduino.h>

#define LED_PIN LED_BUILTIN

void setup() {
    pinMode(LED_PIN, OUTPUT);
}

void loop() {
    for (int i = 0; i < 5; i++) {
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(LED_PIN, LOW);
        delay(100);
    }

    delay(5000);
}
