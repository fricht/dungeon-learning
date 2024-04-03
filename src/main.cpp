#include <iostream>
#include "matrix.hpp"


int main() {
    Matrix<int> mat{10, 11, 4};
    Matrix<int> mat2{10, 11, -1};
    Matrix<float>* matf = new Matrix<float>{10, 11, 0.5f};
    Matrix<int>* mat_add = mat + mat2;
    std::cout << mat_add->rows << " : " << mat_add->cols << std::endl;
    std::cout << (*mat_add)[mat_add->linear_index(3, 9)] << std::endl;
    std::cout << (*(*(mat_add->mat_static_cast<float>()) + (*matf)))[mat_add->linear_index(3, 9)] << std::endl;
}
