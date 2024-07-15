#include "test.h"

START_TEST(s21_create_test_1) {
  matrix_t A = {0};
  int res = s21_create_matrix(-1, -1, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_test_2) {
  matrix_t A = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_test_3) {
  matrix_t A = {0};
  const int rows = 0;
  const int columns = 0;
  int res = s21_create_matrix(rows, columns, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_test_4) {
  matrix_t A = {0};
  int res = s21_create_matrix(4, 0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_test_5) {
  matrix_t A = {0};
  int res = s21_create_matrix(0, 50, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_test_6) {
  matrix_t A = {0};
  int res = s21_create_matrix(4, -1, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_test_7) {
  matrix_t A = {0};
  int res = s21_create_matrix(-0, -0, &A);
  ck_assert_int_eq(res, INCORRECT_MATRIX);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_create_test_8) {
  matrix_t A = {0};
  int res = s21_create_matrix(4, 4, &A);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&A);
}
END_TEST

Suite *test_create() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_CREATE=-\033[0m");
  TCase *tc = tcase_create("case_create_matrix");
  tcase_add_test(tc, s21_create_test_1);
  tcase_add_test(tc, s21_create_test_2);
  tcase_add_test(tc, s21_create_test_3);
  tcase_add_test(tc, s21_create_test_4);
  tcase_add_test(tc, s21_create_test_5);
  tcase_add_test(tc, s21_create_test_6);
  tcase_add_test(tc, s21_create_test_7);
  tcase_add_test(tc, s21_create_test_8);
  suite_add_tcase(s, tc);
  return s;
}