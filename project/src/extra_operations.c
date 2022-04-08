#include <stdio.h>

#include "matrix.h"
#include "extra_utils.h"

int det(const Matrix* matrix, double* val) {
    if (matrix == NULL || val == NULL || matrix->cols != matrix->rows) {
        return ERROR;
    }
    *val = 0;
    switch (matrix->cols) {
        case 1:
            *val = matrix->matrix[0][0];
            break;
        case 2:
            *val = matrix->matrix[0][0] * matrix->matrix[1][1] - matrix->matrix[0][1] * matrix->matrix[1][0];
            break;
        default:
            for (size_t i = 0; i < matrix->cols; i++) {
                Matrix *matr_minor = create_matrix(matrix->rows - 1, matrix->cols - 1);
                if (matr_minor == NULL) {
                    return ERROR;
                }
                double value;
                if (det(get_minor(matrix, matr_minor, 0, i), &value) != 0) {
                    free_matrix(matr_minor);
                    return ERROR;
                }
                *val += sign_func(i) * matrix->matrix[0][i] * value;
                free_matrix(matr_minor);
            }
            break;
    }
    return 0;
}

Matrix* adj(const Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    return NULL;
}
Matrix* inv(const Matrix* matrix) {
    if (matrix == NULL) {
        return NULL;
    }
    return NULL;
}
