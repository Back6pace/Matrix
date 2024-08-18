#include "test_main.h"

START_TEST(s21_inverse_matrix_test_1) {
  matrix_t A = {0};
  matrix_t D = {0};
  s21_create_matrix(1, 5, &A);
  int error = s21_inverse_matrix(&A, &D);
  ck_assert_int_eq(error, S21_CALC_ERROR);
  s21_remove_matrix(&D);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(s21_inverse_matrix_test_2) {
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t D = {0};

  // Создаем матрицы
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  s21_create_matrix(3, 3, &D);

  // Инициализация матрицы A
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  // Ожидаемая обратная матрица
  C.matrix[0][0] = 1;
  C.matrix[0][1] = -1;
  C.matrix[0][2] = 1;

  C.matrix[1][0] = -38;
  C.matrix[1][1] = 41;
  C.matrix[1][2] = -34;

  C.matrix[2][0] = 27;
  C.matrix[2][1] = -29;
  C.matrix[2][2] = 24;
  // Вычисление обратной матрицы
  int error = s21_inverse_matrix(&A, &D);

  // Проверка результата
  ck_assert_int_eq(s21_eq_matrix(&D, &C), SUCCESS);
  ck_assert_int_eq(error, S21_OK);

  // Удаление матриц
  s21_remove_matrix(&A);
  s21_remove_matrix(&C);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_inverse_matrix_test_3) {
  matrix_t A = {0};
  matrix_t D = {0};
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 1;
  A.matrix[1][0] = 1;
  A.matrix[1][1] = 1;
  int error = s21_inverse_matrix(&A, &D);
  ck_assert_int_eq(error, S21_CALC_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_inverse_matrix_test_4) {
  matrix_t A = {0};
  matrix_t D = {0};
  int error = s21_inverse_matrix(&A, &D);
  ck_assert_int_eq(error, S21_ERROR);
  s21_remove_matrix(&A);
  s21_remove_matrix(&D);
}
END_TEST

START_TEST(s21_inverse_matrix_test_5) {
  matrix_t A = {0};
  matrix_t C = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B = {0};
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(s21_inverse_matrix_test_7) {
  int res = 0;
  matrix_t A = {0};
  matrix_t Z = {0};
  matrix_t X = {0};

  s21_create_matrix(3, 3, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 2.0;
  A.matrix[0][2] = 3.0;
  A.matrix[1][0] = 4.0;
  A.matrix[1][1] = 5.0;
  A.matrix[1][2] = 6.0;
  A.matrix[2][0] = 8.0;
  A.matrix[2][1] = 6.0;
  A.matrix[2][2] = 9.0;

  s21_inverse_matrix(&A, &Z);

  s21_create_matrix(3, 3, &X);

  X.matrix[0][0] = -3.0 / 5.0;
  X.matrix[0][1] = 0.0;
  X.matrix[0][2] = 1.0 / 5.0;
  X.matrix[1][0] = -4.0 / 5.0;
  X.matrix[1][1] = 1.0;
  X.matrix[1][2] = -2.0 / 5.0;
  X.matrix[2][0] = 16.0 / 15.0;
  X.matrix[2][1] = -2.0 / 3.0;
  X.matrix[2][2] = 1.0 / 5.0;

  res = s21_eq_matrix(&X, &Z);

  s21_remove_matrix(&A);
  s21_remove_matrix(&X);
  s21_remove_matrix(&Z);

  ck_assert_int_eq(res, SUCCESS);
}
END_TEST

START_TEST(s21_inverse_matrix_test_8) {
  matrix_t A = {0};
  matrix_t C = {0};
  matrix_t D = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  A.matrix[0][0] = 2;
  A.matrix[0][1] = 5;
  A.matrix[0][2] = 7;

  A.matrix[1][0] = 6;
  A.matrix[1][1] = 3;
  A.matrix[1][2] = 4;

  A.matrix[2][0] = 5;
  A.matrix[2][1] = -2;
  A.matrix[2][2] = -3;

  C.matrix[0][0] = 1;
  C.matrix[0][1] = -1;
  C.matrix[0][2] = 1;

  C.matrix[1][0] = -38;
  C.matrix[1][1] = 41;
  C.matrix[1][2] = -34;

  C.matrix[2][0] = 27;
  C.matrix[2][1] = -29;
  C.matrix[2][2] = 24;

  int error = s21_inverse_matrix(&A, &D);

  ck_assert_int_eq(s21_eq_matrix(&D, &C), SUCCESS);
  ck_assert_int_eq(error, S21_OK);
  s21_remove_matrix(&A);
  s21_remove_matrix(&D);
  s21_remove_matrix(&C);
}
END_TEST

Suite *test_invert_matrix() {
  Suite *s = suite_create("\033[36m-=S21_MATRIX_INVERSE=-\033[0m");
  TCase *tc = tcase_create("case_inverse_matrix");
  tcase_add_test(tc, s21_inverse_matrix_test_1);
  tcase_add_test(tc, s21_inverse_matrix_test_2);
  tcase_add_test(tc, s21_inverse_matrix_test_3);
  tcase_add_test(tc, s21_inverse_matrix_test_4);
  tcase_add_test(tc, s21_inverse_matrix_test_5);
  tcase_add_test(tc, s21_inverse_matrix_test_7);
  tcase_add_test(tc, s21_inverse_matrix_test_8);
  suite_add_tcase(s, tc);
  return s;
}