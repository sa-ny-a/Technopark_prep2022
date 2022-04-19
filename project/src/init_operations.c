#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

#include "matrix_func.h"

#define DIM_MATR_PARAM 2
#define ELEM_SIZE      1

Matrix* create_matrix_from_file(const char* path_file) {
    if (path_file == NULL) {
        return NULL;
    }
    FILE* ptr_matrix = fopen(path_file, "r");
    if (ptr_matrix == NULL) {
        return NULL;
    }
    size_t rows;
    size_t cols;
    if (fscanf(ptr_matrix, "%zu %zu", &rows, &cols) == DIM_MATR_PARAM) {
        Matrix* matrix = create_matrix(rows, cols);
        if (matrix == NULL) {
            fclose(ptr_matrix);
            return NULL;
        }
        for (size_t i = 0; i < rows; i++) {
            for (size_t j = 0; j < cols; j++) {
                if (fscanf(ptr_matrix, "%lf", &matrix->matrix[i][j]) != ELEM_SIZE) {
                    fclose(ptr_matrix);
                    free_matrix(matrix);
                    return NULL;
                }
            }
        }
        fclose(ptr_matrix);
        return matrix;
    }
    fclose(ptr_matrix);
    return NULL;
}

Matrix* create_matrix(size_t rows, size_t cols) {
    if (rows < 1 || cols < 1) {
        return NULL;
    }
    Matrix* matrix = malloc(sizeof(Matrix));
    if (matrix == NULL) {
        return NULL;
    }
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->matrix = calloc(rows, sizeof(double *));
    if (matrix->matrix == NULL) {
        free(matrix);
        return NULL;
    }
    for (size_t i = 0; i < rows; i++) {
        matrix->matrix[i] = calloc(cols, sizeof(double));
        if (matrix->matrix[i] == NULL) {
            free_matrix(matrix);
            return NULL;
        }
    }
    return matrix;
}

void free_matrix(Matrix* matrix) {
    if (matrix == NULL) {
        return;
    }
    for (size_t i = 0; i < matrix->rows; ++i) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}
