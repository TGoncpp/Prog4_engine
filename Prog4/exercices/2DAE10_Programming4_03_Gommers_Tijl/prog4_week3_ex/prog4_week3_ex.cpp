
#include <iostream>
#include <chrono>
#include <vector>
#include <algorithm>
#include <numeric>

double CalculateAverage(std::vector<double> vector);

template<typename T>
void PrintAverageLooptimeOfBuffer(T* buffer, int size);


struct transform
{
    float matrix[16] = {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1
    };
};

class GameObject
{
public:
    transform local{};
    int id{5};

    GameObject* operator*=(int other)
    {
         id *= other;
         return this;
    }
};

int main()
{
    static const int size{ 1000000 };
    GameObject* bufferGameObj = new GameObject[size]{};
    int* bufferInt = new int[size]{};

    std::cout << "print looptime of ints\n";
    PrintAverageLooptimeOfBuffer(bufferInt, size);
    std::cout << "\n\n";
    std::cout << "print looptime of gameObjects\n";
    PrintAverageLooptimeOfBuffer(bufferGameObj, size);


    delete[] bufferGameObj;
    delete[] bufferInt;
}

double CalculateAverage(std::vector<double> vector)
{
    auto minMax = std::minmax_element(vector.cbegin(), vector.cend());
    std::pair<double, double> dMinMax = std::make_pair<>(*minMax.first, *minMax.second);

    vector.erase(std::remove_if(vector.begin(), vector.end(), [dMinMax](double e)
        { return   e == dMinMax.first || e == dMinMax.second; }), vector.end());

    return std::accumulate(vector.cbegin(), vector.cend(), 0.0) / vector.size();
}

template<typename T>
void PrintAverageLooptimeOfBuffer(T* buffer, int size)
{
    const int vectorSize{ 10 };
    std::vector< double> vecStoredTimes(vectorSize);
    
    for (int stepsize = 1; stepsize <= 1024; stepsize *= 2)
    {
        for (int recordTest = 0; recordTest < vectorSize; ++recordTest)
        {
    
            auto start = std::chrono::high_resolution_clock::now();
            for (int i{}; i < size; i += stepsize)
            {
                buffer[i] *= 2;
            }
            auto end = std::chrono::high_resolution_clock::now();
            auto time = std::chrono::duration<double, std::micro>(end - start);
            vecStoredTimes[recordTest] = time.count();
    
        }
    
    
        std::cout << CalculateAverage(vecStoredTimes) << " : " << stepsize << "\n";
    
    
    }
}