#include "test.h"

START_TEST(s21_calc_compl_test_1) {
  matrix_t A = {0};
  matrix_t D = {0};
  s21_create_matrix(1, 1, &A);
  int res = s21_calc_complements(&A, &D);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_calc_compl_test_2) {
  matrix_t A = {0};
  matrix_t D = {0};
  int res = s21_calc_complements(&A, &D);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_calc_compl_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 2;
  A.matrix[0][2] = 3;

  A.matrix[1][0] = 0;
  A.matrix[1][1] = 4;
  A.matrix[1][2] = 2;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = 2;
  A.matrix[2][2] = 1;

  C.matrix[0][0] = 0;
  C.matrix[0][1] = 10;
  C.matrix[0][2] = -20;

  C.matrix[1][0] = 4;
  C.matrix[1][1] = -14;
  C.matrix[1][2] = 8;

  C.matrix[2][0] = -8;
  C.matrix[2][1] = -2;
  C.matrix[2][2] = 4;

  int error = s21_calc_complements(&A, &B);

  ck_assert_int_eq(s21_eq_matrix(&B, &C), SUCCESS);
  ck_assert_int_eq(error, OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

Suite *test_calc_compl() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_CALC_COMPL=-\033[0m");
  TCase *tc = tcase_create("case_calc_compl");
  tcase_add_test(tc, s21_calc_compl_test_1);
  tcase_add_test(tc, s21_calc_compl_test_2);
  tcase_add_test(tc, s21_calc_compl_test_3);
  suite_add_tcase(s, tc);
  return s;
}