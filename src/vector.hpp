#ifndef VECTOR_HPP
#define VECTOR_HPP

#include <exception>
#include <string>


class VectorException : public std::exception {
private:
    std::string message;
public:
    VectorException(std::string msg) : message(msg) {};
    const char* what() const throw() {
        return message.c_str();
    }
};


template <typename T>

class Vector {

private:
    T* data;

public:
    int size;

    Vector(int s) : size(s) {
        if (s < 1) {
            throw VectorException("Invalid Vector size " + std::to_string(s) + ".");
        };

        data = new T[size];
    };

    Vector(int s, T default_value) : size(s) {
        if (s < 1) {
            throw VectorException("Invalid Vector size " + std::to_string(s) + ".");
        };

        data = new T[size];
        fill(default_value);
    };

    Vector(int s, T generator(int)) : size(s) {
        if (s < 1) {
            throw VectorException("Invalid Vector size " + std::to_string(s) + ".");
        };

        data = new T[size];
        for (int i = 0; i < size; i++) {
            data[i] = generator(i);
        }
    };

    ~Vector() {
        delete[] data;
    };

    void fill(T val) {
        for (int x = 0; x < size; x++) {
            data[x] = val;
        }
    };

    T& operator[](int pos) {
        if (pos < 0 || pos >= size) {
            // out of bounds
            throw VectorException("Error while trying to get element of Vector.\ntrying to get [" + std::to_string(pos) + "] but size is (" + std::to_string(size) + ")");
        }
        return data[pos];
    };

    template <typename oT>
    Vector<T>* operator+(Vector<oT> & other) {
        // check for types matching
        if (std::is_same<T, oT>::value == false) {
            throw VectorException("Vector types does not match");
        }
        if (size != other.size) {
            // dims not matching !!!
            throw VectorException("Dimentions (" + std::to_string(size) + ") and (" + std::to_string(other.size) + ") not matching for vector addition");
        }
        Vector<T>* vec = new Vector<T>(size);
        for (int x = 0; x < size; x++) {
            (*vec)[x] = (*this)[x] + other[x];
        }
        return vec;
    };

    template <typename oT> // other type
    Vector<T>* operator*(Vector<oT> & other) {
        // check for types matching
        if (std::is_same<T, oT>::value == false) {
            throw VectorException("Vector types does not match");
        }
        if (size != other.size) {
            // dims not matching !!!
            throw VectorException("Dimentions (" + std::to_string(size) + ") and (" + std::to_string(other.size) + ") not matching for vector multiplication (elem by elem)");
        }
        Vector<T>* vec = new Vector<T>(size);
        for (int x = 0; x < size; x++) {
            (*vec)[x] = (*this)[x] * other[x];
        }
        return vec;
    };

    template <typename nT> // new type
    Vector<nT>* vec_static_cast() {
        Vector<nT>* vec = new Vector<nT>(size);
        for (int x = 0; x < size; x++) {
            (*vec)[x] = static_cast<nT>((*this)[x]);
        }
        return vec;
    };

    template <typename oT> // other type
    T dot(Vector<oT>& other) {
        // check for types matching
        if (std::is_same<T, oT>::value == false) {
            throw VectorException("Vector types does not match");
        }
        if (size != other.size) {
            // dims not matching !!!
            throw VectorException("Dimentions (" + std::to_string(size) + ") and (" + std::to_string(other.size) + ") not matching for vector multiplication (elem by elem)");
        }
        T out = 0;
        for (int x = 0; x < size; x++) {
            out += (*this)[x] * other[x];
        }
        return out;
    };

};


#endif // VECTOR_HPP
