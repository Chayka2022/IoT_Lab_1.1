#include "input_processor.h"

DD_Led led(LED_PIN);  // Define LED instance here instead of `main.cpp`

void inputProcessor() {
    static char inputArray[10] = {0};  // Буфер для длинных команд
    static uint8_t index = 0;

    while (Serial.available() > 0) {
        char incomingChar = Serial.read();

        if (incomingChar == '\n' || incomingChar == '\r') {
            inputArray[index] = '\0';  
            index = 0;  

            char* command = inputArray;
            while (*command == ' ') command++;  
            char* end = command + strlen(command) - 1;
            while (end > command && *end == ' ') *end-- = '\0';  

            for (char* p = command; *p; ++p) *p = toupper(*p);

            if (strcmp(command, "ON") == 0) {
                led.ledOn();
            } 
            else if (strcmp(command, "OFF") == 0) {
                led.ledOff();
            } 
            else {
                Serial.println("Unknown command. Please send 'ON' or 'OFF'.");
            }

            memset(inputArray, 0, sizeof(inputArray));  
        } 
        else if (index < sizeof(inputArray) - 1) {  
            inputArray[index++] = incomingChar;
        } 
        else {  
            Serial.println("Input too long. Please send 'ON' or 'OFF'.");
            index = 0;
            memset(inputArray, 0, sizeof(inputArray));
        }
    }
}
