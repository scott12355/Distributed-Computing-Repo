#include <iostream>
#include <vector>
#include <thread>

void multiply(std::vector<int> a, std::vector<int> b, std::vector<int>* result, int index)
{
    result->at(index) = a[index] * b[index];
}

int main()
{
    std::vector<int> v1 = { 3,4,5,6 }, v2 = { 10,11,12,13 };
    std::vector<int> vResult = { 0,0,0,0 };
    std::vector<std::thread> threads;

    for (int i = 0; i < vResult.size(); i++)
    {
        threads.push_back(std::thread(multiply, v1, v2, &vResult, i));
    }

    for (int i = 0; i < vResult.size(); i++)
    {
        threads[i].join();
    }

    for (int i = 0; i < vResult.size(); i++)
    {
        std::cout << v1[i] << " * " << v2[i] << " = " << vResult[i] << "\n";
    }
}
