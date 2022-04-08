#ifndef PROJECT_INCLUDE_EXTRA_UTILS_H_
#define PROJECT_INCLUDE_EXTRA_UTILS_H_

#include "matrix.h"

Matrix *get_minor(const Matrix *matrix, Matrix *minor, size_t row, size_t col);
int sign_func(size_t number);

#endif  // PROJECT_INCLUDE_EXTRA_UTILS_H_
