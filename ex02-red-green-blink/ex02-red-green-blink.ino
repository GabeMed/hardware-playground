#include <Arduino.h>

#define RED_LED_PIN   13
#define GREEN_LED_PIN 12

void blinkLed(int pin, int times, int intervalMs) {
    for (int i = 0; i < times; i++) {
        digitalWrite(pin, HIGH);
        delay(intervalMs);
        digitalWrite(pin, LOW);
        delay(intervalMs);
    }
}

void setup() {
    pinMode(RED_LED_PIN, OUTPUT);
    pinMode(GREEN_LED_PIN, OUTPUT);
}

void loop() {
    digitalWrite(GREEN_LED_PIN, LOW);
    blinkLed(RED_LED_PIN, 3, 100);
    digitalWrite(RED_LED_PIN, LOW);
    delay(3000);

    digitalWrite(RED_LED_PIN, LOW);
    blinkLed(GREEN_LED_PIN, 3, 100);
    digitalWrite(GREEN_LED_PIN, LOW);
    delay(3000);
}
