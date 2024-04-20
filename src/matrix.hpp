#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <exception>
#include <string>
#include <cmath>
#include "vector.hpp"


class MatrixException : public std::exception {
private:
    std::string message;
public:
    MatrixException(std::string msg) : message(msg) {};
    const char* what() const throw() {
        return message.c_str();
    }
};


template <typename T>

class Matrix {

private:
    T** data;

public:
    int cols;
    int rows;

    Matrix(int c, int r) : cols(c), rows(r) {
        if (c < 1 || r < 1) {
            throw MatrixException("Invalid Matrix size (" + std::to_string(c) + ", " + std::to_string(r) + ")");
        };

        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    };

    Matrix(int c, int r, T default_value) : cols(c), rows(r) {
        if (c < 1 || r < 1) {
            throw MatrixException("Invalid Matrix size (" + std::to_string(c) + ", " + std::to_string(r) + ")");
        };

        // not using fill to avoid doing same loop twice
        data = new T*[rows];
        for (int y = 0; y < rows; y++) {
            data[y] = new T[cols];
            for (int x = 0; x < cols; x++) {
                data[y][x] = default_value;
            }
        }
    };

    Matrix(int c, int r, T generator(int, int)) : cols(c), rows(r) {
        if (c < 1 || r < 1) {
            throw MatrixException("Invalid Matrix size (" + std::to_string(c) + ", " + std::to_string(r) + ")");
        };

        // not using fill to avoid doing same loop twice
        data = new T*[rows];
        for (int y = 0; y < rows; y++) {
            data[y] = new T[cols];
            for (int x = 0; x < cols; x++) {
                data[y][x] = generator(x, y);
            }
        }
    };

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    };

    void fill(T val) {
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                data[y][x] = val;
            }
        }
    };

    T& operator[](int linear_pos) {
        int x = linear_pos % cols;
        int y = (int)linear_pos / cols;
        if (x < 0 || y < 0 || x >= cols || y >= rows) {
            // out of bounds
            throw MatrixException("Error while trying to get element of matrix.\ntrying to get " + std::to_string(linear_pos) + " => [" + std::to_string(x) + ", " + std::to_string(y) + "] but dimentions are (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        }
        return data[y][x];
    };

    int linear_index(int x, int y) {
        if (x < 0 || y < 0 || x >= cols || y >= rows) {
            // out of bounds
            throw MatrixException("Error while trying to flatten indexes of matrix.\ntrying to get [" + std::to_string(x) + ", " + std::to_string(y) + "] but dimentions are (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        }
        return y * cols + x;
    };

    Matrix<T>* operator+(Matrix<T> & other) {
        if (rows != other.rows || cols != other.cols) {
            // dims not matching !!!
            throw MatrixException("Dimentions (" + std::to_string(cols) + ", " + std::to_string(rows) + ") and (" + std::to_string(other.cols) + ", " + std::to_string(other.rows) + ") not matching for matrix addition");
        }
        Matrix<T>* mat = new Matrix<T>(cols, rows);
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                mat->set_at(x, y, get_at(x, y) + other.get_at(x, y));
            }
        }
        return mat;
    };

    Matrix<T>* operator*(Matrix<T> & other) {
        if (rows != other.rows || cols != other.cols) {
            // dims not matching !!!
            throw MatrixException("Dimentions (" + std::to_string(cols) + ", " + std::to_string(rows) + ") and (" + std::to_string(other.cols) + ", " + std::to_string(other.rows) + ") not matching for matrix multiplication (elem by elem)\nUse .matmul(Matrix) to perform real matrix multipication");
        }
        Matrix<T>* mat = new Matrix<T>(cols, rows);
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                mat->set_at(x, y, get_at(x, y) * other.get_at(x, y));
            }
        }
        return mat;
    };

    template <typename nT> // new type
    Matrix<nT>* mat_static_cast() {
        Matrix<nT>* mat = new Matrix<nT>(cols, rows);
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                mat->set_at(x, y, static_cast<nT>(get_at(x, y)));
            }
        }
        return mat;
    };

    Vector<T>* get_row(int row) {
        if (row < 0 || row >= rows) {
            // out of bounds
            throw MatrixException("Error getting row (" + std::to_string(row) + ") : out of bound (" + std::to_string(rows) + " rows availables)");
        }
        Vector<T>* vec = new Vector<T>(cols);
        for (int x = 0; x < cols; x++) {
            (*vec)[x] = data[row][x];
        }
        return vec;
    };

    Vector<T>* get_col(int col) {
        if (col < 0 || col >= cols) {
            // out of bounds
            throw MatrixException("Error getting column (" + std::to_string(col) + ") : out of bound (" + std::to_string(cols) + " columns availables)");
        }
        Vector<T>* vec = new Vector<T>(rows);
        for (int x = 0; x < rows; x++) {
            (*vec)[x] = data[x][col];
        }
        return vec;
    };

    Matrix<T>* matmul(Matrix<T>& other) {
        if (cols != other.rows) {
            // dims not matching !!!
            throw MatrixException("Dimentions (" + std::to_string(cols) + ", " + std::to_string(rows) + ") and (" + std::to_string(other.cols) + ", " + std::to_string(other.rows) + ") not matching for matrix multiplication.");
        }
        Matrix<T>* mat = new Matrix<T>(other.cols, rows);

        Vector<T>** rows_vec = new Vector<T>*[rows];
        for (int i = 0; i < rows; i++) {
            rows_vec[i] = get_row(i);
        }
        Vector<T>** cols_vec = new Vector<T>*[other.cols];
        for (int i = 0; i < other.cols; i++) {
            cols_vec[i] = other.get_col(i);
        }

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < other.cols; x++) {
                mat->set_at(x, y, (rows_vec[y])->dot(*(cols_vec[y])));
            }
        }

        for (int i = 0; i < rows; i++) {
            delete rows_vec[i];
        }
        delete[] rows_vec;
        for (int i = 0; i < other.cols; i++) {
            delete cols_vec[i];
        }
        delete[] cols_vec;

        return mat;
    };

    Matrix<T>* transpose() {
        Matrix<T>* mat = new Matrix<T>(rows, cols);

        for (int x = 0; x < cols; x++) {
            for (int y = 0; y < rows; y++) {
                mat->set_at(x, y, get_at(y, x));
            }
        }

        return mat;
    };

    void set_at(int x, int y, T value) {
        (*this)[linear_index(x, y)] = value;
    };

    T get_at(int x, int y) {
        return (*this)[linear_index(x, y)];
    };

    Matrix<T>* slice(int from_x, int from_y, int to_x, int to_y) {
        // to is not included

        if (from_x >= to_x || from_y >= to_y) {
            // wrong slice
            throw MatrixException("Coords from (" + std::to_string(from_x) + ", " + std::to_string(from_y) + ") cant't be greater than to (" + std::to_string(to_x) + ", " + std::to_string(to_y) + ") when slicing.");
        }

        if (from_x < 0 || from_x >= cols || from_y < 0 || from_y >= rows) {
            // out of bound
            throw MatrixException("Error slicing from (" + std::to_string(from_x) + ", " + std::to_string(from_y) + ") : out of bounds (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        }

        if (to_x < 0 || to_x > cols || to_y < 0 || to_y > rows) {
            // out of bound
            throw MatrixException("Error slicing from (" + std::to_string(to_x) + ", " + std::to_string(to_y) + ") : out of bounds (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        }

        int dx = to_x - from_x;
        int dy = to_y - from_y;

        Matrix<T>* mat = new Matrix<T>(dx, dy);

        for (int x = 0; x < dx; x++) {
            for (int y = 0; y < dy; y++) {
                mat->set_at(x, y, get_at(x + from_x, y + from_y));
            }
        }

        return mat;
    };

    void put_matrix(int dx, int dy, Matrix<T>& mat) {
        if (dx < 0 || dy < 0 || dx + mat.cols > cols || dy + mat.rows > rows) {
            throw MatrixException("Can't put matrix size (" + std::to_string(mat.cols) + ", " + std::to_string(mat.rows) + ") at pos [" + std::to_string(dx) + ", " + std::to_string(dy) + "] in matrix size (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        }

        for (int x = 0; x < mat.cols; x++) {
            for (int y = 0; y < mat.rows; y++) {
                set_at(x + dx, y + dy, mat.get_at(x, y));
            }
        }
    };

    T cofactor(int x, int y) {
        if (x < 0 || y < 0 || x >= cols || y >= rows) {
            // out of bounds
            throw MatrixException("Error while getting cofactor at [" + std::to_string(x) + ", " + std::to_string(y) + "] but dimentions are (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        }

        Matrix<T>* mat = new Matrix<T>(cols - 1, rows - 1);

        // pre-compute conditions that will be reused
        bool do_top = y > 0;
        bool do_left = x > 0;
        bool do_bottom = y < cols - 1;
        bool do_right = x < rows - 1;

        // top left
        if (do_top && do_left) {
            Matrix<T>* sub_mat = slice(0, 0, x, y);
            mat->put_matrix(0, 0, *sub_mat);
            delete sub_mat;
        }

        // top right
        if (do_top && do_right) {
            Matrix<T>* sub_mat = slice(x + 1, 0, cols, y);
            mat->put_matrix(x, 0, *sub_mat);
            delete sub_mat;
        }

        // bottom left
        if (do_bottom && do_left) {
            Matrix<T>* sub_mat = slice(0, y + 1, x, rows);
            mat->put_matrix(0, y, *sub_mat);
            delete sub_mat;
        }

        // bottom right
        if (do_bottom && do_right) {
            Matrix<T>* sub_mat = slice(x + 1, y + 1, cols, rows);
            mat->put_matrix(x, y, *sub_mat);
            delete sub_mat;
        }

        T cof = mat->determinant() * pow(-1, x + y);
        delete mat;

        return cof;
    };

    Matrix<T>* append_right(Matrix<T> & other) {
        if (rows != other.rows) {
            throw MatrixException("Cant append matrix with size (" + std::to_string(other.cols) + ", " + std::to_string(other.rows) + ") to the right of matrix with size (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        };

        Matrix<T>* mat = new Matrix<T>(cols + other.cols, rows);

        // here put_matrix can be used

        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                mat->set_at(x, y, get_at(x, y));
            }
            for (int x = 0; x < other.cols; x++) {
                mat->set_at(x + cols, y, other.get_at(x, y));
            }
        }

        return mat;
    };

    Matrix<T>* append_bottom(Matrix<T> & other) {
        if (cols != other.cols) {
            throw MatrixException("Cant append matrix with size (" + std::to_string(other.cols) + ", " + std::to_string(other.rows) + ") to the botom of matrix with size (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        };

        Matrix<T>* mat = new Matrix<T>(cols, rows + other.rows);

        for (int x = 0; x < cols; x++) {
            for (int y = 0; y < rows; y++) {
                mat->set_at(x, y, get_at(x, y));
            }
            for (int y = 0; y < other.rows; y++) {
                mat->set_at(x, y + rows, other.get_at(x, y));
            }
        }

        return mat;
    };

    T determinant() {
        if (rows != cols) {
            throw MatrixException("Can't compute the determinant if the matrix isn't square. Size : (" + std::to_string(cols) + ", " + std::to_string(rows) + ")");
        }

        if (cols == 1) {
            return get_at(0, 0);
        }

        T det = T();

        for (int x = 0; x < cols; x++) {
            det += cofactor(x, 0) * get_at(x, 0);
        }

        return det;
    };

    void apply_function(T func(int, int, T)) {
        for (int x = 0; x < cols; x++) {
            for (int y = 0; y < rows; y++) {
                set_at(x, y, func(x, y, get_at(x, y)));
            }
        }
    };

};


#endif // MATRIX_HPP

/* TODOs

mirror matrix horizontally / vertically
inverse matrix
multiply by constant

*/
