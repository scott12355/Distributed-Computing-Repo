#include <thread>
#include <iostream>
#include <vector>
#include <string>
#include <mutex>

std::vector<std::string> strings;
std::mutex mtx;

void addString1() {
    mtx.lock();
    printf("mutex locked by thread 1\n");
    strings.push_back("Thread 1 was here and pushed 'a'\n");
    strings.push_back("Thread 1 was here and pushed 'b'\n");
    strings.push_back("Thread 1 was here and pushed 'c'\n");
    strings.push_back("Thread 1 was here and pushed 'd'\n");
    strings.push_back("Thread 1 was here and pushed 'e'\n");
    strings.push_back("Thread 1 was here and pushed 'f'\n");
    strings.push_back("Thread 1 was here and pushed 'g'\n");
    strings.push_back("Thread 1 was here and pushed 'h'\n");
    strings.push_back("Thread 1 was here and pushed 'i'\n");
    strings.push_back("Thread 1 was here and pushed 'j'\n");
    mtx.unlock();
    printf("mutex unlocked by thread 1\n");
}

void addString2() {
    std::lock_guard<std::mutex> lock(mtx);
    printf("mutex locked by thread 2\n");
    strings.push_back("Thread 2 was here and pushed '1'\n");
    strings.push_back("Thread 2 was here and pushed '2'\n");
    strings.push_back("Thread 2 was here and pushed '3'\n");
    strings.push_back("Thread 2 was here and pushed '4'\n");
    strings.push_back("Thread 2 was here and pushed '5'\n");
    strings.push_back("Thread 2 was here and pushed '6'\n");
    strings.push_back("Thread 2 was here and pushed '7'\n");
    strings.push_back("Thread 2 was here and pushed '8'\n");
    strings.push_back("Thread 2 was here and pushed '9'\n");
    strings.push_back("Thread 2 was here and pushed '10'\n");
    printf("mutex unlocked by thread 2\n");
}

int main() {
    std::thread t1(addString1);
    std::thread t2(addString2);

    t1.join();
    t2.join();

    // Print the strings to verify the result
    for (const auto& str : strings) {
        std::cout << str;
    }

    return 0;
}