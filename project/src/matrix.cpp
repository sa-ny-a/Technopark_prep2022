#include "matrix.h"
#include "exceptions.h"

namespace prep {
    explicit Matrix::Matrix(size_t rows, size_t cols) {
        if (rows < 1 || cols < 1) {
            throw InvalidMatrixStream();
        } else {
            this->rows = rows;
            this->cols = cols;
            this->matrix = new double *[this->rows];
            for (size_t i = 0; i < this->rows; i++) {
                this->matrix[i] = new double [this->cols];
            }
        }
    }

    explicit Matrix::Matrix(std::istream& is) {
         if (!(is >> this->rows >> this->cols)) {
            throw InvalidMatrixStream();
        } else {
            Matrix(this->rows, this->cols);
            for (size_t i = 0; i < this->rows; i++) {
                for (size_t j = 0; j < cthis->cols; j++) {
                    if (!(is >> matrix[i][j])) {
                        throw InvalidMatrixStream();
                    }
                }
            }
        }
    }

//    size_t Matrix::getRows() const;
//    size_t Matrix::getCols() const;
//
//    double Matrix::operator()(size_t i, size_t j) const;
//    double& Matrix::operator()(size_t i, size_t j);
//
//    bool Matrix::operator==(const Matrix& rhs) const;
//    bool Matrix::operator!=(const Matrix& rhs) const;
//
//    Matrix Matrix::operator+(const Matrix& rhs) const;
//    Matrix Matrix::operator-(const Matrix& rhs) const;
//    Matrix Matrix::operator*(const Matrix& rhs) const;
//
//    Matrix Matrix::operator*(double val) const;
//
//    friend Matrix Matrix::operator*(double val, const Matrix& matrix);
//    friend std::ostream& Matrix::operator<<(std::ostream& os, const Matrix& matrix);
//
//    Matrix Matrix::transp() const;
//    double Matrix::det() const;
//    Matrix Matrix::adj() const;
//    Matrix Matrix::inv() const;
//
//    Matrix operator*(double val, const Matrix& matrix);
//    std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
}
