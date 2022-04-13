#include <stdlib.h>
#include <math.h>
#include <float.h>

#include "matrix_func.h"

int det(const Matrix* matrix, double* val) {
    if (matrix == NULL || val == NULL || matrix->cols != matrix->rows) {
        return ERROR;
    }
    *val = 0;
    double **matr_buf = matrix->matrix;
    switch (matrix->cols) {
        case 1:
            *val = matr_buf[0][0];
            break;
        case 2:
            *val = matr_buf[0][0] * matr_buf[1][1] - matr_buf[0][1] * matr_buf[1][0];
            break;
        default:
            for (size_t i = 0; i < matrix->cols; i++) {
                Matrix* matr_minor = create_matrix(matrix->rows - 1, matrix->cols - 1);
                if (matr_minor == NULL) {
                    return ERROR;
                }
                double value;
                if (det(get_minor(matrix, matr_minor, 0, i), &value) != 0) {
                    free_matrix(matr_minor);
                    return ERROR;
                }
                *val += sign_func(i) * matr_buf[0][i] * value;
                free_matrix(matr_minor);
            }
    }
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (matrix == NULL || matrix->cols != matrix->rows) {
        return NULL;
    }
    double determ = 0;
    if (det(matrix, &determ) != 0 || fabs(determ) < DBL_EPSILON) {
        return NULL;
    }
    Matrix* matr_adj = create_matrix(matrix->rows, matrix->cols);
    if (matr_adj == NULL) {
        return NULL;
    }
    if (matrix->cols == 1) {
        matr_adj->matrix[0][0] = 1;
        return matr_adj;
    }
    Matrix* matr_transp = transp(matrix);
    if (matr_transp == NULL) {
        free_matrix(matr_adj);
        return NULL;
    }
    for (size_t i = 0; i < matr_adj->rows; ++i) {
        for (size_t j = 0; j < matr_adj->cols; ++j) {
            Matrix* matr_minor = create_matrix(matr_transp->rows -1,
                                               matr_transp->cols -1);
            if (matr_minor == NULL) {
                free_matrix(matr_transp);
                free_matrix(matr_adj);
                return NULL;
            }
            double value = 0;
            if (det(get_minor(matr_transp, matr_minor, i, j),
                              &value) != 0) {
                free_matrix(matr_minor);
                free_matrix(matr_transp);
                free_matrix(matr_adj);
                return NULL;
            }
            matr_adj->matrix[i][j] = sign_func(i + j) * value;
            free_matrix(matr_minor);
        }
    }
    free_matrix(matr_transp);
    return matr_adj;
}

Matrix* inv(const Matrix* matrix) {
    if (matrix == NULL || matrix->cols != matrix->rows) {
        return NULL;
    }
    double determ = 0;
    if (det(matrix, &determ) != 0 || fabs(determ) < DBL_EPSILON) {
        return NULL;
    }
    Matrix *matr_buf = adj(matrix);
    if (matr_buf == NULL) {
        return NULL;
    }
    double inv_determ = 1 / determ;
    Matrix* matr_inv = mul_scalar(matr_buf, inv_determ);
    if (matr_inv == NULL) {
        free_matrix(matr_buf);
        return NULL;
    }
    free_matrix(matr_buf);
    return matr_inv;
}
