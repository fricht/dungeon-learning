#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"
#include <random>


int main() {
    Matrix<float> mat{3, 2};
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 2; y++) {
            mat.set_at(x, y, std::rand() / pow(2, 32));
        }
    }
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 2; y++) {
            std::cout << mat.get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    Matrix<float> mat2 = *(mat.transpose());
    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 3; y++) {
            std::cout << mat2.get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    }
}
