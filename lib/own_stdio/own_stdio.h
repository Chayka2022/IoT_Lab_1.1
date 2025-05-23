#ifndef UART_STDIO_H
#define UART_STDIO_H
#include <Arduino.h> 
#include <stdio.h> 
#include <stdint.h>

void own_stdio_setup(const uint32_t baudrate);
// Выводит символ через UART (используется функцией putchar)
int own_stdio_putchar(char c, FILE *stream);
// Читает символ с UART (используется функцией getchar)
int own_stdio_getchar(FILE *stream);
#endif // UART_STDIO_H