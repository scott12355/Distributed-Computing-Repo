#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

// function to sum one row given the index of the row
void sumRow(const std::vector<int>& rowA, const std::vector<int>& rowB, std::vector<int>& result) {
    for (int j = 0; j < rowA.size(); j++) {
        result.push_back(rowA[j] + rowB[j]);
    }
}

// function to sum a range of rows
void sumRows(const std::vector<std::vector<int>>& matrixA, const std::vector<std::vector<int>>& matrixB, std::vector<std::vector<int>>& results, int startRow, int endRow) {
    for (int i = startRow; i < endRow; i++) {
        for (int j = 0; j < matrixA[i].size(); j++) {
            results[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
}

int main() {
    int size = 2400;
    srand((unsigned int) time(0)); // set random seed
    // two vectors matrix
    // Initialize 50x50 matrices
    std::vector<std::vector<int>> matrixA(size, std::vector<int>(size, 1)); // Example initialization with all elements as random
    std::vector<std::vector<int>> matrixB(size, std::vector<int>(size, 2)); // Example initialization with all elements as 2


    // populate with random values
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j++) {
            matrixA[i][j] = rand() % 100;
            matrixB[i][j] = rand() % 100;
        }
    }

    std::vector<std::vector<int>> results(size, std::vector<int>(size));

    // sum of two vectors matrix

    // start timer
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < matrixA.size(); i++) {
        std::vector<int> row;
        for (int j = 0; j < matrixA[i].size(); j++) {
            row.push_back(matrixA[i][j] + matrixB[i][j]);
        }
        results[i] = row;
    }

    // end timer
    auto end = std::chrono::high_resolution_clock::now();
    double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // print time elapsed
    std::cout << "Time Elapsed: " << duration << " nanoseconds" << std::endl;

    // for (const auto& row : results) {
    //     for (const auto& elem : row) {
    //         std::cout << elem << " ";
    //     }
    //     std::cout << std::endl;
    // }

    // With thread for each row
    results.clear();
    results.resize(size, std::vector<int>(size));


    std::cout << std::endl << "With thread for each row" << std::endl;

    // start timer
    start = std::chrono::high_resolution_clock::now();

    // Create threads to process each half of the matrix
    std::thread t1(sumRows, std::cref(matrixA), std::cref(matrixB), std::ref(results), 0, size/2);
    std::thread t2(sumRows, std::cref(matrixA), std::cref(matrixB), std::ref(results), size/2, size);

    // Join threads
    t1.join();
    t2.join();

    // end timer
    end = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();


    std::cout << "Time Elapsed: " << duration << " nanoseconds" << std::endl;

    for (const auto& row : results) {
        for (const auto& elem : row) {
            std::cout << elem << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}