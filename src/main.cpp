#include <iostream>
#include "matrix.hpp"
#include "vector.hpp"
#include <random>


float gen(int x, int y) {
    return std::rand();
};


int main() {

    Matrix<float> * mat = new Matrix<float>(4, 4, gen);
    mat->display();

    std::cout << std::endl;

    Matrix<float>* inv_mat = mat->inverse();
    inv_mat->display();

    Matrix<float>* prod_mat = mat->matmul(*inv_mat);
    prod_mat->display();

    delete mat;
    delete inv_mat;

}
