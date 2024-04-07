#include <iostream>
#include "matrix.hpp"


int main() {
    Matrix<int> mat{10, 11, 4};
    std::cout << mat[mat.linear_index(2, 3)] << std::endl;
    mat[mat.linear_index(2, 3)] = 3;
    std::cout << mat[mat.linear_index(2, 3)] << std::endl;
}
