#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <exception>
#include <string>
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
        data = new T*[rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new T[cols];
        }
    };

    Matrix(int c, int r, T default_value) : cols(c), rows(r) {
        // not using fill to avoid doing same loop twice
        data = new T*[rows];
        for (int y = 0; y < rows; y++) {
            data[y] = new T[cols];
            for (int x = 0; x < cols; x++) {
                data[y][x] = default_value;
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

    template <typename oT>
    Matrix<T>* operator+(Matrix<oT> & other) {
        // check for types matching
        if (std::is_same<T, oT>::value == false) {
            throw MatrixException("Matrix types does not match");
        }
        if (rows != other.rows || cols != other.cols) {
            // dims not matching !!!
            throw MatrixException("Dimentions (" + std::to_string(cols) + ", " + std::to_string(rows) + ") and (" + std::to_string(other.cols) + ", " + std::to_string(other.rows) + ") not matching for matrix addition");
        }
        Matrix<T>* mat = new Matrix<T>(cols, rows);
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                (*mat)[mat->linear_index(x, y)] = (*this)[linear_index(x, y)] + other[other.linear_index(x, y)];
            }
        }
        return mat;
    };

    template <typename oT> // other type
    Matrix<T>* operator*(Matrix<oT> & other) {
        // check for types matching
        if (std::is_same<T, oT>::value == false) {
            throw MatrixException("Matrix types does not match");
        }
        if (rows != other.rows || cols != other.cols) {
            // dims not matching !!!
            throw MatrixException("Dimentions (" + std::to_string(cols) + ", " + std::to_string(rows) + ") and (" + std::to_string(other.cols) + ", " + std::to_string(other.rows) + ") not matching for matrix multiplication (elem by elem)\nUse .matmul(Matrix) to perform real matrix multipication");
        }
        Matrix<T>* mat = new Matrix<T>(cols, rows);
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                (*mat)[mat->linear_index(x, y)] = (*this)[linear_index(x, y)] * other[other.linear_index(x, y)];
            }
        }
        return mat;
    };

    template <typename nT> // new type
    Matrix<nT>* mat_static_cast() {
        Matrix<nT>* mat = new Matrix<nT>(cols, rows);
        for (int y = 0; y < rows; y++) {
            for (int x = 0; x < cols; x++) {
                (*mat)[mat->linear_index(x, y)] = static_cast<nT>((*this)[linear_index(x, y)]);
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

    template <typename oT> // other type
    Matrix<T>* matmul(Matrix<oT>& other) {
        // check for types matching
        if (std::is_same<T, oT>::value == false) {
            throw MatrixException("Matrix types does not match");
        }
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
                (*mat)[mat->linear_index(x, y)] = (rows_vec[y])->dot(*(cols_vec[y]));
                std::cout << (*mat)[mat->linear_index(x, y)] << std::endl;
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

    // TODO : implement sub-matrix

};


#endif // MATRIX_HPP
