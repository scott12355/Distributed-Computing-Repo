#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <future>
#define PARALLEL  //comment this line to run sequential version

int concurrency = std::thread::hardware_concurrency();
// int concurrency = 4;
std::vector<std::thread> threadVector;
std::vector<std::vector<int>> m1, m2, mResult;

void sum(int i);
void parallel();
void parallel_async();
void sequential();

int main()
{
    int iterations = 10;

#ifdef PARALLEL
    std::cout << "Hardware concurrency: " << concurrency << std::endl;
    std::ofstream outputTimesFile("times_parallelAsync.txt");
    outputTimesFile << "Size" << "," << "t1" << "," << "t4" << "," << "t3" << std::endl;
#else
    std::cout << "Sequential version" << std::endl;
    std::ofstream outputTimesFile("times_sequential.txt");
    outputTimesFile << "Size" << "," << "t1" << "," << "t2" << "," << "t3" << std::endl;
#endif

	outputTimesFile << std::fixed;
    outputTimesFile << std::setprecision(0);

    for (int sizeIter = 10000; sizeIter <= 10000; sizeIter+=100)
    {
        double cumulativeT1 = 0, cumulativeT2 = 0, cumulativeT3 = 0;

        std::cout << "Size: " << sizeIter << std::endl;

        for (int iter = 0; iter < iterations; iter++)
        {

            auto startT1 = std::chrono::high_resolution_clock::now();

            m1.resize(sizeIter);
            m2.resize(sizeIter);
            mResult.resize(sizeIter);

            //reset seed for random number generation
            srand((unsigned int)time(0));

            for (int index = 0; index < m1.size(); ++index)
            {
                m1[index].resize(sizeIter);
                m2[index].resize(sizeIter);
                mResult[index].resize(sizeIter);

                //fill each element of m1 and m2 with a random number between 0 and 100
                for (int j = 0; j < m1[index].size(); ++j)
                {
                    m1[index][j] = rand() % 100;
                    m2[index][j] = rand() % 100;
                    mResult[index][j] = 0;
                }
            }

            auto startT2 = std::chrono::high_resolution_clock::now();

#ifdef PARALLEL
            //parallel();
            parallel_async();
#else
			sequential();
#endif

            auto startT3 = std::chrono::high_resolution_clock::now();

			m1.clear();
			m2.clear();
			mResult.clear();

            auto end = std::chrono::high_resolution_clock::now();

            double t1 = std::chrono::duration_cast<std::chrono::nanoseconds>(startT2 - startT1).count();
            double t2 = std::chrono::duration_cast<std::chrono::nanoseconds>(startT3 - startT2).count();
            double t3 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - startT3).count();

            cumulativeT1 += t1;
            cumulativeT2 += t2;
            cumulativeT3 += t3;
        }

        outputTimesFile << sizeIter << "," << (cumulativeT1 / iterations) << "," << (cumulativeT2 / iterations) << "," << (cumulativeT3 / iterations) << std::endl;
        outputTimesFile.flush();
    }
}

void sum(int i)
{
    int portion_size = m1[i].size() / concurrency;

    for (int row = portion_size * i; row < portion_size * (i + 1); ++row)
    {
        for (int j = 0; j < m1[row].size(); ++j)
        {
            mResult[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void sequential()
{
    for (int i = 0; i < m1.size(); ++i)
    {
        for (int j = 0; j < m1[i].size(); ++j)
        {
            mResult[i][j] = m1[i][j] + m2[i][j];
        }
    }
}

void parallel()
{
    for (int i = 0; i < concurrency; ++i)
    {
        threadVector.push_back(std::thread(sum, i));
    }

    for (int i = 0; i < threadVector.size(); ++i)
    {
        threadVector[i].join();
    }

	threadVector.clear();
}


void parallel_async()
{
    std::vector<std::future<void>> futures;
    for (int i = 0; i < concurrency; ++i)
    {
        futures.push_back(std::async(std::launch::async, sum, i));
    }

    for (auto &fut : futures)
    {
        fut.get();
    }
}
