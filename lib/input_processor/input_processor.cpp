#include "input_processor.h"  // Подключаем заголовочный файл input_processor.h

// Создаём глобальный объект `led` для управления светодиодом.
// Эта строка создаёт объект `led` класса `DD_Led` и передаёт в него `LED_PIN` из config.h.
DD_Led led(LED_PIN);  // Define LED instance here instead of `main.cpp`

// Функция обработки ввода с последовательного порта
void inputProcessor() {
    // Создаём статический массив `inputArray` размером 10 символов.
    // Этот массив используется для хранения команды, вводимой пользователем.
    // `static` означает, что массив сохраняет своё состояние между вызовами функции.
    static char inputArray[10] = {0};  // Буфер для длинных команд

    // Создаём статическую переменную `index`, которая указывает, куда записывать следующий символ в `inputArray`.
    // `static` здесь позволяет сохранить позицию внутри массива между вызовами функции.
    static uint8_t index = 0;

    // Пока в буфере последовательного порта есть данные (Serial.available() > 0)
    while (Serial.available() > 0) {
        // Читаем один символ из входного буфера последовательного порта
        char incomingChar = Serial.read();

        // Если введён символ новой строки (`\n`) или возврата каретки (`\r`)
        if (incomingChar == '\n' || incomingChar == '\r') {
            // Завершаем строку, добавляя символ `\0` (конец строки)
            inputArray[index] = '\0';

            // Сбрасываем индекс, чтобы следующая команда начиналась с начала массива
            index = 0;

            // Указатель `command` теперь указывает на начало массива `inputArray`
            char* command = inputArray;

            // Убираем начальные пробелы (если пользователь случайно ввёл пробелы перед командой)
            while (*command == ' ') command++;  // Сдвигаем указатель `command`, пока встречаем пробелы

            // Указатель `end` указывает на последний значимый символ строки (не `\0`)
            char* end = command + strlen(command) - 1;

            // Убираем конечные пробелы (проходим с конца и заменяем пробелы на `\0`)
            while (end > command && *end == ' ') *end-- = '\0';

            // Приводим команду к верхнему регистру (на случай, если Serial Monitor передаёт строчные буквы)
            for (char* p = command; *p; ++p) *p = toupper(*p);

            // Проверяем введённую команду
            if (strcmp(command, "ON") == 0) {  // Если команда "ON"
                led.ledOn();  // Включаем светодиод
            } 
            else if (strcmp(command, "OFF") == 0) {  // Если команда "OFF"
                led.ledOff();  // Выключаем светодиод
            } 
            else {  
                // Если команда неизвестна, выводим сообщение об ошибке
                Serial.println("Unknown command. Please send 'ON' or 'OFF'.");
            }

            // Очищаем `inputArray`, заполняя его нулями
            memset(inputArray, 0, sizeof(inputArray));
        } 
        else if (index < sizeof(inputArray) - 1) {  // Если ещё есть место в буфере
            inputArray[index++] = incomingChar;  // Записываем символ и увеличиваем `index`
        } 
        else {  // Если буфер заполнен (длина команды слишком большая)
            Serial.println("Input too long. Please send 'ON' or 'OFF'.");  // Сообщаем об ошибке
            index = 0;  // Сбрасываем индекс
            memset(inputArray, 0, sizeof(inputArray));  // Очищаем буфер
        }
    }
}
