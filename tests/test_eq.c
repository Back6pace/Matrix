#include "test.h"

START_TEST(s21_eq_test_1) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_2) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(4, 4, &A);
  s21_create_matrix(4, 4, &B);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      A.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      B.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_3) {
  matrix_t A = {0};
  matrix_t B = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      A.matrix[i][j] = i + j;
      B.matrix[i][j] = i + j;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_4) {
  matrix_t A = {0};
  matrix_t B = {0};
  const int rows = rand() % 100 + 1;
  const int columns = rand() % 100 + 1;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < columns; ++j) {
      int rand_value = get_rand(DBL_MIN, DBL_MAX);
      A.matrix[i][j] = rand_value;
      B.matrix[i][j] = rand_value;
    }
  }
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_5) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 1, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 3.05;
  A.matrix[1][0] = 0.0;
  B.matrix[0][0] = 3.05;
  B.matrix[0][1] = 4.0521314;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = -1.321423;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_6) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 3.05;
  A.matrix[0][1] = 4.0521314;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = -1.321423;
  B.matrix[0][0] = 3.05;
  B.matrix[0][1] = 4.0521314;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = -1.321423;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_7) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(2, 2, &B);
  A.matrix[0][0] = 3.05;
  A.matrix[0][1] = 4.0521314;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = -1.321423;
  B.matrix[0][0] = 3.05;
  B.matrix[0][1] = 4.0521314;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = -1.321423;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_8) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(2, 2, &A);
  s21_create_matrix(1, 2, &B);
  A.matrix[0][0] = 3.05;
  A.matrix[0][1] = 4.0521314;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = -1.321423;
  B.matrix[0][0] = 3.05;
  B.matrix[0][1] = 4.0521314;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_9) {
  matrix_t A = {0};
  matrix_t B = {0};
  const int rows = (rand() % 100 + 1) * -1;
  const int columns = (rand() % 100 + 1) * -1;
  s21_create_matrix(rows, columns, &A);
  const int rows_1 = rand() % 100 + 1;
  const int columns_1 = rand() % 100 + 1;
  s21_create_matrix(rows_1, columns_1, &B);
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(s21_eq_test_10) {
  matrix_t A = {0};
  matrix_t B = {0};
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, FAILURE);
}
END_TEST

START_TEST(s21_eq_test_11) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  int value = get_rand(DBL_MIN, DBL_MAX);
  A.matrix[0][0] = value;
  B.matrix[0][0] = value;
  int res = s21_eq_matrix(&A, &B);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

Suite *test_eq() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_EQ=-\033[0m");
  TCase *tc = tcase_create("case_eq_matrix");
  tcase_add_test(tc, s21_eq_test_1);
  tcase_add_test(tc, s21_eq_test_2);
  tcase_add_test(tc, s21_eq_test_3);
  tcase_add_test(tc, s21_eq_test_4);
  tcase_add_test(tc, s21_eq_test_5);
  tcase_add_test(tc, s21_eq_test_6);
  tcase_add_test(tc, s21_eq_test_7);
  tcase_add_test(tc, s21_eq_test_8);
  tcase_add_test(tc, s21_eq_test_9);
  tcase_add_test(tc, s21_eq_test_10);
  tcase_add_test(tc, s21_eq_test_11);
  suite_add_tcase(s, tc);
  return s;
}