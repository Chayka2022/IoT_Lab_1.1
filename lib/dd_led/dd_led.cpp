#include "dd_led.h"

DD_Led::DD_Led(int pin) {
    ledPin = pin;
    pinMode(ledPin, OUTPUT);
}

void DD_Led::ledOn() {
    digitalWrite(ledPin, HIGH);
    Serial.println("LED is ON");
}

void DD_Led::ledOff() {
    digitalWrite(ledPin, LOW);
    Serial.println("LED is OFF");
}
