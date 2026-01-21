#include "test.h"

int main() {
  SRunner* sr = srunner_create(NULL);

  srunner_add_suite(sr, test_suite_add());
  srunner_add_suite(sr, test_suite_sub());
  srunner_add_suite(sr, test_suite_det());
  srunner_add_suite(sr, test_suite_minor());
  srunner_add_suite(sr, test_suite_remove());
  srunner_add_suite(sr, test_suite_create());
  srunner_add_suite(sr, test_suite_eq());
  srunner_add_suite(sr, test_suite_mul_num());
  srunner_add_suite(sr, test_suite_mul_mat());
  srunner_add_suite(sr, test_suite_transpose());
  srunner_add_suite(sr, test_suite_calc());
  srunner_add_suite(sr, test_suite_inverse());
  srunner_add_suite(sr, test_suite_determinant());

  srunner_run_all(sr, CK_NORMAL);

  srunner_ntests_failed(sr);

  srunner_free(sr);
}
