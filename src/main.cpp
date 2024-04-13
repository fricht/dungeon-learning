#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"
#include <random>


float gen(int, int) {
    return std::rand();
};


int main() {
    Matrix<float> mat(2, 3, gen);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 2; x++) {
            std::cout << mat.get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };

    std::cout << std::endl;

    Matrix<float> mat2(4, 3, gen);

    for (int y = 0; y < 3; y++) {
        for (int x = 0; x < 4; x++) {
            std::cout << mat2.get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };

    std::cout << std::endl;

    Matrix<float>* matS = mat.append_right(mat2);

    for (int y = 0; y < matS->rows; y++) {
        for (int x = 0; x < matS->cols; x++) {
            std::cout << matS->get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };

    //

    Matrix<float>* Tmat = mat.transpose();

    for (int y = 0; y < 2; y++) {
        for (int x = 0; x < 3; x++) {
            std::cout << Tmat->get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };

    std::cout << std::endl;

    Matrix<float>* Tmat2 = mat2.transpose();

    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 3; x++) {
            std::cout << Tmat2->get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };

    std::cout << std::endl;

    Matrix<float>* TmatS = Tmat->append_bottom(*Tmat2);

    for (int y = 0; y < TmatS->rows; y++) {
        for (int x = 0; x < TmatS->cols; x++) {
            std::cout << TmatS->get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };

}
