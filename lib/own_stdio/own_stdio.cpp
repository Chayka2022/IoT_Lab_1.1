#include "own_stdio.h" // Подключение заголовочного файла для перенаправления стандартных потоков через UART
// Создание статической структуры FILE для работы с UART как стандартными потоками ввода/вывода
static FILE uart_stdio_file = {0};
// Функция для вывода символа через UART
int own_stdio_putchar(char c, FILE *stream)
{
    Serial.write(c); // Отправка символа через последовательный порт
    return 0; // Возврат 0 в случае успешной записи
}
// Функция для чтения символа с UART
int own_stdio_getchar(FILE *stream)
{
    while (!Serial.available()); // Ожидание, пока не появятся данные в буфере
    return Serial.read(); // Чтение и возврат символа из последовательного порта
}
// Функция настройки UART для работы стандартных потоков ввода/вывода
void own_stdio_setup(const uint32_t baudrate)
{
    Serial.begin(baudrate); // Инициализация последовательного порта с заданной скоростью
                            // Настройка структуры FILE для использования функций ввода/вывода uart_stdio_putchar и uart_stdio_getchar
    fdev_setup_stream(&uart_stdio_file, own_stdio_putchar, own_stdio_getchar, _FDEV_SETUP_RW);
    stdin = &uart_stdio_file; // Перенаправление стандартного ввода на UART
    stdout = &uart_stdio_file; // Перенаправление стандартного вывода на UART
}