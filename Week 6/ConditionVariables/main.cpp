#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <vector>

std::mutex threadMutex;
std::condition_variable cv;
std::vector<int> numbers(10);
bool ready = false;
// producer thread
void addInts() {
    std::unique_lock<std::mutex> lock(threadMutex);
    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] = rand() % 100;
    }
    ready = true;
    cv.notify_all();
}

// consumer thread
void multiplyAndPrintInts() {
    std::unique_lock<std::mutex> lock(threadMutex);

    cv.wait(lock, [] { return ready; });

    for (int i = 0; i < numbers.size(); i++) {
        numbers[i] *= 2;
    }

    for (int i = 0; i < numbers.size(); i++) {
        std::cout << numbers[i] << std::endl;
    }
}

int main() {
    std::cout << "Hello, World!" << std::endl;
    std::vector<std::thread> threads;


    threads.push_back(std::thread(multiplyAndPrintInts));
    threads.push_back(std::thread(addInts));

    for (auto& thread : threads) {
        thread.join();
    }
    return 0;
}