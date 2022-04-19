#include <stdlib.h>

#include "matrix_func.h"

#define ROWS 2
#define COLS 2

int main(void) {
    Matrix* A = create_matrix(ROWS, COLS);
    Matrix* B = create_matrix(ROWS, COLS);
    double num_A;
    double num_B;

    for (int i = 1; i <= ROWS; i++) {
        for (int j = 1; i <= COLS; i++) {
            num_A = (i+j)/2;
            set_elem(A, i, j, num_A);
            num_B = i-2*j;
            set_elem(B, i, j, num_B);
        }
    }

    Matrix* sum_m = sum(A, B);
    mul_scalar(sum_m, 2);
    return 0;
}
