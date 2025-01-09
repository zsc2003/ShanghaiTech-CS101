#include <iostream>
#include <random>

const int N = 1e5;
const int MAX_INSERTION = 5;

int array[N], a[N];
std::mt19937 engine;  // this is a random number generator

void hack1() {
    for (int i = 0; i < N; ++i)
        array[i] = i;
}

// i from 0 to N-1
void hack2() {
    for (int i = 0; i < N; ++i)
        a[i] = i;
    for (int i = 0; N - i > MAX_INSERTION; ++i) {
        int n = N - i;
        int pos = std::uniform_int_distribution<>(0, n - 1)(engine);
        std::swap(a[i], a[i + pos]);  // quicksort.cpp L67 std::swap(*first, *choosePivot(first, last));
    }
    for (int i = 0; i < N; ++i)
        array[a[i]] = i;
}

// i from N-1 to 0 also OK.
// void hack2() {
//     for (int i = 0; i < N; ++i)
//         a[i] = i;
//     for (int i = N - 1; i >= 0; i--) {
//         int pivot = std::uniform_int_distribution<>(0, i)(engine);
//         std::swap(a[1], a[pivot]);
//         std::swap(a[1], a[i]);
//     }
//     for (int i = 0; i < N; ++i)
//         array[a[i]] = i;
// }

void hack3() {
    for (int i = 0; i < N; ++i)
        a[i] = i;
    for (int i = 0; N - i > MAX_INSERTION; i += 2) {
        int n = N - i;
        int pos1 = std::uniform_int_distribution<>(0, n - 1)(engine);
        int pos2 = std::uniform_int_distribution<>(0, n - 2)(engine);
        int pos3 = std::uniform_int_distribution<>(0, n - 3)(engine);
        pos3 += pos3 >= pos2;
        pos3 += pos3 >= pos1;
        pos2 += pos2 >= pos1;
        // sort pos1 < pos2 < pos3
        if (pos2 < pos1)
            std::swap(pos2, pos1);
        if (pos3 < pos2)
            std::swap(pos3, pos2);
        if (pos2 < pos1)
            std::swap(pos2, pos1);
        // let array[i+pos2]=i<array[i+pos1]=i+1<array[i+pos3]=i+2, then choose i+pos1 as the pivot
        std::swap(a[i], a[i + pos1]);      // quicksort.cpp L67 std::swap(*first, *choosePivot(first, last));
        std::swap(a[i + 1], a[i + pos2]);  // quicksort.cpp L76 std::swap(*low, *high);
        std::swap(a[i], a[i + 1]);         // quicksort.cpp L80 std::swap(*first, *high);
    }
    for (int i = 0; i < N; ++i)
        array[a[i]] = i;
}

int main() {
    int pivotStrategy, seed;
    std::cin >> pivotStrategy >> seed;
    engine.seed(seed);  // initialize random generator with seed

    // run quicksort algorithm with given pivotStrategy
    if (pivotStrategy == 1)
        hack1();
    if (pivotStrategy == 2)
        hack2();
    if (pivotStrategy == 3)
        hack3();

    for (int i = 0; i < N; ++i)
        std::cout << array[i] << ' ';
    std::cout << std::endl;
    return 0;
}