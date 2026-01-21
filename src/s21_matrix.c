#include "s21_matrix.h"

// ОСНОВНЫЕ ФУНКЦИИ

int s21_create_matrix(int rows, int columns, matrix_t* result) {
  int help = MATRIX_SUCCESS;

  if (rows <= 0 || columns <= 0) {
    help = MATRIX_ERROR;
  }
  if (result == NULL) return MATRIX_ERROR;

  if (help == MATRIX_SUCCESS) {
    result->matrix = (double**)calloc(rows, sizeof(double*));
    if (result->matrix) {
      result->rows = rows;
      result->columns = columns;

      for (int i = 0; i < rows; i++) {
        if (!(result->matrix[i] = (double*)calloc(columns, sizeof(double)))) {
          for (int j = 0; j < i; j++) free(result->matrix[j]);
          free(result->matrix);
          result->matrix = NULL;
          help = MATRIX_ERROR;
        }
      }
    } else {
      help = MATRIX_ERROR;
    }
  }

  return help;
}

void s21_remove_matrix(matrix_t* A) {
  if (!A) return;

  for (int i = 0; i < A->rows; i++) free(A->matrix[i]);
  free(A->matrix);

  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t* A, matrix_t* B) {
  int code = s21_valid_matrixes(A, B);
  if (code == FAILURE) return FAILURE;

  if (A->columns != B->columns || A->rows != B->rows) return FAILURE;

  int help = SUCCESS;
  for (int i = 0; help == SUCCESS && i < A->rows; i++) {
    for (int j = 0; help == SUCCESS && j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
        help = FAILURE;
      }
    }
  }
  return help;
}

int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int help = s21_valid_matrixes(A, B);
  if (result == NULL) return MATRIX_ERROR;
  if (help == FAILURE) {
    return MATRIX_ERROR;
  }
  if (A->columns != B->columns || A->rows != B->rows) {
    return MATRIX_CALCULATION_ERROR;
  }

  if ((help = s21_create_matrix(A->rows, A->columns, result)) != 0) {
    return help;
  }

  if (help == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return help;
}

int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  int help = s21_valid_matrixes(A, B);
  if (result == NULL) return MATRIX_ERROR;
  if (help == FAILURE) {
    return MATRIX_ERROR;
  }
  if (A->columns != B->columns || A->rows != B->rows) {
    return MATRIX_CALCULATION_ERROR;
  }

  if ((help = s21_create_matrix(A->rows, A->columns, result)) != 0) {
    return help;
  }

  if (help == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return help;
}

int s21_mult_number(matrix_t* A, double number, matrix_t* result) {
  int help = s21_valid_matrix(A);
  if (result == NULL) return MATRIX_ERROR;
  if (help == FAILURE) {
    return MATRIX_ERROR;
  }

  if (result == NULL) {
    return MATRIX_CALCULATION_ERROR;
  }

  if ((help = s21_create_matrix(A->rows, A->columns, result)) != 0) {
    return help;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return help;
}

int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result) {
  if (result == NULL) return MATRIX_ERROR;
  int help = s21_valid_matrixes(A, B);

  if (help == FAILURE || result == NULL) {
    return MATRIX_ERROR;
  }

  if ((help = s21_create_matrix(A->rows, B->columns, result)) != 0) {
    return help;
  }

  if (A->columns != B->rows) return MATRIX_CALCULATION_ERROR;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0.0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return help;
}

int s21_transpose(matrix_t* A, matrix_t* result) {
  if (result == NULL) return MATRIX_ERROR;
  int help = s21_valid_matrix(A);
  if (!s21_valid_matrix(A)) {
    return MATRIX_ERROR;
  }
  if ((help = s21_create_matrix(A->columns, A->rows, result)) != 0) {
    return help;
  }
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return help;
}

int s21_calc_complements(matrix_t* A, matrix_t* result) {
  if (!A || !result || A->rows != A->columns) return MATRIX_CALCULATION_ERROR;
  if (A->rows == 1) {
    s21_create_matrix(1, 1, result);
    result->matrix[0][0] = 1;
    return MATRIX_SUCCESS;
  }

  if (s21_create_matrix(A->rows, A->columns, result) != MATRIX_SUCCESS)
    return MATRIX_ERROR;

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      int sign = ((i + j) % 2 == 0) ? 1 : -1;
      double minor = 0.0;
      int code = 0;
      if ((code = s21_skip(A, i, j, &minor)) != MATRIX_SUCCESS) {
        return code;
      }
      result->matrix[i][j] = sign * minor;
    }
  }
  return MATRIX_SUCCESS;
}

