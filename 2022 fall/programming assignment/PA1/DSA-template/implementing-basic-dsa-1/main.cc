#include <cstdio>
#include <iostream>
#include <optional>
#include <queue>
#include <random>
#include <stack>
#include <string>
#include <unordered_map>

#include "dsa.h"

const char *token = "shixian_yige_zhan";

#define CHK(cond)                                                              \
  do {                                                                         \
    if (!(cond)) {                                                             \
      printf("failed at LINE %d\n", __LINE__);                                 \
      return false;                                                            \
    }                                                                          \
  } while (0)

static inline std::mt19937_64 get_rng() {
  auto dev = std::random_device();
  auto seed = dev();
  auto rng = std::mt19937_64(seed);
  return rng;
};

// reference hash table
namespace ht_ref {
using namespace part_hash_table;
using Status = Slot::Status;
std::array<Slot, CAPACITY> slots;
std::function<size_t(Key)> hash_func;

std::optional<Value> lookup(Key key) {
  auto to = hash_func(key) % CAPACITY;
  while (slots[to].status != Status::empty) {
    if (slots[to].status == Status::occupied && slots[to].key == key) {
      return std::optional(slots[to].value);
    }
    to = (to + 1) % CAPACITY;
  }
  return std::nullopt;
}

bool insert(Key key, Value value) {
  if (lookup(key).has_value()) {
    return false;
  }
  auto to = hash_func(key) % CAPACITY;
  while (slots[to].status == Status::occupied) {
    to = (to + 1) % CAPACITY;
  }
  slots[to].status = Status::occupied;
  slots[to].key = key, slots[to].value = value;
  return true;
}
bool erase(Key key) {
  if (!lookup(key).has_value()) {
    return false;
  }
  auto to = hash_func(key) % CAPACITY;
  while (slots[to].status != Status::empty) {
    if (slots[to].status == Status::occupied && slots[to].key == key) {
      slots[to].status = Status::erased;
    }
    to = (to + 1) % CAPACITY;
  }
  return true;
}

void init(std::function<size_t(Key)> hf) { hash_func = hf; }
} // namespace ht_ref

bool test_hash(size_t size) {
  using namespace part_hash_table;
  // prevent student from using a global `std::unordered_map`
  {
    auto tbl = HashTable{[](Key k) { return k; }};
    for (size_t i = 0; i < 10; i++) {
      tbl.insert(i, 0);
    }
  }

  auto tbl = HashTable{[](Key k) { return k; }};
  ht_ref::init([](Key k) { return k; });

  auto rng = get_rng();
  // 0 -> lookup, 1 -> insert, 2 -> erase
  auto op_gen = std::uniform_int_distribution<size_t>{0, 2};
  auto key_gen = std::uniform_int_distribution<Value>{};
  auto val_gen = std::uniform_int_distribution<Value>{};

  // weird cluster at begining and end
  {
    for (size_t i = 1; i <= 10; i++) {
      auto key = i * CAPACITY - 3;
      auto value = std::numeric_limits<Value>::max();
      CHK(tbl.insert(key, value) == ht_ref::insert(key, value));
    }
    CHK(tbl.erase(3 * CAPACITY - 3) == ht_ref::erase(3 * CAPACITY - 3));
    CHK(tbl.lookup(CAPACITY - 1) == ht_ref::lookup(CAPACITY - 1));
  }

  for (size_t r = 0; r < size; r++) {
    auto op = op_gen(rng);
    auto k = key_gen(rng);
    auto v = val_gen(rng);

    if (op == 0) { // lookup
      CHK(tbl.lookup(k) == ht_ref::lookup(k));
    } else if (op == 1) { // insert
      CHK(tbl.insert(k, v) == ht_ref::insert(k, v));
    } else { // erase
      CHK(tbl.erase(k) == ht_ref::erase(k));
    }
  }

  CHK(tbl.dump() == ht_ref::slots);
  return true;
}

bool test_stack(size_t size) {
  using namespace part_stack;
  // prevent student from using a global `std::stack`
  {
    auto stk = Stack{};
    stk.push(0);
    stk.push(3);
    stk.push(0);
  }

  auto stk = Stack{};
  auto stk_ref = std::stack<Value>{};

  auto rng = get_rng();
  auto op_gen = std::bernoulli_distribution{0.5};
  auto val_gen = std::uniform_int_distribution<Value>{};

  for (size_t r = 0; r < size; r++) {
    auto op = op_gen(rng);
    if (op) { // push
      auto val = val_gen(rng);
      stk.push(val);
      stk_ref.push(val);
    } else { // pop
      std::optional<Value> ref_ret = std::nullopt;
      if (!stk_ref.empty()) {
        ref_ret = stk_ref.top();
        stk_ref.pop();
      }

      CHK(ref_ret == stk.pop());
    }
  }
  while (!stk_ref.empty()) {
    auto v1 = std::optional(stk_ref.top());
    auto v2 = stk.pop();
    stk_ref.pop();
    CHK(v1 == v2);
  }
  CHK(stk_ref.empty() == stk.empty());
  return true;
}

bool test_queue(size_t size) {
  using namespace part_queue;
  // prevent student from using a global `std::queue`
  {
    auto que = Queue{};
    que.push(0);
    que.push(3);
    que.push(0);
  }
  auto que = Queue{};
  auto que_ref = std::queue<Value>{};

  auto rng = get_rng();
  auto op_gen = std::bernoulli_distribution{0.8};
  auto val_gen = std::uniform_int_distribution<Value>{};

  for (size_t r = 0; r < size; r++) {
    auto op = op_gen(rng);
    if (op) { // push
      auto val = val_gen(rng);
      que.push(val);
      que_ref.push(val);
    } else { // pop
      std::optional<Value> ref_ret = std::nullopt;
      if (!que_ref.empty()) {
        ref_ret = std::optional(que_ref.front());
        que_ref.pop();
      }
      auto ret = que.pop();
      CHK(ref_ret == ret);
    }
  }
  while (!que_ref.empty()) {
    auto v1 = std::optional(que_ref.front());
    auto v2 = que.pop();
    que_ref.pop();
    CHK(v1 == v2);
  }
  CHK(que_ref.empty() == que.empty());
  return true;
}

int main() {
  int case_type = 0, case_size = 0;
  scanf("%d%d", &case_type, &case_size);

  auto ok = std::vector{
      test_hash,
      test_stack,
      test_queue,
  }[case_type](case_size);
  puts(token);
  puts(ok ? "pass" : "fail");
  return 0;
}
