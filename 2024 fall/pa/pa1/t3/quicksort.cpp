#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

const int N = 1e5;
const int MAX_INSERTION = 5;

int array[N];
std::mt19937 engine;  // this is a random number generator

namespace timer {
auto start = std::chrono::steady_clock::now();

void restart() {
    start = std::chrono::steady_clock::now();
}

double duration() {
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration<double>(now - start).count();
}
};  // namespace timer

// Pivot Strategy #1: always choose the first element as the pivot
int* chooseFirst(int* first, [[maybe_unused]] int* last) {
    return first;
};

// Pivot Strategy #2: choose a random element as the pivot
int* chooseRandom(int* first, int* last) {
    int n = last - first;
    int pos = std::uniform_int_distribution<>(0, n - 1)(engine);
    return first + pos;
};

// Pivot Strategy #3: choose the median of three random elements as the pivot
int* medianRandom(int* first, int* last) {
    int n = last - first;
    int pos1 = std::uniform_int_distribution<>(0, n - 1)(engine);
    int pos2 = std::uniform_int_distribution<>(0, n - 2)(engine);
    int pos3 = std::uniform_int_distribution<>(0, n - 3)(engine);
    pos3 += pos3 >= pos2;
    pos3 += pos3 >= pos1;
    pos2 += pos2 >= pos1;
    // sort first[pos1] <= first[pos2] <= first[pos3]
    if (first[pos2] < first[pos1])
        std::swap(pos2, pos1);
    if (first[pos3] < first[pos2])
        std::swap(pos3, pos2);
    if (first[pos2] < first[pos1])
        std::swap(pos2, pos1);
    // the median first+pos2 is the pivot
    return first + pos2;
};

void insertionSort(int* first, int* last) {
    for (int* i = first + 1; i < last; ++i) {
        for (int* j = i; j > first && *(j - 1) > *j; --j)
            std::swap(*(j - 1), *j);
    }
}

void quicksort(int* first, int* last, decltype(chooseFirst) choosePivot) {
    if (last - first <= MAX_INSERTION)
        return insertionSort(first, last);
    std::swap(*first, *choosePivot(first, last));
    int *low = first + 1, *high = last - 1;
    while (true) {
        while (low <= high && *low < *first)
            ++low;
        while (low <= high && *high > *first)
            --high;
        if (low > high)
            break;
        std::swap(*low, *high);
        ++low;
        --high;
    }
    std::swap(*first, *high);
    quicksort(first, high, choosePivot);
    quicksort(low, last, choosePivot);
}

int main() {
    int pivotStrategy, seed;
    std::cin >> pivotStrategy >> seed;
    engine.seed(seed);  // initialize random generator with seed

    std::ifstream arrayFile("hack.out");
    for (int i = 0; i < N; ++i)
        arrayFile >> array[i];  // read the array from file "hack.out"

    // run quicksort algorithm with given pivotStrategy
    timer::restart();
    if (pivotStrategy == 1)
        quicksort(array, array + N, chooseFirst);
    if (pivotStrategy == 2)
        quicksort(array, array + N, chooseRandom);
    if (pivotStrategy == 3)
        quicksort(array, array + N, medianRandom);

    std::cout << "The quicksort algorithm takes " << timer::duration() << "seconds" << std::endl;
    return 0;
}