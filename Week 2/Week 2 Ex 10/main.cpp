#include <iostream>
#include <vector>


void multiplyVectors(std::vector<int> &vec1, std::vector<int> &vec2, std::vector<int> &results) {
    for (int i = 0; i < vec1.size(); i++) {
        results[i] = vec1[i] * vec2[i];
    }
}

void printVector(std::vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5, 6};

    std::vector<int> results = {0,0,0};

    printf("Hello, World!\n");

    printVector(results);
    multiplyVectors(vec1, vec2, results);
    printVector(results);


}