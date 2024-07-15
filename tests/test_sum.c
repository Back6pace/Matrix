#include "test.h"

START_TEST(s21_sum_test_1) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m1 = {0};
  s21_create_matrix(rows, cols, &m1);
  matrix_t m2 = {0};
  s21_create_matrix(rows, cols, &m2);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m1.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      m2.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m1.matrix[i][j] + m2.matrix[i][j];
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(s21_sum_test_2) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  s21_create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), FAILED_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(s21_sum_test_3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  matrix_t res = {0};

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *test_sum() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_SUM=-\033[0m");
  TCase *tc = tcase_create("case_sum_matrix");
  tcase_add_test(tc, s21_sum_test_1);
  tcase_add_test(tc, s21_sum_test_2);
  tcase_add_test(tc, s21_sum_test_3);
  suite_add_tcase(s, tc);
  return s;
}