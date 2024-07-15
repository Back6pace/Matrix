#include "my_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int code = S21_OK;
  if (rows < 1 && columns < 1) {
    result->rows = 0;
    result->columns = 0;
    result->matrix = NULL;
    code = S21_ERROR;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = (double **)calloc(rows, sizeof(double *));
    if (result->matrix == NULL) {
      code = S21_ERROR;
    }
  }

  return code;
}

void s21_remove_matrix(matrix_t *A);
