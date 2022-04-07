#include "matrix.h"

int get_rows(const Matrix* matrix, size_t* rows) {
    if (matrix == NULL || rows == NULL) {
        return -1;
    }
    *rows = matrix->rows;
        return 0;
}

int get_cols(const Matrix* matrix, size_t* cols) {
    if (matrix == NULL || cols == NULL) {
        return -1;
    }
    *cols = matrix->cols;
        return 0;
}

int get_elem(const Matrix* matrix, size_t row, size_t col, double* val);
int set_elem(Matrix* matrix, size_t row, size_t col, double val);
