#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <thread>

void add(std::vector<int> a, std::vector<int> b, int index, std::vector<int> &results) {
    results.at(index) = a[index] + b[index];
}

int main() {
    clock_t start = clock();
    std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::vector<int> results = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    std::vector<std::thread> threads;

    for (int i = 0; i < v1.size(); i++) {
        add(v1, v2, i, results);
    }


    for (int i = 0; i < results.size(); i++) {
        std::cout << results[i] << std::endl;
    }

    // Write values and result to file
    std::ofstream file("results.txt");
    if (file.is_open()) {
        for (int i = 0; i < results.size(); i++) {
            file << v1[i] << " + " << v2[i] << " = ";
            file << results[i] << std::endl;
        }
        file.close();
    } else {
        std::cout << "Unable to open file" << std::endl;
    }
    clock_t stop = clock();
    double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
    printf("\nTime elapsed: %.5f\n", elapsed);
}

//
//
// #include <iostream>
// #include <vector>
// #include <fstream>
// #include <iomanip>
// #include <thread>
// #include <ctime>
//
// void add(std::vector<int> a, std::vector<int> b, int index, std::vector<int> &results) {
//     results.at(index) = a[index] + b[index];
// }
//
// int main() {
//     clock_t start = clock();
//     std::vector<int> v1 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     std::vector<int> v2 = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
//     std::vector<int> results(v1.size(), 0);
//     std::vector<std::thread> threads;
//
//     for (int i = 0; i < v1.size(); i++) {
//         threads.emplace_back(add, v1, v2, i, std::ref(results));
//     }
//
//     for (auto &thread : threads) {
//         thread.join();
//     }
//
//     for (int i = 0; i < results.size(); i++) {
//         std::cout << results[i] << std::endl;
//     }
//
//     // Write values and result to file
//     std::ofstream file("results.txt");
//     if (file.is_open()) {
//         for (int i = 0; i < results.size(); i++) {
//             file << v1[i] << " + " << v2[i] << " = ";
//             file << results[i] << std::endl;
//         }
//         file.close();
//     } else {
//         std::cout << "Unable to open file" << std::endl;
//     }
//     clock_t stop = clock();
//     double elapsed = (double) (stop - start) / CLOCKS_PER_SEC;
//     printf("\nTime elapsed: %.5f\n", elapsed);
// }