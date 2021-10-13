#include <iostream>
#include "ArraySequence.h"
#include "SequenceSorter.h"
#include <random>
#include <chrono>

int main() {
    std::cout << "Hello, World!" << std::endl;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(-1000, 1000);
    auto array = new ArraySequence<int>();
    for(int i = 0; i < 10000; i++){
        array->Append(dist(gen));
    }
    auto t1 = std::chrono::high_resolution_clock::now();
    SequenceSorter<int>::QuickSort(array);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, milli> ms_double = t2 - t1;
    cout << "Result: " << ms_double.count() << "ms" << endl;

    auto t3 = std::chrono::high_resolution_clock::now();
    SequenceSorter<int>::QuickSort(array);
    auto t4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, milli> ms_doubl1 = t4 - t3;
    cout << "Result: " << ms_doubl1.count() << "ms" << endl;

    return 0;
}
