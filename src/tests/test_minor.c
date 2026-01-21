#include "test.h"

START_TEST(test_calc_complements_1x1) {
  matrix_t A, R;

  s21_create_matrix(1, 1, &A);

  A.matrix[0][0] = 5.0;

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_SUCCESS);
  ck_assert_double_eq(R.matrix[0][0], 1.0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_2x2) {
  matrix_t A, R;

  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &R);

  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_SUCCESS);

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
  s21_create_matrix(3, 3, &R);

  double data[3][3] = {{1, 2, 3}, {0, 4, 2}, {5, 2, 1}};

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++) A.matrix[i][j] = data[i][j];

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_SUCCESS);

  double expected[3][3] = {{0, 10, -20}, {4, -14, 8}, {-8, -2, 4}};

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      ck_assert_double_eq(R.matrix[i][j], expected[i][j]);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_calc_complements_not_square) {
  matrix_t A, R;

  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &R);

  ck_assert_int_eq(s21_calc_complements(&A, &R), MATRIX_CALCULATION_ERROR);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
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

Suite* test_suite_minor(void) {
  Suite* s = suite_create("minor");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_calc_complements_1x1);
  tcase_add_test(tc, test_calc_complements_2x2);
  tcase_add_test(tc, test_calc_complements_3x3);
  tcase_add_test(tc, test_calc_complements_not_square);
  tcase_add_test(tc, test_calc_complements_null);

  suite_add_tcase(s, tc);
  return s;
}
