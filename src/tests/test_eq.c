#include "test.h"

START_TEST(test_eq_matrix_2x2_equal) {
  matrix_t A, B;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_2x2_not_equal) {
  matrix_t A, B;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 5.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_different_size) {
  matrix_t A, B;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(3, 2, &B);

  ck_assert_int_eq(s21_eq_matrix(&A, &B), FAILURE);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_float_precision) {
  matrix_t A, B;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);

  A.matrix[0][0] = 1.00000001;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  B.matrix[0][0] = 1.0;
  B.matrix[0][1] = 2.0;
  B.matrix[1][0] = 3.0;
  B.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_eq_matrix(&A, &B), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(test_eq_matrix_null_matrix) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_eq_matrix(NULL, &A), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(&A, NULL), FAILURE);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FAILURE);

  s21_remove_matrix(&A);
}
END_TEST

Suite* test_suite_eq(void) {
  Suite* s = suite_create("eq");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_eq_matrix_2x2_equal);
  tcase_add_test(tc, test_eq_matrix_2x2_not_equal);
  tcase_add_test(tc, test_eq_matrix_different_size);
  tcase_add_test(tc, test_eq_matrix_float_precision);
  tcase_add_test(tc, test_eq_matrix_null_matrix);

  suite_add_tcase(s, tc);
  return s;
}
