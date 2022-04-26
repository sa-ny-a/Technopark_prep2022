#include "matrix.h"
#include "exceptions.h"

namespace prep {

    // Init/release operations
    Matrix::Matrix(size_t rows, size_t cols) {
        if (rows < 1 || cols < 1) {
            throw InvalidMatrixStream();
        } else {
            this->rows = rows;
            this->cols = cols;
            this->matrix = new double *[this->rows];
            for (size_t i = 0; i < this->rows; i++) {
                this->matrix[i] = new double[this->cols];
            }
        }
    }

    Matrix::Matrix(std::istream& is) {
        size_t row, col;
        if (!(is >> row >> col)) {
            throw InvalidMatrixStream();
        } else {
            if (row < 1 || col < 1) {
                throw InvalidMatrixStream();
            } else {
                this->rows = row;
                this->cols = col;
                this->matrix = new double *[this->rows];
                for (size_t i = 0; i < this->rows; i++) {
                    this->matrix[i] = new double[this->cols];
                }
                for (size_t i = 0; i < this->rows; i++) {
                    for (size_t j = 0; j < this->cols; j++) {
                        if (!(is >> matrix[i][j])) {
                            throw InvalidMatrixStream();
                        }
                    }
                }
            }
        }
    }

    Matrix::Matrix(const Matrix& rhs) {
        this->rows = rhs.getRows();
        this->cols = rhs.getCols();
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                this->matrix[i][j] = rhs.matrix[i][j];
            }
        }
    }

    Matrix& Matrix::operator=(const Matrix& rhs) {
        this->rows = rhs.getRows();
        this->cols = rhs.getCols();
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                this->matrix[i][j] = rhs.matrix[i][j];
            }
        }
        return *this;
    }
   
    Matrix::~Matrix() {
        if ((this->cols + this->rows) != 0) {
            for (size_t i = 0; i < this->rows; i++) {
                delete[] this->matrix[i];
            }
        delete[] this->matrix;
        }
    }

    // Basic operations
    size_t Matrix::getRows() const {
       return this->rows;
    }

    size_t Matrix::getCols() const {
       return this->cols;
    }

    double Matrix::operator()(size_t i, size_t j) const {
        if (i >= this->rows || j >= this->cols) {
            throw OutOfRange(i, j, *this);
        }
        return this->matrix[i][j];
    }

    double& Matrix::operator()(size_t i, size_t j) {
        if (i >= this->rows || j >= this->cols) {
            throw OutOfRange(i, j, *this);
        }
        return this->matrix[i][j];
    }

    // Math operations
    bool Matrix::operator==(const Matrix& rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            return false;
        }
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                if (std::abs(this->matrix[i][j] - rhs.matrix[i][j]) > 1e-7) {
                    return false;
                }
            }
        }
        return true;
    }

    bool Matrix::operator!=(const Matrix& rhs) const {
        return !(*this == rhs);
    }

    Matrix Matrix::operator+(const Matrix& rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            throw DimensionMismatch(*this, rhs);
        }
        Matrix new_matrix(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                new_matrix.matrix[i][j] = this->matrix[i][j] + rhs.matrix[i][j];
            }
        }
        return new_matrix;
    }

    Matrix Matrix::operator-(const Matrix& rhs) const {
        if (this->rows != rhs.rows || this->cols != rhs.cols) {
            throw DimensionMismatch(*this, rhs);
        }
        Matrix new_matrix(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                new_matrix.matrix[i][j] = this->matrix[i][j] - rhs.matrix[i][j];
            }
        }
        return new_matrix;
    }

    Matrix Matrix::operator*(const Matrix& rhs) const {
        if (this->cols != rhs.rows) {
            throw DimensionMismatch(*this, rhs);
        }
        Matrix new_matrix(this->rows, rhs.cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < rhs.cols; j++) {
                for (size_t k = 0; k < this->cols; k++) {
                    new_matrix.matrix[i][j] += this->matrix[i][k] * rhs.matrix[k][j];
                }
            }
        }
        return new_matrix;
    }

    Matrix Matrix::operator*(double val) const {
        Matrix new_matrix(this->rows, this->cols);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                new_matrix.matrix[i][j] = this->matrix[i][j] * val;
            }
        }
        return new_matrix;
    }

    Matrix operator*(double val, const Matrix& matrix) {
        return matrix * val;
    }

    std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
        os << matrix.rows << ' ' << matrix.cols << '\n';
        for (size_t i = 0; i < matrix.rows; ++i) {
            for (size_t j = 0; j < matrix.cols; ++j) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10)
                 << matrix.matrix[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }
//
      // additional operations
//    Matrix Matrix::transp() const;
//    double Matrix::det() const;
//    Matrix Matrix::adj() const;
//    Matrix Matrix::inv() const;
//
//    Matrix operator*(double val, const Matrix& matrix);
//    std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
};  // namespace prep
