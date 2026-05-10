#include <stdio.h>
#include <stdlib.h>
#include "type_info_double.h"
#include "type_info_complex.h"
#include "square_matrix.h"
#include "operations.h"
#include "errors.h"

int run_all_tests();


static void safe_input(void* value_ptr, int is_double) {
    int res;
    while (1) {
        if (is_double) {
            res = scanf("%lf", (double*)value_ptr);
        } 
        
        else {
            res = scanf("%d", (int*)value_ptr);
        }

        int c;
        while ((c = getchar()) != '\n' && c != EOF);

        if (res == 1) {
            break;
        } 
        
        else {
            printf("Invalid input. Please try again: ");
        }
    }
}

// Выбор типа элементов матрицы
static const type_info* choose_type() {
    int choice;
    printf("\nChoose element type:\n");
    printf("1 - double (real numbers)\n");
    printf("2 - complex (complex numbers)\n");

    while (1) {
        printf("Your choice (1 or 2): ");
        safe_input(&choice, 0);
        if (choice == 1) return get_double_type_info();
        if (choice == 2) return get_complex_type_info();
        printf("Error: input must be 1 or 2.\n");
    }
}

// Заполняет матрицу значениями
static void fill_matrix(square_matrix* m, const char* name) {
    if (!m || !m->data) return;
    printf("\nFilling matrix %s\n", name);

    for (int i = 0; i < m->size; i++) {
        for (int j = 0; j < m->size; j++) {
            if (m->typeInfo == get_double_type_info()) {
                double val;
                printf("%s[%d][%d] = ", name, i, j);
                safe_input(&val, 1);
                set_element(m, i, j, &val);
            } 
            
            else { // Complex
                Complex val;
                printf("%s[%d][%d] Re = ", name, i, j);
                safe_input(&val.re, 1);
                printf("%s[%d][%d] Im = ", name, i, j);
                safe_input(&val.im, 1);
                set_element(m, i, j, &val);
            }
        }
    }
    printf("Matrix %s has been filled!\n", name);
}

// Ввод скаляра
static void input_scalar(const type_info* ti, void* scalar) {
    if (ti == get_double_type_info()) {
        printf("Enter a real number: ");
        safe_input(scalar, 1);
    } 
    
    else { // Complex
        Complex* c = (Complex*)scalar;
        printf("Enter the real part: ");
        safe_input(&c->re, 1);
        printf("Enter the imaginary part: ");
        safe_input(&c->im, 1);
    }
}

void print_menu() {
    printf("\n======================= Menu =========================\n");
    printf("| 1 - Initialize matrix A                              |\n");
    printf("| 2 - Initialize matrix B                              |\n");
    printf("| 3 - Fill matrix A                                    |\n");
    printf("| 4 - Fill matrix B                                    |\n");
    printf("| 5 - Show matrices A and B                            |\n");
    printf("| 6 - Add matrices (C = A + B)                         |\n");
    printf("| 7 - Multiply matrices (C = A * B)                    |\n");
    printf("| 8 - Multiply a matrix by a scalar                    |\n");
    printf("| 9 - Run tests                                        |\n");
    printf("| 0 - Exit                                             |\n");
    printf("========================================================\n");
    printf("Your choice: ");
}

