#include <Arduino.h>

#define BUTTON_PIN 2

int lastState = HIGH;
bool onOff = false;

void setup() {
    Serial.begin(9600);
    pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
    int state = digitalRead(BUTTON_PIN);

    if (state != lastState) {
        if (state == LOW) {
            onOff = !onOff;
            String message = onOff ? "Turned ON" : "Turned OFF";
            Serial.println(message);
        }
        lastState = state;
    }

    delay(50);
}
