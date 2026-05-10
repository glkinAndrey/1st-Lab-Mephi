#include "type_info_double.h"
#include <stdio.h>
#include <stdlib.h>

// Выводит значение
static void print_double(const void* a) { printf("%7.2f ", *(const double*)a); }

// Складывает два значения
static void add_double(void* res, const void* a, const void* b) { *(double*)res = *(const double*)a + *(const double*)b; }

// Умножает два значения
static void mul_double(void* res, const void* a, const void* b) { *(double*)res = *(const double*)a * *(const double*)b; }

// Устанавливает значение в ноль
static void zero_double(void* res) { *(double*)res = 0.0; }

static type_info* doubleTypeInfo = NULL;

// Возвращает информацию о типе double
const type_info* get_double_type_info() {
    if (doubleTypeInfo == NULL) {
        doubleTypeInfo = (type_info*)malloc(sizeof(type_info));
        if (doubleTypeInfo!= NULL) {
            doubleTypeInfo->size = sizeof(double);
            doubleTypeInfo->print = print_double;
            doubleTypeInfo->add = add_double;
            doubleTypeInfo->mul = mul_double;
            doubleTypeInfo->zero = zero_double;
        }
    }
    return doubleTypeInfo;
}