#include "test.h"

START_TEST(s21_mul_num_test_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  double value = get_rand(DBL_MIN, DBL_MAX);
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      A.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      C.matrix[i][j] = A.matrix[i][j] * value;
    }
  }
  int res = s21_mult_number(&A, value, &B);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mul_num_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  double value = 0;
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      A.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      C.matrix[i][j] = A.matrix[i][j] * value;
    }
  }
  int res = s21_mult_number(&A, value, &B);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mul_num_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  double value = 0;
  int res = s21_mult_number(&A, value, &B);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

Suite *test_mul_num() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_MUL_NUM=-\033[0m");
  TCase *tc = tcase_create("case_mul_num_matrix");
  tcase_add_test(tc, s21_mul_num_test_1);
  tcase_add_test(tc, s21_mul_num_test_2);
  tcase_add_test(tc, s21_mul_num_test_3);
  suite_add_tcase(s, tc);
  return s;
}