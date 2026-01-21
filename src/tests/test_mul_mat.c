#include "test.h"

START_TEST(test_mult_matrix_2x2) {
  matrix_t A, B, R;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  B.matrix[0][0] = 2;
  B.matrix[0][1] = 0;
  B.matrix[1][0] = 1;
  B.matrix[1][1] = 2;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), MATRIX_SUCCESS);

  ck_assert_double_eq(R.matrix[0][0], 4);   // 1*2 + 2*1 = 4
  ck_assert_double_eq(R.matrix[0][1], 4);   // 1*0 + 2*2 = 4
  ck_assert_double_eq(R.matrix[1][0], 10);  // 3*2 + 4*1 = 10
  ck_assert_double_eq(R.matrix[1][1], 8);   // 3*0 + 4*2 = 8

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_mult_matrix_wrong_size) {
  matrix_t A, B, R;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_null_result) {
  matrix_t A, B;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  ck_assert_int_eq(s21_mult_matrix(&A, &B, NULL), MATRIX_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_invalid_matrix) {
  matrix_t A;
  A.rows = 0;
  A.columns = 2;
  A.matrix = NULL;

  matrix_t B;
  s21_create_matrix(2, 2, &B);

  matrix_t R;
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), MATRIX_ERROR);

  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_mult_matrix_3x2_2x3) {
  matrix_t A, B, R;

  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &B);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;

  B.matrix[0][0] = 7;
  B.matrix[0][1] = 8;
  B.matrix[0][2] = 9;
  B.matrix[1][0] = 10;
  B.matrix[1][1] = 11;
  B.matrix[1][2] = 12;

  ck_assert_int_eq(s21_mult_matrix(&A, &B, &R), MATRIX_SUCCESS);

  // проверим некоторые элементы
  ck_assert_double_eq(R.matrix[0][0], 1 * 7 + 2 * 10);  // 27
  ck_assert_double_eq(R.matrix[1][1], 3 * 8 + 4 * 11);  // 65
  ck_assert_double_eq(R.matrix[2][2], 5 * 9 + 6 * 12);  // 123

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
}
END_TEST

Suite* test_suite_mul_mat(void) {
  Suite* s = suite_create("mul_mat");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_mult_matrix_2x2);
  tcase_add_test(tc, test_mult_matrix_wrong_size);
  tcase_add_test(tc, test_mult_matrix_null_result);
  tcase_add_test(tc, test_mult_matrix_invalid_matrix);
  tcase_add_test(tc, test_mult_matrix_3x2_2x3);

  suite_add_tcase(s, tc);
  return s;
}
