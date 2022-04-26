#include "../include/matrix.h"
#include "../include/exceptions.h"

static int sign(size_t x) {
        return x % 2 == 0 ? 1 : -1;
}

namespace prep {

    // Init operations
    Matrix::Matrix(size_t rows, size_t cols) {
        this->rows = rows;
        this->cols = cols;
        this->matrix = new double *[this->rows];
        for (size_t i = 0; i < this->rows; i++) {
            this->matrix[i] = new double[this->cols];
            for (size_t j = 0; j < this->cols; j++) {
                this->matrix[i][j] = 0;
            }
        }
    }

    Matrix::Matrix(std::istream& is) {
        this->rows = this->cols = 0;
        if (!(is >> this->rows >> this->cols)) {
            throw InvalidMatrixStream();
        } else {
            this->matrix = new double *[this->rows];
            for (size_t i = 0; i < this->rows; i++) {
                this->matrix[i] = new double[this->cols];
                for (size_t j = 0; j < this->cols; j++) {
                    if (!(is >> matrix[i][j])) {
                        for (size_t k = 0; k < this->rows; k++) {
                            delete[] this->matrix[k];
                        }
                        delete[] this->matrix;
                        throw InvalidMatrixStream();
                    }
                }
            }
        }
    }

    Matrix::Matrix(const Matrix& rhs) {
        this->rows = rhs.getRows();
        this->cols = rhs.getCols();
        this->matrix = new double *[this->rows];
        for (size_t i = 0; i < this->rows; i++) {
            this->matrix[i] = new double[this->cols];
            for (size_t j = 0; j < this->cols; j++) {
                this->matrix[i][j] = rhs.matrix[i][j];
            }
        }
    }

    Matrix& Matrix::operator=(const Matrix& rhs) {
        if (&rhs != this) {
            for (size_t i = 0; i < this->rows; i++) {
                delete[] this->matrix[i];
            }
            delete[] this->matrix;
            this->rows = rhs.getRows();
            this->cols = rhs.getCols();
            this->matrix = new double *[this->rows];
            for (size_t i = 0; i < this->rows; i++) {
                this->matrix[i] = new double[this->cols];
                for (size_t j = 0; j < this->cols; j++) {
                    this->matrix[i][j] = rhs.matrix[i][j];
                }
            }
        }
        return *this;
    }

    Matrix::~Matrix() {
        for (size_t i = 0; i < this->rows; i++) {
            delete[] this->matrix[i];
        }
        delete[] this->matrix;
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
        double buf;
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < rhs.cols; j++) {
                buf = 0;
                for (size_t k = 0; k < this->cols; k++) {
                    buf += this->matrix[i][k] * rhs.matrix[k][j];
                }
                new_matrix.matrix[i][j] = buf;
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
        for (size_t i = 0; i < matrix.rows; i++) {
            for (size_t j = 0; j < matrix.cols; j++) {
                os << std::setprecision(std::numeric_limits<double>::max_digits10)
                 << matrix.matrix[i][j] << ' ';
            }
            os << '\n';
        }
        return os;
    }

      // additional operations
    Matrix Matrix::minor_matrix(size_t i, size_t j) const {
        Matrix minor(this->rows - 1, this->cols - 1);
        for (size_t l = 0; l < this->rows - 1; l++) {
            for (size_t k = 0; k < this->cols - 1; k++) {
                const size_t row_offset = l >= i;
                const size_t col_offset = k >= j;
                minor.matrix[l][k] = this->matrix[l + row_offset][k + col_offset];
            }
        }
        return minor;
    }

    Matrix Matrix::transp() const {
        Matrix tra_mtx(this->cols, this->rows);
        for (size_t i = 0; i < this->rows; i++) {
            for (size_t j = 0; j < this->cols; j++) {
                tra_mtx.matrix[j][i] = this->matrix[i][j];
            }
        }
        return tra_mtx;
    }

    double Matrix::det() const {
        if (this->cols != this->rows) {
            throw DimensionMismatch(*this);
        } else {
            double determinant = 0;
            switch (this->cols) {
                case 1:
                    determinant = this->matrix[0][0];
                    break;
                case 2:
                    determinant = this->matrix[0][0] * this->matrix[1][1] - this->matrix[0][1] *
                                  this->matrix[1][0];
                    break;
                case 3:
                    for (size_t i = 0; i < 3; i++) {
                        determinant += this->matrix[0][i] * this->matrix[1][(i + 1) % 3] *
                                       this->matrix[2][(i + 2) % 3];
                        determinant -= this->matrix[0][i] * this->matrix[1][(i + 2) % 3] *
                                       this->matrix[2][(i + 1) % 3];
                    }
                    break;
                default:
                    for (size_t k = 0; k < this->cols; k++) {
                        double v = this->minor_matrix(0, k).det();
                        determinant += sign(k) * this->matrix[0][k] * v;
                    }
            }
            return determinant;
        }
    }

    Matrix Matrix::adj() const {
        if (this->cols != this->rows) {
            throw DimensionMismatch(*this);
        } else {
            double determinant = this->det();
            if (determinant == 0) {
                throw SingularMatrix();
            } else {
                Matrix buf_mtx(this->rows, this->cols);
                if (this->rows == 1 && this->cols == 1) {
                    buf_mtx.matrix[0][0] = 1;
                    return buf_mtx;
                } else {
                    for (size_t i = 0; i < buf_mtx.getRows(); i++) {
                        for (size_t j = 0; j < buf_mtx.getCols(); j++) {
                            double v = this->transp().minor_matrix(i, j).det();
                            buf_mtx.matrix[i][j] = sign(i + j) * v;
                        }
                    }
                    return buf_mtx;
                }
            }
        }
    }

    Matrix Matrix::inv() const {
        if (this->cols != this->rows) {
            throw DimensionMismatch(*this);
        } else {
            double determinant = this->det();
            if (determinant == 0) {
                throw SingularMatrix();
            } else {
                double inv_det = 1 / determinant;
                return this->adj() * inv_det;
            }
        }
    }
}  // namespace prep
