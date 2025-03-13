// async example
#include <iostream>       // std::cout
#include <future>         // std::async, std::future
// #include <windows.h>


// a non-optimized way of checking for prime numbers:
bool is_prime (int x)
{
    std::cout << "Calculating. Please, wait...\n";

    for (int i=2; i<x; ++i) if (x%i==0)
        return false;

    return true;
}

int sum (int* x, int* y,int* z)
{
    std::cout << "Calculating. Please, wait...\n";
    return *x + *y + *z;
}

int avg (std::vector<int> x, int size) {
    int sum = 0;
    for  (int i = 0; i < size; i++){
        sum += x[i];
    }
    return sum/size;
}

std::vector<int> avg2Vecotrs(std::vector<int> v1, std::vector<int> v2, int size) {
    std::vector<int> ret;
    int v1Avg = avg(v1, size);
    int v2Avg = avg(v2, size);
    ret.push_back(v1Avg);
    ret.push_back(v2Avg);
    return ret;
}

int main ()
{




    // call is_prime(313222313) asynchronously:
    // std::future<bool> fut = std::async (std::launch::async, is_prime, 313222313);

    int a,b,c;
    a = 1; b = 2; c = 3;
    std::future<int> futSum = std::async (std::launch::async, sum, &a, &b, &c);
    std::cout << "Checking whether 313222313 is prime.\n";
    std::cout << "Here main thread sleeps for 1 sec\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    std::cout << "Then gets the result of the function\n";

    std::future<int> futAvg = std::async(std::launch::async, avg, std::vector<int>{1,2,3,4,5,6,7,8,9,10}, 10);

    std::future<std::vector<int>> futAvg2Vec = std::async(std::launch::async, avg2Vecotrs, std::vector<int>{1,2,3,4,5,6,7,8,9,10}, std::vector<int>{11,12,13,14,15,16,17,18,19,20}, 10);


    int ret = futSum.get();
    std::cout << "The sum = " << ret << std::endl;

    ret = futAvg.get();
    std::cout << "The avg = " << ret << std::endl;

    std::vector<int> retV = futAvg2Vec.get();
    std::cout << "The avg of 2 vectors = " << retV[0] << ", " << retV[1] << std::endl;



    return 0;
}
