#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define SUCCESS 1
#define FAILURE 0

#define MATRIX_SUCCESS 0
#define MATRIX_ERROR 1
#define MATRIX_CALCULATION_ERROR 2

#include "math.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct matrix_struct {
  double** matrix;
  int rows;
  int columns;
} matrix_t;

// основные функции
//  Создание
int s21_create_matrix(int rows, int columns, matrix_t* result);
// Удаление
void s21_remove_matrix(matrix_t* A);
// Сравнение
int s21_eq_matrix(matrix_t* A, matrix_t* B);
// Сумирование
int s21_sum_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
// Разница
int s21_sub_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
// Умножение на число
int s21_mult_number(matrix_t* A, double number, matrix_t* result);
// Умножение матриц
int s21_mult_matrix(matrix_t* A, matrix_t* B, matrix_t* result);
// Транспонирование матрици
int s21_transpose(matrix_t* A, matrix_t* result);
// Минор матрици
int s21_calc_complements(matrix_t* A, matrix_t* result);
// Детерминант матрици
int s21_determinant(matrix_t* A, double* result);
// Инверсия матрици
int s21_inverse_matrix(matrix_t* A, matrix_t* result);

// вспомагательные функции

int s21_skip(matrix_t* A, int row, int col, double* minor);
int s21_pivot(matrix_t* A, int i, int col);
int s21_valid_matrixes(matrix_t* A, matrix_t* B);
int s21_valid_matrix(matrix_t* A);

#endif