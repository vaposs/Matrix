#include "test.h"

START_TEST(test_create_matrix_3x3) {
  matrix_t A;

  ck_assert_int_eq(s21_create_matrix(3, 3, &A), MATRIX_SUCCESS);

  ck_assert_int_eq(A.rows, 3);
  ck_assert_int_eq(A.columns, 3);
  ck_assert_ptr_nonnull(A.matrix);

  for (int i = 0; i < 3; i++) {
    ck_assert_ptr_nonnull(A.matrix[i]);
    for (int j = 0; j < 3; j++) ck_assert_double_eq(A.matrix[i][j], 0.0);
  }

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_1x1) {
  matrix_t A;

  ck_assert_int_eq(s21_create_matrix(1, 1, &A), MATRIX_SUCCESS);

  ck_assert_int_eq(A.rows, 1);
  ck_assert_int_eq(A.columns, 1);
  ck_assert_double_eq(A.matrix[0][0], 0.0);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(test_create_matrix_invalid_rows) {
  matrix_t A;

  ck_assert_int_eq(s21_create_matrix(0, 3, &A), MATRIX_ERROR);
}
END_TEST

START_TEST(test_create_matrix_invalid_columns) {
  matrix_t A;

  ck_assert_int_eq(s21_create_matrix(3, 0, &A), MATRIX_ERROR);
}
END_TEST

START_TEST(test_create_matrix_null_result) {
  ck_assert_int_eq(s21_create_matrix(2, 2, NULL), MATRIX_ERROR);
}
END_TEST

START_TEST(test_create_matrix_negative_sizes) {
  matrix_t A;

  ck_assert_int_eq(s21_create_matrix(-3, -5, &A), MATRIX_ERROR);
}
END_TEST

Suite* test_suite_create(void) {
  Suite* s = suite_create("create_matrix");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_create_matrix_3x3);
  tcase_add_test(tc, test_create_matrix_1x1);
  tcase_add_test(tc, test_create_matrix_invalid_rows);
  tcase_add_test(tc, test_create_matrix_invalid_columns);
  tcase_add_test(tc, test_create_matrix_null_result);
  tcase_add_test(tc, test_create_matrix_negative_sizes);

  suite_add_tcase(s, tc);
  return s;
}
