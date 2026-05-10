#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "square_matrix.h"
#include "errors.h"

OpStatus add_matrices(square_matrix* res, const square_matrix* a, const square_matrix* b);

OpStatus multiply_matrices(square_matrix* res, const square_matrix* a, const square_matrix* b);

OpStatus matrix_by_scalar(square_matrix* res, const square_matrix* a, const void* scalar);

#endif