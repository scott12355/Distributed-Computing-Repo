#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <thread>


// use threads to increment each element of the matrix
// function to increment matrix elements
void increment_matrix(std::vector<std::vector<int>>& matrix, int start_row, int end_row) {
    for (int i = start_row; i < end_row; ++i) {
        for (int j = 0; j < matrix[i].size(); ++j) {
            ++matrix[i][j];
        }
    }
}

int main() {
    std::srand(std::time(0)); // use current time as seed for random generator

    const int rows = 100;
    const int cols = 1000000;
    std::vector<std::vector<int>> matrix(rows, std::vector<int>(cols));

    // populate matrix with random numbers
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = std::rand() % 100;
        }
    }

    // print matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::vector<std::thread> threads;
    for (int i = 0; i < rows; ++i) {
        threads.emplace_back( std::thread(increment_matrix, std::ref(matrix), i, i + 1));
    }
    // join threads
    for (int i = 0; i < rows; ++i) {
        threads[i].join();
    }

    // print matrix
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}