#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <stddef.h>

typedef struct TypeInfo {
    size_t size;
    void (*print)(const void*);
    void (*add)(void* res, const void* a, const void* b);
    void (*mul)(void* res, const void* a, const void* b);
    void (*zero)(void* res);
} type_info;

#endif