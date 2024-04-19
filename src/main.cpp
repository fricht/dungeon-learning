#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"
#include <random>


int gen(int x, int y) {
    return std::rand() % 21 - 10;
};


int main() {

    Matrix<int> * mat = new Matrix<int>(4, 4, gen);

    for (int y = 0; y < mat->rows; y++) {
        for (int x = 0; x < mat->cols; x++) {
            std::cout << mat->get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };

    std::cout << std::endl << std::endl;

    std::cout << "determinant " << mat->determinant() << std::endl;

    for (int y = 0; y < mat->rows; y++) {
        for (int x = 0; x < mat->cols; x++) {
            std::cout << mat->cofactor(x, y) << "  ";
        }
        std::cout << std::endl;
    };

    delete mat;

}
