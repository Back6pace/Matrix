#include "test.h"

START_TEST(s21_mul_matrix_test_1) {
  int rows = 4;
  int cols = 2;
  matrix_t A = {0};
  s21_create_matrix(rows, cols, &A);
  matrix_t B = {0};
  s21_create_matrix(cols, rows, &B);

  for (int i = 0; i < rows; i++)
    for (int j = 0; j < cols; j++) A.matrix[i][j] = get_rand(2, 10);

  for (int i = 0; i < cols; i++)
    for (int j = 0; j < rows; j++) B.matrix[i][j] = get_rand(2, 10);

  matrix_t C = {0};
  s21_create_matrix(A.rows, B.columns, &C);

  for (int i = 0; i < A.rows; i++) {
    for (int j = 0; j < B.columns; j++) {
      C.matrix[i][j] = 0;
      for (int k = 0; k < A.columns; k++)
        C.matrix[i][j] += A.matrix[i][k] * B.matrix[k][j];
    }
  }

  matrix_t D = {0};
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &D), OK);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mul_matrix_test_2) {
  const int rows = 2;
  const int cols = 3;
  matrix_t A = {0};
  s21_create_matrix(rows, cols, &A);
  matrix_t B = {0};
  s21_create_matrix(cols, rows, &B);

  for (int i = 0, c = 1; i < rows; i++)
    for (int j = 0; j < cols; j++) A.matrix[i][j] = c++;

  for (int i = 0, c = 7; i < cols; i++)
    for (int j = 0; j < rows; j++) B.matrix[i][j] = c++;

  matrix_t C = {0};
  s21_create_matrix(A.rows, B.columns, &C);
  C.matrix[0][0] = 58;
  C.matrix[0][1] = 64;
  C.matrix[1][0] = 139;
  C.matrix[1][1] = 154;

  matrix_t D = {0};
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &D), OK);
  ck_assert_int_eq(s21_eq_matrix(&C, &D), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_mul_matrix_test_3) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t A = {0};
  s21_create_matrix(rows, cols, &A);
  matrix_t B = {0};
  s21_create_matrix(cols, rows, &B);

  matrix_t C = {0};
  s21_create_matrix(A.rows, B.columns, &C);

  matrix_t D = {0};
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &D), INCORRECT_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_mul_matrix_test_4) {
  matrix_t A = {0};
  int rows = 2;
  int cols = 3;
  s21_create_matrix(rows, cols, &A);
  matrix_t B = {0};
  int rows1 = 4;
  int cols1 = 5;
  s21_create_matrix(rows1, cols1, &B);

  matrix_t C = {0};
  s21_create_matrix(A.rows, B.columns, &C);

  matrix_t D = {0};
  ck_assert_int_eq(s21_mult_matrix(&A, &B, &D), FAILED_MATRIX);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

Suite *test_mul_matrix() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_MUL_MATRIX=-\033[0m");
  TCase *tc = tcase_create("case_mul_matrix");
  tcase_add_test(tc, s21_mul_matrix_test_1);
  tcase_add_test(tc, s21_mul_matrix_test_2);
  tcase_add_test(tc, s21_mul_matrix_test_3);
  tcase_add_test(tc, s21_mul_matrix_test_4);
  suite_add_tcase(s, tc);
  return s;
}