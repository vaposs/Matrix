#include "test.h"

START_TEST(test_det_2x2_simple) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[1][0] = 3.0;
  A.matrix[1][1] = 4.0;

  ck_assert_int_eq(s21_determinant(&A, &res), 0);
  ck_assert_double_eq(res, -2.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_det_3x3_zero) {
  matrix_t A;
  double res = 1;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 7.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 9.0;

  ck_assert_int_eq(s21_determinant(&A, &res), 0);
  ck_assert_double_eq(res, 0.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_det_3x3_nonzero) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 6.0;
  A.matrix[0][1] = 1.0;
  A.matrix[0][2] = 1.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = -2.0;
  A.matrix[1][2] = 5.0;
  A.matrix[2][0] = 2.0;
  A.matrix[2][1] = 8.0;
  A.matrix[2][2] = 7.0;

  ck_assert_int_eq(s21_determinant(&A, &res), 0);
  ck_assert_double_eq(res, -306);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_det_need_pivot) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 1.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 0.0;

  ck_assert_int_eq(s21_determinant(&A, &res), 0);
  ck_assert_double_eq(res, 31.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_det_1x1) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 5.0;

  ck_assert_int_eq(s21_determinant(&A, &res), 0);
  ck_assert_double_eq(res, 5.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_det_not_square) {
  matrix_t A;
  double res = 0;

  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_determinant(&A, &res), 2);

  s21_remove_matrix(&A);
}
END_TEST

Suite* test_suite_det(void) {
  Suite* s = suite_create("det");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_det_2x2_simple);
  tcase_add_test(tc, test_det_3x3_zero);
  tcase_add_test(tc, test_det_3x3_nonzero);
  tcase_add_test(tc, test_det_need_pivot);
  tcase_add_test(tc, test_det_1x1);
  tcase_add_test(tc, test_det_not_square);

  suite_add_tcase(s, tc);
  return s;
}
