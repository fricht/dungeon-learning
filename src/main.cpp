#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"
#include <random>


float gen(int, int) {
    return std::rand();
};


int main() {
    Matrix<float> mat(2, 3, gen);

    std::cout << gen(2, 3) << std::endl << std::endl;

    for (int x = 0; x < 2; x++) {
        for (int y = 0; y < 3; y++) {
            std::cout << mat.get_at(x, y) << "  ";
        }
        std::cout << std::endl;
    };
}
