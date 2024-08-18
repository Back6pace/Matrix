#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code = S21_OK;

  if (result == NULL || rows < 1 || columns < 1) {
    code = S21_ERROR;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));

    if (result->matrix != NULL) {
      for (int i = 0; i < rows; i++) {
        result->matrix[i] = (double *)calloc(columns, sizeof(double));
        if (result->matrix[i] == NULL) {
          for (int j = 0; j < i; j++) {
            free(result->matrix[j]);
          }
          free(result->matrix);
          result->matrix = NULL;
          code = S21_ERROR;
          break;
        }
      }
    } else {
      code = S21_ERROR;
    }

    if (code == S21_ERROR) {
      result->rows = 0;
      result->columns = 0;
    }
  }

  return code;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix != NULL) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    A->matrix = NULL;
    A->rows = 0;
    A->columns = 0;
  } else {
    A->rows = 0;
    A->columns = 0;
  }
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int code = SUCCESS;
  if (A->matrix == NULL || B->matrix == NULL) {
    code = FAILURE;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    code = FAILURE;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
          code = FAILURE;
          break;
        }
      }
    }
  }
  return code;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = S21_OK;
  if (result == NULL || A == NULL || B == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    code = S21_ERROR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    code = S21_CALC_ERROR;
  } else {
    code = s21_create_matrix(A->rows, A->columns, result);
    if (code == S21_OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    }
  }
  return code;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = S21_OK;
  if (result == NULL || A == NULL || B == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    code = S21_ERROR;
  } else if (A->rows != B->rows || A->columns != B->columns) {
    code = S21_CALC_ERROR;
  } else {
    code = s21_create_matrix(A->rows, A->columns, result);
    if (code == S21_OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    }
  }
  return code;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int code = S21_OK;
  if (result == NULL || A == NULL || A->matrix == NULL) {
    code = S21_ERROR;
  } else if (A->rows < 1 || A->columns < 1) {
    code = S21_CALC_ERROR;
  } else {
    code = s21_create_matrix(A->rows, A->columns, result);
    if (code == S21_OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] * number;
        }
      }
    }
  }
  return code;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int code = S21_OK;
  if (result == NULL || A == NULL || B == NULL || A->matrix == NULL ||
      B->matrix == NULL) {
    code = S21_ERROR;
  } else if (A->columns != B->rows) {
    code = S21_CALC_ERROR;
  } else {
    code = s21_create_matrix(A->rows, B->columns, result);
    if (code == S21_OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          for (int k = 0; k < A->columns; k++) {
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
          }
        }
      }
    }
  }
  return code;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int code = S21_OK;
  if (result == NULL || A == NULL || A->matrix == NULL) {
    code = S21_ERROR;
  } else if (A->rows < 1 || A->columns < 1) {
    code = S21_CALC_ERROR;
  } else {
    code = s21_create_matrix(A->columns, A->rows, result);
    if (code == S21_OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    }
  }
  return code;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int code = S21_OK;
  if (result == NULL || A == NULL || A->matrix == NULL) {
    code = S21_ERROR;
  } else if (A->rows < 1 || A->columns < 1) {
    code = S21_CALC_ERROR;
  } else {
    code = s21_create_matrix(A->rows, A->columns, result);
    if (code == S21_OK) {
      code = option_calc_complements(A, result);
      if (code != S21_OK) {
        s21_remove_matrix(result);  // Освобождение ресурсов в случае ошибки
      }
    }
  }
  return code;
}

int option_calc_complements(matrix_t *A, matrix_t *result) {
  int code = S21_OK;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      int rows = A->rows <= 1 ? 2 : A->rows;
      int columns = A->columns <= 1 ? 2 : A->columns;
      int minor_rows = rows - 1;
      int minor_columns = columns - 1;
      matrix_t minor;
      code = s21_create_matrix(minor_rows, minor_columns, &minor);
      if (code != S21_OK) {
        for (int x = 0; x < i; x++) {
          for (int y = 0; y < A->columns; y++) {
            s21_remove_matrix(&minor);
          }
        }
        break;
      }
      int remi = 0;
      int remj = 0;
      for (int k = 0; k < A->rows; k++) {
        if (k == i) continue;
        for (int l = 0; l < A->columns; l++) {
          if (l == j) continue;
          minor.matrix[remi][remj] = A->matrix[k][l];
          remj++;
        }
        remi++;
        remj = 0;
      }
      double minor_determinant;
      code = s21_determinant(&minor, &minor_determinant);
      if (code != S21_OK) {
        break;
      }
      result->matrix[i][j] = pow(-1, i + j) * minor_determinant;
      s21_remove_matrix(&minor);
    }
  }
  return code;
}

int s21_determinant(matrix_t *A, double *result) {
  int code = S21_OK;
  if (A->rows < 1 || A->columns < 1 || A->rows != A->columns) {
    code = S21_ERROR;
  } else if (A->matrix == NULL) {
    code = S21_CALC_ERROR;
  }
  if (A->columns == 1) {
    *result = A->matrix[0][0];
  } else if (A->columns == 2) {
    *result =
        A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
  } else {
    *result = 1;
    for (int i = 0; i < A->rows; i++) {
      int pivotIndex = i;  // Ведущий элемент

      for (int j = i + 1; j < A->rows; j++) {  // Ищем ведущий элементв столбце
        if (fabs(A->matrix[j][i]) > fabs(A->matrix[pivotIndex][i])) {
          pivotIndex = j;
        }
      }

      if (A->matrix[pivotIndex][i] == 0) {  // Если ведущий элемент равен нулю,
                                            // то результат будет равен нулю
        *result = 0;
        break;
      }
      // Если индекс ведущего элемента не совпадает с индексом ведущей
      // строки, то переставляем строки и меняем знак результата
      if (pivotIndex != i) {
        double *temp = A->matrix[i];
        A->matrix[i] = A->matrix[pivotIndex];
        A->matrix[pivotIndex] = temp;
        *result *= -1;
      }
      // Приведение матрицы к верхнетреугольному виду
      for (int j = i + 1; j < A->rows; ++j) {
        double factor = A->matrix[j][i] / A->matrix[i][i];
        for (int k = i; k < A->columns; ++k) {
          A->matrix[j][k] -= factor * A->matrix[i][k];
        }
      }
      *result *= A->matrix[i][i];
    }
  }
  return code;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int code = S21_OK;
  if (A->rows != A->columns) {
    code = S21_CALC_ERROR;
  } else if (A->matrix == NULL || A->rows < 1) {
    code = S21_ERROR;
  } else {
    double det;
    matrix_t mat_for_det;
    s21_create_matrix(A->rows, A->columns, &mat_for_det);
    for (int x = 0; x < A->rows; x++) {
      for (int y = 0; y < A->columns; y++) {
        mat_for_det.matrix[x][y] = A->matrix[x][y];
      }
    }
    code = s21_determinant(&mat_for_det, &det);

    if (code == S21_OK && fabs(det) > EPSILON) {
      matrix_t complements = {0};
      code = s21_calc_complements(A, &complements);
      if (code == S21_OK) {
        matrix_t transposed = {0};
        code = s21_transpose(&complements, &transposed);
        s21_remove_matrix(&complements);

        code = s21_create_matrix(A->rows, A->columns, result);
        if (code == S21_OK) {
          code = s21_mult_number(&transposed, 1.0 / det, result);
        }

        s21_remove_matrix(&transposed);
      }
    } else {
      code = S21_CALC_ERROR;  // Если детерминант равен 0 или функция не удалась
    }
  }
  return code;
}
