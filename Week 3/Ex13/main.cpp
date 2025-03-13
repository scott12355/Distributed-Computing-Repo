#include <fstream>
#include <iostream>
#include <vector>
#include <thread>


void add_vectors(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& result, int row) {
    result[row] = v1[row] + v2[row];
}

int main() {
    std::vector<int> v1 = {2, 3, 4, 3, 2, 6, 3, 8, 30, 11};
    std::vector<int> v2 = {5, 4, 8, 6, 2, 3, 7, 87, 2, 12};
    std::vector<int> result(10);

    // Create a vector to hold the threads
    std::vector<std::thread> threads;
    threads.reserve(10);
    // Launch a thread for each row
    for (int i = 0; i < 10; ++i) { // emplace_back is more efficient than push_back. creates the thread in place, not create then move to the vector
        //threads.push_back(std::thread(add_vectors, std::ref(v1), std::ref(v2), std::ref(result), i));
        threads.emplace_back(add_vectors, std::ref(v1), std::ref(v2), std::ref(result), i);
    }

    // Join all threads
    for (auto& th : threads) {
        th.join();
    }

    // Print the result to the console
    std::cout << "Result: ";
    for (const auto& val : result) {
        std::cout << val << " ";
    }
    std::cout << std::endl;



    // Save values and results
    std::ofstream file2("results.txt");
    if (file2.is_open()) {
        for (int i = 0; i < 10; ++i) {
            file2 << v1[i] << " + " << v2[i] << " = " << result[i] << std::endl;
        }
        file2.close();
    } else {
        std::cout << "Error opening file" << std::endl;
    }

    return 0;
}