#include <cassert>
#include <cstdio>
#include <functional>
#include <random>

#include "dsa.h"

#define CHK(cond)                                                              \
  do {                                                                         \
    if (!(cond)) {                                                             \
      printf("failed at LINE %d\n", __LINE__);                                 \
      return false;                                                            \
    }                                                                          \
  } while (0)

// the random number generator
static std::mt19937_64 rng;
// either quick_sort for merge_sort
static std::function<void(lsort::List &)> sort_func;

const std::size_t N = 10;  // list size
const std::size_t M = 100; // list value bound
int main() {
  // initialize the random number generator

  /*
  auto dev = std::random_device();
  auto seed = dev();
  rng = std::mt19937_64(seed);*/

  // pick a sort function
  sort_func = lsort::merge_sort;
  sort_func = lsort::quick_sort;

  // generate a random list
  lsort::List l;
  for (std::size_t i = 0; i < N; i++) {
    //l.push_front(rng() % M);
    l.push_front(rand() % M);

  }

  // sort the list
  sort_func(l);

  // display the sorted list
  for (auto x : l) {
    printf("%u, ", x);
  }
  putchar('\n');

  return 0;
}

namespace lsort {
std::size_t list_size(const lsort::List &la) {
  std::size_t sz = 0;
  for (auto i = la.begin(); i != la.end(); i++, sz++) {
  }
  return sz;
}
std::size_t random_index(const std::size_t n) { return rng() % n; }
void merge_sort(List &list_to_sort) {
  auto n = list_size(list_to_sort);
  if (n <= 1) {
    return;
  }
  auto m = n / 2;
  List lhs, rhs;
  for (decltype(n) i = 0; i < m; i++) {
    lhs.push_front(list_to_sort.front());
    list_to_sort.pop_front();
  }
  for (decltype(n) i = m; i < n; i++) {
    rhs.push_front(list_to_sort.front());
    list_to_sort.pop_front();
  }
  merge_sort(lhs), merge_sort(rhs);
  merge(lhs, rhs, list_to_sort);
}

void quick_sort(List &list_to_sort) {
  auto n = list_size(list_to_sort);
  if (n <= 2) {
    list_to_sort.sort();
    return;
  }

  auto pivot = select_pivot(list_to_sort);
  auto leq = lsort::List{}, gt = lsort::List{};
  partition(list_to_sort, leq, gt, pivot);
  quick_sort(leq), quick_sort(gt);
  list_to_sort.clear();
  for (auto x : leq) {
    list_to_sort.push_front(x);
  }
  for (auto x : gt) {
    list_to_sort.push_front(x);
  }
  list_to_sort.reverse();
}
} // namespace lsort
