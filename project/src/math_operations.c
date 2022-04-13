#include "matrix_func.h"

Matrix* mul_scalar(const Matrix* matrix, double val) {
    if (matrix == NULL) {
        return NULL;
    }
    Matrix* matr_mul_scalar = create_matrix(matrix->rows, matrix->cols);
    if (matr_mul_scalar == NULL)
        return NULL;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            matr_mul_scalar->matrix[i][j] = matrix->matrix[i][j] * val;
        }
    }
    return matr_mul_scalar;
}

Matrix* transp(const Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    Matrix* matr_transp = create_matrix(matrix->cols, matrix->rows);
    if (matr_transp == NULL)
        return NULL;
    for (size_t i = 0; i < matrix->rows; i++) {
        for (size_t j = 0; j < matrix->cols; j++) {
            matr_transp->matrix[j][i] = matrix->matrix[i][j];
        }
    }
    return matr_transp;
}

Matrix* sum(const Matrix* l, const Matrix* r) {
    Matrix* matr_sum = general_func_sum_sub(l, r, 1);
    return matr_sum;
}

Matrix* sub(const Matrix* l, const Matrix* r) {
    Matrix* matr_sub = general_func_sum_sub(l, r, -1);
    return matr_sub;
}

Matrix* mul(const Matrix* l, const Matrix* r) {
    if (l == NULL || r == NULL || l->cols != r->rows) {
        return NULL;
    }
    Matrix* matr_mul = create_matrix(l->rows, r->cols);
    if (matr_mul == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < l->rows; i++) {
        for (size_t j = 0; j < r->cols; j++) {
            matr_mul->matrix[i][j] = 0;
            for (size_t k = 0; k < l->cols; k++)
            matr_mul->matrix[i][j] += l->matrix[i][k] * r->matrix[k][j];
        }
    }
    return matr_mul;
}
