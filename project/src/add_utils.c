#include "matrix_func.h"

Matrix *get_minor(const Matrix *matrix, Matrix *minor, size_t row, size_t col) {
    if (matrix == NULL || minor == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < matrix->rows - 1; i++) {
        for (size_t j = 0; j < matrix->cols - 1; j++) {
            if (i < row) {
                if (j < col) {
                    minor->matrix[i][j] = matrix->matrix[i][j];
                } else {
                    minor->matrix[i][j] = matrix->matrix[i][j + 1];
                }
            }  else {
            if (j < col) {
                    minor->matrix[i][j] = matrix->matrix[i + 1][j];
                } else {
                    minor->matrix[i][j] = matrix->matrix[i + 1][j + 1];
                }
            }
        }
    }
    return minor;
}

int sign_func(size_t number) {
    return number % 2 == 0 ? 1 : -1;
}

Matrix* general_func_sum_sub(const Matrix* l, const Matrix* r, int sign) {
    if (l == NULL || r == NULL || l->rows != r->rows || l->cols != r->cols) {
        return NULL;
    }
    if (sign == 0) {
        return NULL;
    }
    Matrix* matr_general = create_matrix(l->rows, l->cols);
    if (matr_general == NULL) {
        return NULL;
    }

    if (sign < 0) {
        for (size_t i = 0; i < l->rows; i++) {
            for (size_t j = 0; j < l->cols; j++) {
                matr_general->matrix[i][j] = l->matrix[i][j] - r->matrix[i][j];
            }
        }
    }
    if (sign > 0) {
        for (size_t i = 0; i < l->rows; i++) {
            for (size_t j = 0; j < l->cols; j++) {
                matr_general->matrix[i][j] = l->matrix[i][j] + r->matrix[i][j];
            }
        }
    }
    return matr_general;
}
