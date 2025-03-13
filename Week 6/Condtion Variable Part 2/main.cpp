#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex threadMutex;
std::condition_variable cv;
std::vector<int> numbers(10);
std::vector<int>numbersx2(10);
bool readyToMultiply = false;
bool readyToPrint = false;
// producer thread
void addInts() {
    std::unique_lock<std::mutex> lock(threadMutex);
    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = rand() % 100;
    }
    readyToMultiply = true;
    cv.notify_all();
}

// intermediate thread
void multiply() {
    std::unique_lock<std::mutex> lock(threadMutex);
    cv.wait(lock, [] { return readyToMultiply; });
    for (int i = 0; i < numbers.size(); i++) {
        numbersx2[i] = numbers[i] * 2;
    }
    readyToPrint = true;
    cv.notify_all();
}


// consumer thread
void addAndPrintInts() {
    std::unique_lock<std::mutex> lock(threadMutex);

    cv.wait(lock, [] { return readyToPrint; });

    for (int i = 0; i < numbers.size(); i++) {
        numbersx2[i] ++;
    }

    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << std::endl;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<std::thread> threads;

    threads.push_back(std::thread(multiply));
    threads.push_back(std::thread(addAndPrintInts));
    threads.push_back(std::thread(addInts));

    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}