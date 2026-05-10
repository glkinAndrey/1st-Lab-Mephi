#include "errors.h"
#include <stdio.h>

void print_op_error(OpStatus status) {
    switch (status) {
        case OP_SUCCESS:
            break;
        case OP_ERROR_NULL_POINTER:
            printf("\nError: Null pointer passed to operation.\n");
            break;
        case OP_ERROR_SIZE_MISMATCH:
            printf("\nError: Matrices sizes do not match!\n");
            break;
        case OP_ERROR_TYPE_MISMATCH:
            printf("\nError: Matrices types do not match!\n");
            break;
        case OP_ERROR_MEMORY:
            printf("\nError: Memory allocation failed during operation.\n");
            break;
        default:
            printf("\nError: Unknown operation error.\n");
            break;
    }
}