#include "test.h"

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

int main() {
  int failed = 0;
  Suite *s21_decimal_test[] = {test_create(),
                               test_eq(),
                               test_sum(),
                               test_sub(),
                               test_mul_num(),
                               test_mul_matrix(),
                               test_transpose(),
                               test_dtr(),
                               test_calc_compl(),
                               test_invert_matrix(),
                               NULL};

  for (int i = 0; s21_decimal_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_decimal_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return failed == 0 ? 0 : 1;
}
