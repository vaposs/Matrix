#include "test.h"

START_TEST(test_calc_complements_2x2) {
  matrix_t A, R;

  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_SUCCESS);

  // дополнения 2×2: [[4, -3], [-2, 1]]
  ck_assert_double_eq(R.matrix[0][0], 4);
  ck_assert_double_eq(R.matrix[0][1], -3);
  ck_assert_double_eq(R.matrix[1][0], -2);
  ck_assert_double_eq(R.matrix[1][1], 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_3x3) {
  matrix_t A, R;

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 2;
  A.matrix[1][2] = 3;
  A.matrix[2][0] = 4;
  A.matrix[2][1] = 5;
  A.matrix[2][2] = 6;

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_SUCCESS);

  // известные дополнения (вычислены вручную)
  ck_assert_double_eq(R.matrix[0][0], -3);  // |4 2| |2 1| det = 0
  ck_assert_double_eq(R.matrix[0][1], 6);   // -(0*1-5*2) = 10
  ck_assert_double_eq(R.matrix[0][2], -3);  // |0 4| |5 2| det = -20

  ck_assert_double_eq(R.matrix[1][0], 3);
  ck_assert_double_eq(R.matrix[1][1], -6);
  ck_assert_double_eq(R.matrix[1][2], 3);

  ck_assert_double_eq(R.matrix[2][0], 0);
  ck_assert_double_eq(R.matrix[2][1], 0);
  ck_assert_double_eq(R.matrix[2][2], 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_1x1) {
  matrix_t A, R;

  s21_create_matrix(1, 1, &A);
  A.matrix[0][0] = 42;

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_SUCCESS);

  ck_assert_int_eq(R.rows, 1);
  ck_assert_int_eq(R.columns, 1);
  ck_assert_double_eq(R.matrix[0][0], 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_non_square) {
  matrix_t A, R;
  s21_create_matrix(2, 3, &A);

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_calc_complements_null) {
  matrix_t A;
  s21_create_matrix(2, 2, &A);

  ck_assert_int_eq(s21_calc_complements(NULL, &A), MATRIX_CALCULATION_ERROR);
  ck_assert_int_eq(s21_calc_complements(&A, NULL), MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
}
END_TEST

Suite* test_suite_calc(void) {
  Suite* s = suite_create("calc_complements");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_calc_complements_2x2);
  tcase_add_test(tc, test_calc_complements_3x3);
  tcase_add_test(tc, test_calc_complements_1x1);
  tcase_add_test(tc, test_calc_complements_non_square);
  tcase_add_test(tc, test_calc_complements_null);

  suite_add_tcase(s, tc);
  return s;
}
