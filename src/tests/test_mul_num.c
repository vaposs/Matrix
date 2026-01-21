#include "test.h"

START_TEST(test_mult_number_2x2_positive) {
  matrix_t A, R;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  ck_assert_int_eq(s21_mult_number(&A, 2.0, &R), MATRIX_SUCCESS);

  ck_assert_double_eq(R.matrix[0][0], 2.0);
  ck_assert_double_eq(R.matrix[0][1], 4.0);
  ck_assert_double_eq(R.matrix[1][0], 6.0);
  ck_assert_double_eq(R.matrix[1][1], 8.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_number_2x2_negative) {
  matrix_t A, R;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = -2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = -4;

  ck_assert_int_eq(s21_mult_number(&A, -2.0, &R), MATRIX_SUCCESS);

  ck_assert_double_eq(R.matrix[0][0], -2.0);
  ck_assert_double_eq(R.matrix[0][1], 4.0);
  ck_assert_double_eq(R.matrix[1][0], -6.0);
  ck_assert_double_eq(R.matrix[1][1], 8.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_number_2x2_zero) {
  matrix_t A, R;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  ck_assert_int_eq(s21_mult_number(&A, 0.0, &R), MATRIX_SUCCESS);

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++) ck_assert_double_eq(R.matrix[i][j], 0.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_number_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_mult_number(&A, 2.0, NULL), MATRIX_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_mult_number_invalid_matrix) {
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  A.matrix = NULL;

  matrix_t R;
  ck_assert_int_eq(s21_mult_number(&A, 2.0, &R), MATRIX_ERROR);
}
END_TEST

Suite* test_suite_mul_num(void) {
  Suite* s = suite_create("mul_num");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_mult_number_2x2_positive);
  tcase_add_test(tc, test_mult_number_2x2_negative);
  tcase_add_test(tc, test_mult_number_2x2_zero);
  tcase_add_test(tc, test_mult_number_null_result);
  tcase_add_test(tc, test_mult_number_invalid_matrix);

  suite_add_tcase(s, tc);
  return s;
}
