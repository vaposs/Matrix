#ifndef TESTS
#define TESTS

#include <check.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../s21_matrix.h"

Suite* test_suite_add(void);
Suite* test_suite_sub(void);
Suite* test_suite_minor(void);
Suite* test_suite_det(void);
Suite* test_suite_create(void);
Suite* test_suite_remove(void);
Suite* test_suite_eq(void);
Suite* test_suite_mul_num(void);
Suite* test_suite_mul_mat(void);
Suite* test_suite_transpose(void);
Suite* test_suite_calc(void);
Suite* test_suite_inverse(void);
Suite* test_suite_determinant(void);

#endif
