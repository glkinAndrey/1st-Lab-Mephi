#ifndef ERRORS_H
#define ERRORS_H

// Коды ошибок для операций
typedef enum {
    OP_SUCCESS = 0,             // Успех
    OP_ERROR_NULL_POINTER = 1,  // Передан NULL указатель
    OP_ERROR_SIZE_MISMATCH = 2, // Размеры матриц не совпадают
    OP_ERROR_TYPE_MISMATCH = 3, // Типы матриц не совпадают
    OP_ERROR_MEMORY = 4         // Ошибка выделения памяти
} OpStatus;

// Выводит сообщение об ошибке на основе кода
void print_op_error(OpStatus status);

#endif