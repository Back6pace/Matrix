#include "test.h"

START_TEST(s21_dtr_test_1) {
  const int size = 5;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) A.matrix[i][j] = j;
  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(error, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_dtr_test_2) {
  const int size = 4;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);

  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++) A.matrix[i][j] = j + i;

  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq_tol(res, 0, 1e-6);
  ck_assert_int_eq(error, OK);

  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_dtr_test_3) {
  const int size = 5;
  matrix_t A = {0};
  s21_create_matrix(size, size, &A);
  A.matrix[0][1] = 6;
  A.matrix[0][2] = -2;
  A.matrix[0][3] = -1;
  A.matrix[0][4] = 5;
  A.matrix[1][3] = -9;
  A.matrix[1][4] = -7;
  A.matrix[2][1] = 15;
  A.matrix[2][2] = 35;
  A.matrix[3][1] = -1;
  A.matrix[3][2] = -11;
  A.matrix[3][3] = -2;
  A.matrix[3][4] = 1;
  A.matrix[4][0] = -2;
  A.matrix[4][1] = -2;
  A.matrix[4][2] = 3;
  A.matrix[4][4] = -2;

  double res = 0;
  int error = s21_determinant(&A, &res);
  ck_assert_double_eq_tol(res, 2480, 1e-6);
  ck_assert_int_eq(error, OK);

  s21_remove_matrix(&A);
}
END_TEST

Suite *test_dtr() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_DETERMINANT=-\033[0m");
  TCase *tc = tcase_create("case_dtr");
  tcase_add_test(tc, s21_dtr_test_1);
  tcase_add_test(tc, s21_dtr_test_2);
  tcase_add_test(tc, s21_dtr_test_3);
  suite_add_tcase(s, tc);
  return s;
}