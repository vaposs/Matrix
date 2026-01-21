#include "test.h"

START_TEST(test_sub_matrix_2x2) {
  matrix_t A, B, R;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 5;
  A.matrix[0][1] = 7;
  A.matrix[1][0] = 9;
  A.matrix[1][1] = 11;

  B.matrix[0][0] = 1;
  B.matrix[0][1] = 2;
  B.matrix[1][0] = 3;
  B.matrix[1][1] = 4;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), MATRIX_SUCCESS);

  ck_assert_double_eq(R.matrix[0][0], 4);
  ck_assert_double_eq(R.matrix[0][1], 5);
  ck_assert_double_eq(R.matrix[1][0], 6);
  ck_assert_double_eq(R.matrix[1][1], 7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_sub_matrix_1x1) {
  matrix_t A, B, R;

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 10.5;
  B.matrix[0][0] = 2.5;

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), MATRIX_SUCCESS);
  ck_assert_double_eq(R.matrix[0][0], 8.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_sub_matrix_different_size) {
  matrix_t A, B, R;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_invalid_matrix) {
  matrix_t A, B, R;

  A.rows = 0;
  A.columns = 2;
  A.matrix = NULL;

  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, &R), MATRIX_ERROR);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_null_result) {
  matrix_t A, B;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_sub_matrix(&A, &B, NULL), MATRIX_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_sub_matrix_null_inputs) {
  matrix_t A, R;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_sub_matrix(NULL, &A, &R), MATRIX_ERROR);

  ck_assert_int_eq(s21_sub_matrix(&A, NULL, &R), MATRIX_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

Suite* test_suite_sub(void) {
  Suite* s = suite_create("sub");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_sub_matrix_2x2);
  tcase_add_test(tc, test_sub_matrix_1x1);
  tcase_add_test(tc, test_sub_matrix_different_size);
  tcase_add_test(tc, test_sub_matrix_invalid_matrix);
  tcase_add_test(tc, test_sub_matrix_null_result);
  tcase_add_test(tc, test_sub_matrix_null_inputs);

  suite_add_tcase(s, tc);
  return s;
}
