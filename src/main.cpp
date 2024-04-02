#include "matrix.hpp"
#include <iostream>


int main() {
    Matrix<int> mat{10, 10};
    std::cout << mat.rows << " : " << mat.cols << std::endl;
}
