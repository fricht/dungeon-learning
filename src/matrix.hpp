#ifndef MATRIX_HPP
#define MATRIX_HPP


template <typename T>

class Matrix {

private:
    T** data;

public:
    int rows;
    int cols;

    Matrix(int r, int c) : rows(r), cols(c) {
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

};


#endif // MATRIX_HPP
