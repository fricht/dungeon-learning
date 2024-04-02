#include "matrix.hpp"


template <typename T>

Matrix<T>::Matrix(int r, int c) : rows(r), cols(c) {
    data = new T*[rows];
    for (int i = 0; i < rows; i++) {
        data[i] = new T[cols];
    }
};


template <typename T>

Matrix<T>::~Matrix() {
    for (int i = 0; i < rows; i++) {
        delete[] data[i];
    }
    delete[] data;
};
