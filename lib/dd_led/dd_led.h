#ifndef DD_LED_H
#define DD_LED_H

#include <Arduino.h>

class DD_Led {
public:
    DD_Led(int pin);  // Конструктор, принимающий пин, к которому подключен светодиод
    void ledOn();     // Метод для включения светодиода
    void ledOff();    // Метод для выключения светодиода

private:
    int ledPin;       // Пин, к которому подключен светодиод
};

#endif