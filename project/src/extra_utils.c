#include "extra_utils.h"
#include "matrix.h"

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
