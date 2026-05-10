cmake_minimum_required(VERSION 3.10)
project(first_lab C)

set(CMAKE_C_STANDARD 11)

add_executable(first_lab
    main.c
    square_matrix.c
    operations.c
    errors.c
    type_info_double.c
    type_info_complex.c
    tests.c
)
target_compile_options(first_lab PRIVATE "-finput-charset=UTF-8" "-fexec-charset=UTF-8")

add_executable(run_tests
    tests.c
    square_matrix.c
    operations.c
    errors.c
    type_info_double.c
    type_info_complex.c
)
target_compile_definitions(run_tests PRIVATE RUN_TESTS_MAIN)
target_compile_options(run_tests PRIVATE "-finput-charset=UTF-8" "-fexec-charset=UTF-8")