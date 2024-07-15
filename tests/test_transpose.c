#include "test.h"

START_TEST(s21_transpose_test_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 2, &A);
  s21_create_matrix(2, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[1][0] = 3;
  A.matrix[1][1] = 4;
  A.matrix[2][0] = 5;
  A.matrix[2][1] = 6;

  double check[2][3] = {{1, 3, 5}, {2, 4, 6}};
  for (int i = 0; i < C.rows; ++i) {
    for (int j = 0; j < C.columns; ++j) {
      C.matrix[i][j] = check[i][j];
    }
  }
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_transpose_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(columns, rows, &C);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      double value = get_rand(DBL_MIN, DBL_MAX);
      A.matrix[i][j] = value;
      C.matrix[j][i] = value;
    }
  }
  int res = s21_transpose(&A, &B);
  ck_assert_int_eq(res, OK);
  ck_assert_int_eq(s21_eq_matrix(&C, &B), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_transpose_test_3) {
  int rows = (rand() % 100 + 1) * -1;
  int cols = (rand() % 100 + 1) * -1;
  matrix_t A = {0};
  s21_create_matrix(rows, cols, &A);
  matrix_t C = {0};
  s21_create_matrix(cols, rows, &C);

  matrix_t D = {0};
  ck_assert_int_eq(s21_transpose(&A, &D), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

Suite *test_transpose() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_TRANSPOSE=-\033[0m");
  TCase *tc = tcase_create("case_transpose");
  tcase_add_test(tc, s21_transpose_test_1);
  tcase_add_test(tc, s21_transpose_test_2);
  tcase_add_test(tc, s21_transpose_test_3);
  suite_add_tcase(s, tc);
  return s;
}