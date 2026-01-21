#include "test.h"

START_TEST(det_1x1) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  int code = s21_determinant(&A, &res);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_double_eq_tol(res, 5.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_2x2) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  int code = s21_determinant(&A, &res);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_double_eq_tol(res, -2.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_3x3) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 5;
  A.matrix[2][0] = 1;
  A.matrix[2][1] = 0;
  A.matrix[2][2] = 6;

  int code = s21_determinant(&A, &res);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_double_eq_tol(res, 22.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_with_pivot) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 0;
  A.matrix[1][2] = 3;
  A.matrix[2][0] = 4;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = 6;

  int code = s21_determinant(&A, &res);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_double_eq_tol(res, 17.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_zero) {
  matrix_t A;
  double res = 123.0;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 6;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  A.matrix[2][2] = 9;

  int code = s21_determinant(&A, &res);

  ck_assert_int_eq(code, MATRIX_SUCCESS);
  ck_assert_double_eq_tol(res, 0.0, 1e-7);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_not_square) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(2, 3, &A);

  int code = s21_determinant(&A, &res);

  ck_assert_int_eq(code, MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(det_null) {
  double res = 0;

  ck_assert_int_eq(s21_determinant(NULL, &res), MATRIX_CALCULATION_ERROR);

  ck_assert_int_eq(s21_determinant(NULL, NULL), MATRIX_CALCULATION_ERROR);
}
END_TEST

Suite* test_suite_determinant(void) {
  Suite* s = suite_create("determinant");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, det_1x1);
  tcase_add_test(tc, det_2x2);
  tcase_add_test(tc, det_3x3);
  tcase_add_test(tc, det_with_pivot);
  tcase_add_test(tc, det_zero);
  tcase_add_test(tc, det_not_square);
  tcase_add_test(tc, det_null);

  suite_add_tcase(s, tc);
  return s;
}
