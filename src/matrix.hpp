#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <exception>
#include <string>


class MatrixException : public std::exception {
private:
    std::string message;
public:
    MatrixException(std::string msg) : message(msg) {};
    std::string what() {
        return "Matrix Error : " + message;
    };
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

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    };

    T& operator[](int x, int y) {
        if (x < 0 || y < 0 || x >= cols || y >= rows) {
            // out of bounds
            throw MatrixException("Error while trying to get element out of matrix.\ntrying to get [" + std::to_string(x) + " , " + std::to_string(y) + "] but dimentions are (" + std::to_string(cols) + " , " + std::to_string(rows) + ")");
        }
        return data[x][y];
    };

    Matrix operator+(Matrix & other) {
        if (rows != other.rows || cols != other.cols) {
            // dims not matching !!!
            throw MatrixException("Dimentions (" + std::to_string(cols) + " , " + std::to_string(rows) + ") and (" + std::to_string(other.cols) + " , " + std::to_string(other.rows) + ") not matching for matrix addition");
        }
        Matrix mat = Matrix(cols, rows);
        for (int x = 0; x < rows; x++) {
            for (int y = 0; y < cols; y++) {
                mat[x, y] = data[x, y] + other.data[x, y];
            }
        }
        return mat;
    };

};


#endif // MATRIX_HPP
