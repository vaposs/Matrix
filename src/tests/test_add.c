#include "test.h"

START_TEST(test_sum_matrix_2x2) {
  matrix_t A, B, R;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 5;
  B.matrix[0][1] = 6;
  B.matrix[1][0] = 7;
  B.matrix[1][1] = 8;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), MATRIX_SUCCESS);

  ck_assert_double_eq(R.matrix[0][0], 6);
  ck_assert_double_eq(R.matrix[0][1], 8);
  ck_assert_double_eq(R.matrix[1][0], 10);
  ck_assert_double_eq(R.matrix[1][1], 12);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_sum_matrix_1x1) {
  matrix_t A, B, R;

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 2.5;
  B.matrix[0][0] = 3.5;

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), MATRIX_SUCCESS);
  ck_assert_double_eq(R.matrix[0][0], 6.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_sum_matrix_different_size) {
  matrix_t A, B, R;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_invalid_matrix) {
  matrix_t A, B, R;

  A.rows = 0;
  A.columns = 2;
  A.matrix = NULL;

  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, &R), MATRIX_ERROR);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_null_result) {
  matrix_t A, B;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sum_matrix(&A, &B, NULL), MATRIX_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sum_matrix_null_inputs) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_sum_matrix(NULL, &A, &R), MATRIX_ERROR);

  ck_assert_int_eq(s21_sum_matrix(&A, NULL, &R), MATRIX_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

Suite* test_suite_add(void) {
  Suite* s = suite_create("add");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_sum_matrix_2x2);
  tcase_add_test(tc, test_sum_matrix_1x1);
  tcase_add_test(tc, test_sum_matrix_different_size);
  tcase_add_test(tc, test_sum_matrix_invalid_matrix);
  tcase_add_test(tc, test_sum_matrix_null_result);
  tcase_add_test(tc, test_sum_matrix_null_inputs);

  suite_add_tcase(s, tc);
  return s;
}