int main() {
    square_matrix A = {0};
    square_matrix B = {0};

    run_all_tests();

    int choice = -1;
    while (choice != 0) {
        print_menu();
        safe_input(&choice, 0);

        switch (choice) {
            case 1: {
                if (A.data) {
                    free_matrix(&A);
                }

                printf("\n--- Matrix A Initialization ---\n");
                const type_info* ti = choose_type();
                int size;
                while (1) {
                    printf("Enter matrix dimension (N > 0): ");
                    safe_input(&size, 0);
                    if (size > 0) break;
                    printf("Dimension must be greater than zero!\n");
                }

                init_matrix(&A, size, ti);

                if (A.data) {
                    printf("\nMatrix A (%dx%d) created successfully!\n", size, size);
                } 
                
                else {
                    printf("\nMemory allocation error for Matrix A!\n");
                }
                break;
            }

            case 2: {
                if (B.data) {
                    free_matrix(&B);
                }
                
                printf("\n--- Matrix B Initialization ---\n");
                const type_info* ti = choose_type();
                int size;
                while (1) {
                    printf("Enter matrix dimension (N > 0): ");
                    safe_input(&size, 0);
                    if (size > 0) break;
                    printf("Dimension must be greater than zero!\n");
                }

                init_matrix(&B, size, ti);
                
                if (B.data) {
                    printf("\nMatrix B (%dx%d) created successfully!\n", size, size);
                } 
                
                else {
                    printf("\nMemory allocation error for Matrix B!\n");
                }

                break;
            }
            
            case 3:
                if (!A.data) {
                    printf("\nInitialize matrix A first (option 1)!\n");
                } 
                
                else {
                    fill_matrix(&A, "A");
                }
                break;
                
            case 4:
                if (!B.data) {
                    printf("\nInitialize matrix B first (option 2)!\n");
                } 
                
                else {
                    fill_matrix(&B, "B");
                }
                break;
                
            case 5:
                if (!A.data && !B.data) {
                    printf("\nInitialize matrices first (options 1 or 2)!\n");
                    break;
                }

                if (A.data) {
                    printf("\nMatrix A:\n");
                    print_matrix(&A);
                } 
                
                else {
                    printf("\nMatrix A is not initialized.\n");
                }

                if (B.data) {
                    printf("\nMatrix B:\n");
                    print_matrix(&B);
                } 
                
                else {
                    printf("\nMatrix B is not initialized.\n");
                }
                break;
                
            case 6: {
                if (!A.data || !B.data) {
                    printf("\nInitialize both matrices first (options 1 and 2)!\n");
                    break;
                }

                square_matrix C = {0};
                init_matrix(&C, A.size, A.typeInfo);

                if (C.data) {
                    OpStatus status = add_matrices(&C, &A, &B);
                    if (status == OP_SUCCESS) {
                        printf("\nAddition result (A + B):\n");
                        print_matrix(&C);
                    } 
                    
                    else {
                        print_op_error(status);
                    }
                    free_matrix(&C);
                } 
                
                else {
                    printf("\nError during matrix addition (memory allocation)!\n");
                }
                break;
            }
            
            case 7: {
                if (!A.data || !B.data) {
                    printf("\nInitialize both matrices first (options 1 and 2)!\n");
                    break;
                }

                square_matrix C = {0};
                init_matrix(&C, A.size, A.typeInfo);

                if (C.data) {
                    OpStatus status = multiply_matrices(&C, &A, &B);
                    if (status == OP_SUCCESS) {
                        printf("\nMultiplication result (A * B):\n");
                        print_matrix(&C);
                    } 
                    
                    else {
                        print_op_error(status);
                    }
                    free_matrix(&C);
                } 
                
                else {
                    printf("\nError during matrix multiplication (memory allocation)!\n");
                }
                break;
            }
            
            case 8: {
                if (!A.data && !B.data) {
                    printf("\nInitialize at least one matrix first (options 1 or 2)!\n");
                    break;
                }

                square_matrix* targetMatrix = NULL;
                if (A.data && B.data) {
                    int matrixChoice;
                    while(1) {
                        printf("\nChoose matrix to multiply by scalar (1 for A, 2 for B): ");
                        safe_input(&matrixChoice, 0);
                        if (matrixChoice == 1) {
                            targetMatrix = &A;
                            break;
                        } 
                        
                        if (matrixChoice == 2) {
                            targetMatrix = &B;
                            break;
                        }
                        printf("Error: input must be 1 or 2.\n");
                    }
                }

                else if (A.data) {
                    targetMatrix = &A;
                }

                else {
                    targetMatrix = &B;
                }

                void* scalar = malloc(targetMatrix->typeInfo->size);
                if (!scalar) {
                    printf("\nMemory allocation error!\n");
                    break;
                }
                
                input_scalar(targetMatrix->typeInfo, scalar);
                
                square_matrix C = {0};
                init_matrix(&C, targetMatrix->size, targetMatrix->typeInfo);

                if (C.data) {
                    OpStatus status = matrix_by_scalar(&C, targetMatrix, scalar);
                    if (status == OP_SUCCESS) {
                        printf("\nScalar multiplication result:\n");
                        print_matrix(&C);
                    } 
                    
                    else {
                        print_op_error(status);
                    }
                    free_matrix(&C);
                } 
                
                else {
                    printf("\nError during multiplication (memory allocation)!\n");
                }

                free(scalar);
                break;
            }
            
            case 9:
                run_all_tests();
                break;

            case 0:
                break;
                
            default:
                printf("\nInvalid menu option. Please try again.\n");
                break;
        }
    }

    if (A.data) free_matrix(&A);
    if (B.data) free_matrix(&B);
    
    return 0;
}