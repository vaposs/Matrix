#include "test.h"

START_TEST(inverse_2x2) {
  matrix_t A, inv, expected;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &expected);

  A.matrix[0][0] = 4;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 6;

  expected.matrix[0][0] = 0.6;
  expected.matrix[0][1] = -0.7;
  expected.matrix[1][0] = -0.2;
  expected.matrix[1][1] = 0.4;

  int code = s21_inverse_matrix(&A, &inv);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&inv, &expected), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&inv);
  s21_remove_matrix(&expected);
}
END_TEST

START_TEST(inverse_det_zero) {
  matrix_t A, inv;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;

  int code = s21_inverse_matrix(&A, &inv);

  ck_assert_int_eq(code, MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(inverse_identity) {
  matrix_t A, inv;

  s21_create_matrix(3, 3, &A);
  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = (i == j) ? 1.0 : 0.0;

  int code = s21_inverse_matrix(&A, &inv);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_int_eq(s21_eq_matrix(&A, &inv), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&inv);
}
END_TEST

START_TEST(inverse_1x1) {
  matrix_t A, inv;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int code = s21_inverse_matrix(&A, &inv);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_double_eq_tol(inv.matrix[0][0], 0.2, 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&inv);
}
END_TEST

Suite* test_suite_inverse(void) {
  Suite* s = suite_create("inverse_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, inverse_2x2);
  tcase_add_test(tc, inverse_det_zero);
  tcase_add_test(tc, inverse_identity);
  tcase_add_test(tc, inverse_1x1);

  suite_add_tcase(s, tc);
  return s;
}
