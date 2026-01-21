#include "test.h"

START_TEST(test_remove_matrix_normal) {
  matrix_t A;

  s21_create_matrix(3, 3, &A);
  ck_assert_ptr_nonnull(A.matrix);

  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_double_call) {
  matrix_t A;

  s21_create_matrix(2, 2, &A);
  s21_remove_matrix(&A);

  /* второй вызов не должен падать */
  s21_remove_matrix(&A);

  ck_assert_ptr_null(A.matrix);
  ck_assert_int_eq(A.rows, 0);
  ck_assert_int_eq(A.columns, 0);
}
END_TEST

START_TEST(test_remove_matrix_null_pointer) { s21_remove_matrix(NULL); }
END_TEST

Suite* test_suite_remove(void) {
  Suite* s = suite_create("remove");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, test_remove_matrix_normal);
  tcase_add_test(tc, test_remove_matrix_double_call);
  tcase_add_test(tc, test_remove_matrix_null_pointer);

  suite_add_tcase(s, tc);
  return s;
}
