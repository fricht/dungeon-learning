#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"


int main() {
    Matrix<int> mat{3, 2, 1};
    Matrix<int> mat2{4, 3, 2};
    Matrix<int>* res = mat.matmul(mat2);

    for (int x = 0; x < res->cols; x++) {
        for (int y = 0; y < res->rows; y++) {
            //std::cout << (*res)[res->linear_index(x, y)] << std::endl;
        }
    }
    std::cout << std::endl;
    Matrix<int> res2 = *res;
    for (int x = 0; x < res2.cols; x++) {
        for (int y = 0; y < res2.rows; y++) {
            //std::cout << res2[res2.linear_index(x, y)] << std::endl;
        }
    }

    std::cout << std::endl;
    int a = 5;
    std::cout << 3 ** (&a) << std::endl;
}