int s21_determinant(matrix_t* A, double* result) {
  if (!A || !result || A->rows != A->columns) return MATRIX_CALCULATION_ERROR;

  int sign = 1;
  *result = 1.0;
  matrix_t tmp;
  if (s21_create_matrix(A->rows, A->columns, &tmp) != MATRIX_SUCCESS)
    return MATRIX_ERROR;

  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++) tmp.matrix[i][j] = A->matrix[i][j];

  if (tmp.rows == 1) {
    *result = tmp.matrix[0][0];
    s21_remove_matrix(&tmp);
    return MATRIX_SUCCESS;
  } else if (tmp.rows == 2) {
    *result = (tmp.matrix[0][0] * tmp.matrix[1][1]) -
              (tmp.matrix[0][1] * tmp.matrix[1][0]);
    s21_remove_matrix(&tmp);
    return MATRIX_SUCCESS;
  } else if (tmp.rows > 2) {
    for (int col = 0; col < tmp.columns; col++) {
      int res = s21_pivot(&tmp, col, col);
      if (res == 1) {
        sign = -sign;
      } else if (res == -1) {
        *result = 0;
        s21_remove_matrix(&tmp);
        return MATRIX_SUCCESS;
      }
      if (fabs(tmp.matrix[col][col]) < 1e-7) {
        *result = 0;
        s21_remove_matrix(&tmp);
        return MATRIX_SUCCESS;
      }
      for (int i = col + 1; i < tmp.rows; i++) {
        double x = tmp.matrix[i][col] / tmp.matrix[col][col];
        tmp.matrix[i][col] = 0.0;
        for (int j = col; j < tmp.columns; j++) {
          tmp.matrix[i][j] -= tmp.matrix[col][j] * x;
        }
      }
    }
  }
  for (int i = 0; i < tmp.rows; i++) {
    *result *= tmp.matrix[i][i];
  }
  *result *= sign;
  s21_remove_matrix(&tmp);
  return MATRIX_SUCCESS;
}

int s21_inverse_matrix(matrix_t* A, matrix_t* result) {
  if (result == NULL) return MATRIX_ERROR;
  int help = s21_valid_matrix(A);
  if (!s21_valid_matrix(A)) {
    return MATRIX_ERROR;
  }
  if (A->columns != A->rows) return MATRIX_CALCULATION_ERROR;

  double det = 0;
  int status = s21_determinant(A, &det);
  if (fabs(det) < 1e-6 || status != MATRIX_SUCCESS)
    return MATRIX_CALCULATION_ERROR;

  matrix_t B = {0}, B_transpose = {0};

  s21_calc_complements(A, &B);
  s21_transpose(&B, &B_transpose);
  if ((help = s21_create_matrix(A->columns, A->rows, result)) != 0) {
    return help;
  }

  for (int i = 0; i < A->rows; i += 1) {
    for (int j = 0; j < A->rows; j += 1) {
      result->matrix[i][j] = B_transpose.matrix[i][j] / det;
    }
  }

  s21_remove_matrix(&B_transpose);
  s21_remove_matrix(&B);

  return MATRIX_SUCCESS;
}

// ВСПОМАГАТЕЛЬНЫЕ ФУНКЦИИ

int s21_valid_matrix(matrix_t* A) {
  int help = SUCCESS;
  if (A == NULL)
    help = FAILURE;
  else if (A->rows <= 0 || A->columns <= 0) {
    help = FAILURE;
  }
  return help;
}

int s21_valid_matrixes(matrix_t* A, matrix_t* B) {
  int help = SUCCESS;
  if (A == NULL || B == NULL)
    help = FAILURE;
  else if (A->rows <= 0 || A->columns <= 0 || B->rows <= 0 || B->columns <= 0) {
    help = FAILURE;
  }
  return help;
}

int s21_pivot(matrix_t* A, int row, int col) {
  if (A->matrix[row][col] != 0) return 0;

  for (int p = row + 1; p < A->rows; p++) {
    if (A->matrix[p][col] != 0) {
      for (int i = 0; i < A->columns; i++) {
        double tmp = A->matrix[row][i];
        A->matrix[row][i] = A->matrix[p][i];
        A->matrix[p][i] = tmp;
      }
      return 1;
    }
  }
  return -1;
}

int s21_skip(matrix_t* A, int row, int col, double* minor) {
  matrix_t tmp;
  if (s21_create_matrix(A->rows - 1, A->columns - 1, &tmp) != MATRIX_SUCCESS)
    return MATRIX_ERROR;
  int ti = 0;
  for (int i = 0; i < A->rows; i++) {
    if (i == row) continue;
    int tj = 0;
    for (int j = 0; j < A->columns; j++) {
      if (j == col) continue;
      tmp.matrix[ti][tj] = A->matrix[i][j];
      tj++;
    }
    ti++;
  }
  int code = s21_determinant(&tmp, minor);
  s21_remove_matrix(&tmp);
  return code;
}