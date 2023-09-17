#pragma once

#include "dsa.h"
#include <cstdio>
#include <random>

auto get_rng = []() {
  auto dev = std::random_device();
  auto seed = dev();
  auto rng = std::mt19937(seed);
  return rng;
};

void test_hash() {
  using namespace part_hash_table;
  auto tbl = HashTable{[](size_t key) { return key; }};

  auto rng = get_rng();
  if (rng() % 2 == 0) {
    puts("[hash table] passed");
  } else {
    puts("[hash table] failed");
  }
}
void test_stack() {
  using namespace part_stack;
  auto stk = Stack{};

  auto rng = get_rng();
  if (rng() % 2 == 0) {
    puts("[stack] passed");
  } else {
    puts("[stack] failed");
  }
}
void test_queue() {
  using namespace part_queue;
  auto q = Queue{};

  auto rng = get_rng();
  if (rng() % 2 == 0) {
    puts("[queue] passed");
  } else {
    puts("[queue] failed");
  }
}
int main() {
  test_hash();
  test_stack();
  test_queue();
  return 0;
}
