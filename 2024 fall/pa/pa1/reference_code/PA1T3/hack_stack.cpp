#include <iostream>
#include <random>
#include <stack>
#include <utility>

const int N = 1e5;
const int MAX_INSERTION = 5;

int array[N];
std::mt19937 engine;  // this is a random number generator
std::stack<std::pair<int, int>> s;

void hack1() {
}

void hack2() {
    for (int i = 0; N - i > MAX_INSERTION; ++i) {
        int n = N - i;
        int pos = std::uniform_int_distribution<>(0, n - 1)(engine);
        s.push({i, i + pos});  // quicksort.cpp L67 std::swap(*first, *choosePivot(first, last));
    }
}

void hack3() {
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
        s.push({i, i + pos1});      // quicksort.cpp L67 std::swap(*first, *choosePivot(first, last));
        s.push({i + 1, i + pos2});  // quicksort.cpp L76 std::swap(*low, *high);
        s.push({i, i + 1});         // quicksort.cpp L80 std::swap(*first, *high);
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("hack.in", "r", stdin);
    freopen("hack_stack.out", "w", stdout);
#endif
    int pivotStrategy,
        seed;
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
        array[i] = i;
    while (!s.empty()) {
        auto [pos1, pos2] = s.top();
        s.pop();
        std::swap(array[pos1], array[pos2]);
    }
    for (int i = 0; i < N; ++i)
        std::cout << array[i] << ' ';
    std::cout << std::endl;
    return 0;
}