#include "square_matrix.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void init_matrix(square_matrix* matrix, int size, const type_info* typeInfo) {
    if (!matrix || size <= 0 || typeInfo == NULL) {
        if (matrix) matrix->data = NULL;
        return;
    }
    
    matrix->size = size;
    matrix->typeInfo = typeInfo;
    matrix->data = malloc(size * size * typeInfo->size);
    
    if (!matrix->data) {
        return;
    }

    for (int i = 0; i < size * size; i++) {
        void* ptr = (char*)matrix->data + i * typeInfo->size;
        typeInfo->zero(ptr);
    }
}

// Освобождает память, выделенную под матрицу
void free_matrix(square_matrix* matrix) {
    if (matrix && matrix->data) {
        free(matrix->data);
        matrix->data = NULL;
    }
}

void set_element(square_matrix* matrix, int row, int col, const void* value) {
    if (!matrix || !matrix->data || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size) return;
    void* ptr = (char*)matrix->data + (row * matrix->size + col) * matrix->typeInfo->size;
    memcpy(ptr, value, matrix->typeInfo->size);
}

// Возвращает указатель на элемент матрицы по заданным индексам
void* get_element(const square_matrix* matrix, int row, int col) {
    if (!matrix || !matrix->data || row < 0 || row >= matrix->size || col < 0 || col >= matrix->size) return NULL;
    return (char*)matrix->data + (row * matrix->size + col) * matrix->typeInfo->size;
}

// Выводит матрицу
void print_matrix(const square_matrix* matrix) {
    if (!matrix || !matrix->data) return;
    for (int i = 0; i < matrix->size; i++) {
        for (int j = 0; j < matrix->size; j++) {
            void* ptr = get_element(matrix, i, j);
            matrix->typeInfo->print(ptr);
        }
        printf("\n");
    }
}