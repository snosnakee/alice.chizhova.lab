#include <iostream>
#include <new>
#include <cstddef>

int main() {
    std::size_t rows = 0;
    std::size_t cols = 0;

    if (!(std::cin >> rows >> cols)) {
        std::cerr << "Input error\n";
        return 1;
    }

    int** matrix = new (std::nothrow) int*[rows];
    if (!matrix) {
        std::cerr << "Memory error\n";
        return 2;
    }

    for (std::size_t i = 0; i < rows; ++i) {
        matrix[i] = new (std::nothrow) int[cols];
        if (!matrix[i]) {
            std::cerr << "Memory error\n";
            for (std::size_t j = 0; j < i; ++j) {
                delete[] matrix[j];
            }
            delete[] matrix;
            return 2;
        }
    }

    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < cols; ++j) {
            if (!(std::cin >> matrix[i][j])) {
                std::cerr << "Input error\n";
                for (std::size_t k = 0; k < rows; ++k) {
                    delete[] matrix[k];
                }
                delete[] matrix;
                return 1;
            }
        }
    }

    for (std::size_t j = 0; j < cols; ++j) {
        for (std::size_t i = 0; i < rows; ++i) {
            std::cout << matrix[i][j];
            if (i + 1 < rows) {
                std::cout << " ";
            }
        }
        std::cout << "\n";
    }

    for (std::size_t i = 0; i < rows; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    return 0;
}
