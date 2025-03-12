#include "serial_manager.h"


void initSerial(unsigned long  baudrate) {
    Serial.begin(baudrate); // Использование скорости UART определённой в config.h
}
