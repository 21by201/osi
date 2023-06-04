#include <stdio.h>
#include <stdlib.h>
 
/* Локальные переменные */
void local_variables() {
    int local_int = 5;
    char local_char = 'A';
    float local_float = 3.14;
 
    printf("Local Variables:\n");
    printf("local_int: %p\n", (void*)&local_int);
    printf("local_char: %p\n", (void*)&local_char);
    printf("local_float: %p\n", (void*)&local_float);
}
 
/* Статические переменные */
void static_variables() {
    static int static_int = 10;
    static char static_char = 'B';
    static float static_float = 2.718;
 
    printf("Static Variables:\n");
    printf("static_int: %p\n", (void*)&static_int);
    printf("static_char: %p\n", (void*)&static_char);
    printf("static_float: %p\n", (void*)&static_float);
}
 
/* Константы */
void constant_variables() {
    const int constant_int = 15;
    const char constant_char = 'C';
    const float constant_float = 1.23;
 
    printf("Constant Variables:\n");
    printf("constant_int: %p\n", (void*)&constant_int);
    printf("constant_char: %p\n", (void*)&constant_char);
    printf("constant_float: %p\n", (void*)&constant_float);
}
 
/* Глобальные инициализированные переменные */
int global_initialized_int = 20;
char global_initialized_char = 'D';
float global_initialized_float = 4.56;
 
/* Глобальные неинициализированные переменные */
int global_uninitialized_int;
char global_uninitialized_char;
float global_uninitialized_float;
 
/* Глобальные константы */
const int global_constant_int = 25;
const char global_constant_char = 'E';
const float global_constant_float = 6.78;
 
/* Функция создает и инициализирует локальную переменную и возвращает ее адрес */
int* create_and_initialize_local_variable() {
    int local_variable = 30;
 
    return &local_variable;
}
 
/* Функция для работы с кучей */
void heap_operations() {
    char* buffer1 = (char*)malloc(100 * sizeof(char)); // Выделение памяти на куче
    strcpy(buffer1, "Hello, world!"); // Запись в буфер
    printf("Buffer1: %s\n", buffer1); // Вывод содержимого буфера
 
    free(buffer1); // Освобождение памяти
 
    printf("Buffer1 after free: %s\n", buffer1); // Вывод содержимого буфера после освобождения
 
    char* buffer2 = (char*)malloc(100 * sizeof(char)); // Выделение памяти на куче
    strcpy(buffer2, "Hello, world again!"); // Запись в буфер
    printf("Buffer2: %s\n", buffer2); // Вывод содержимого буфера
 
    char* buffer2_middle = buffer2 + 6; // Перемещение указателя на середину буфера
    free(buffer2_middle); // Освобождение памяти по указателю
 
    printf("Buffer2 after free at middle: %s\n", buffer2); // Вывод содержимого буфера после освобождения
}
 
int main() {
    /* Локальные переменные */
    local_variables();
 
    /* Статические переменные */
    static_variables();
 
    /* Константы */
    constant_variables();
 
    /* Глобальные инициализированные переменные */
    printf("Global Initialized Variables:\n");
    printf("global_initialized_int: %p\n", (void*)&global_initialized_int);
    printf("global_initialized_char: %p\n", (void*)&global_initialized_char);
    printf("global_initialized_float: %p\n", (void*)&global_initialized_float);
 
    /* Глобальные неинициализированные переменные */
    printf("Global Uninitialized Variables:\n");
    printf("global_uninitialized_int: %p\n", (void*)&global_uninitialized_int);
    printf("global_uninitialized_char: %p\n", (void*)&global_uninitialized_char);
    printf("global_uninitialized_float: %p\n", (void*)&global_uninitialized_float);
 
    /* Глобальные константы */
    printf("Global Constant Variables:\n");
    printf("global_constant_int: %p\n", (void*)&global_constant_int);
    printf("global_constant_char: %p\n", (void*)&global_constant_char);
    printf("global_constant_float: %p\n", (void*)&global_constant_float);
 
    /* Функция создает и инициализирует локальную переменную и возвращает ее адрес */
    int* local_variable_ptr = create_and_initialize_local_variable();
    printf("Address of local_variable_ptr: %p\n", (void*)&local_variable_ptr);
    printf("Value of local_variable_ptr: %p\n", (void*)local_variable_ptr);
 
    /* Работа с кучей */
    heap_operations();
 
    return 0;
}
 