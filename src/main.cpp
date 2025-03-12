#include "serial_manager.h"
#include "setup_manager.h"
#include "input_processor.h"

void setup() {
    initSerial(UART_BAUDRATE);  
    init_Setup();
}

void loop() {
    inputProcessor(); 
}
