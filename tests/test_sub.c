#include "test.h"

START_TEST(s21_sub_test_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  s21_create_matrix(4, 4, &C);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), SUCCESS);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_sub_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t D = {0};
  const int rows_a = rand() % 100 + 1;
  const int columns_a = rand() % 100 + 1;
  s21_create_matrix(rows_a, columns_a, &A);
  const int rows_b = rand() % 100 + 1;
  const int columns_b = rand() % 100 + 1;
  s21_create_matrix(rows_b, columns_b, &B);
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(res, FAILED_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_sub_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t D = {0};
  matrix_t C = {0};
  const int rows = (rand() % 100 + 1) * -1;
  const int columns = (rand() % 100 + 1) * -1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &C);
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_sub_test_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t D = {0};
  matrix_t C = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  s21_create_matrix(rows, columns, &C);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      A.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      B.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      C.matrix[i][j] = A.matrix[i][j] - B.matrix[i][j];
    }
  }
  int res = s21_sub_matrix(&A, &B, &D);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

Suite* test_sub() {
  Suite* s = suite_create("\033[36m-=S21_MATRIX_SUB=-\033[0m");
  TCase* tc1_1 = tcase_create("case_sub_matrix");
  tcase_add_test(tc1_1, s21_sub_test_1);
  tcase_add_test(tc1_1, s21_sub_test_2);
  tcase_add_test(tc1_1, s21_sub_test_3);
  tcase_add_test(tc1_1, s21_sub_test_4);
  suite_add_tcase(s, tc1_1);
  return s;
}