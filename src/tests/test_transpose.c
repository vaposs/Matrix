#include "test.h"

START_TEST(test_transpose_2x2) {
  matrix_t A, R;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  ck_assert_int_eq(s21_transpose(&A, &R), MATRIX_SUCCESS);

  ck_assert_double_eq(R.matrix[0][0], 1);
  ck_assert_double_eq(R.matrix[0][1], 3);
  ck_assert_double_eq(R.matrix[1][0], 2);
  ck_assert_double_eq(R.matrix[1][1], 4);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_transpose_3x2) {
  matrix_t A, R;

  s21_create_matrix(3, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;

  ck_assert_int_eq(s21_transpose(&A, &R), MATRIX_SUCCESS);

  ck_assert_int_eq(R.rows, 2);
  ck_assert_int_eq(R.columns, 3);

  ck_assert_double_eq(R.matrix[0][0], 1);
  ck_assert_double_eq(R.matrix[0][1], 3);
  ck_assert_double_eq(R.matrix[0][2], 5);
  ck_assert_double_eq(R.matrix[1][0], 2);
  ck_assert_double_eq(R.matrix[1][1], 4);
  ck_assert_double_eq(R.matrix[1][2], 6);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_transpose_1x1) {
  matrix_t A, R;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 42;

  ck_assert_int_eq(s21_transpose(&A, &R), MATRIX_SUCCESS);
  ck_assert_double_eq(R.matrix[0][0], 42);
  ck_assert_int_eq(R.rows, 1);
  ck_assert_int_eq(R.columns, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_transpose_null_result) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_transpose(&A, NULL), MATRIX_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_transpose_invalid_matrix) {
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  A.matrix = NULL;

  matrix_t R;
  ck_assert_int_eq(s21_transpose(&A, &R), MATRIX_ERROR);
}
END_TEST

Suite* test_suite_transpose(void) {
  Suite* s = suite_create("transpose");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_transpose_2x2);
  tcase_add_test(tc, test_transpose_3x2);
  tcase_add_test(tc, test_transpose_1x1);
  tcase_add_test(tc, test_transpose_null_result);
  tcase_add_test(tc, test_transpose_invalid_matrix);

  suite_add_tcase(s, tc);
  return s;
}
