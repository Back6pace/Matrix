#ifndef MY_MATRIX_H
#define MY_MATRIX_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Matrix structure
typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Коды ошибок
// @param 0  OK
// @param 1  Ошибка, некорректная матрица
//  @param 2  Ошибка вычисления (несовпадающие размеры матриц; матрица, для
//  которой нельзя провести вычисления и т.д.)
#define S21_OK 0
#define S21_ERROR 1
#define S21_CALC_ERROR 2

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);

#define SUCCESS 1
#define FAILURE 0
// Сравнение матриц
//
// @param А  Матрица 1
// @param B  Матрица 2
//
// @brief Сравнивает 2 матрицы
//  Две матрицы A, B совпадают |A = B|, если совпадают их размеры и
//  соответствующие элементы равны, то есть при всех i, j A(i,j) = B(i,j).
//
// @return 1, если два значения равны, 0 в противном случае
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// @brief Суммой двух матриц A = m × n и B = m × n одинаковых размеров
// называется матрица
//  C = m × n = A + B тех же размеров, элементы которой определяются равенствами
//  C(i,j) = A(i,j) + B(i,j).
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
// @brief Разностью двух матриц A = m × n и B = m × n одинаковых размеров
// называется матрица
//  C = m × n = A - B тех же размеров, элементы которой определяются равенствами
//  C(i,j) = A(i,j) - B(i,j).
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// @brief Произведением матрицы A = m × n на число λ называется матрица B = m ×
// n = λ × A, элементы которой определяются равенствами B = λ × A(i,j).
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

// @brief Произведением матрицы A = m × k на матрицу B = k × n называется
// матрица C = m × n = A × B размера m × n, элементы которой определяются
// равенством C(i,j) = A(i,1) × B(1,j) + A(i,2) × B(2,j) + … + A(i,k) × B(k,j).
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// @brief Транспонирование матрицы А заключается в замене строк этой матрицы ее
// столбцами с сохранением их номеров.
int s21_transpose(matrix_t *A, matrix_t *result);

// @brief Минором M(i,j) называется определитель (n-1)-го порядка, полученный
// вычёркиванием из матрицы A i-й строки и j-го столбца.
int s21_calc_complements(matrix_t *A, matrix_t *result);

/** Определитель (детерминант) - это число, которое ставят в соответствие
 *каждой квадратной матрице и вычисляют из элементов по специальным формулам. \
 *Tip: определитель может быть вычислен только для квадратной матрицы.
 *
 *
 * Определитель матрицы равен сумме произведений элементов строки
 * (столбца) на соответствующие алгебраические дополнения.
 * */
int s21_determinant(matrix_t *A, double *result);

/**
 * Матрицу A в степени -1 называют обратной к квадратной матрице А, если
 * произведение этих матриц равняется единичной матрице.
 *
 *
 * Обратной матрицы не существует, если определитель равен 0.
 *
 * Обратная матрица находится по формуле $`A^{-1}=\frac{1} {|A|} × A_*^T`$
 * */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
#endif