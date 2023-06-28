#include "dsa.h"
#include <functional>
#include <optional>

namespace part_queue {
Queue::Queue() : head(0), tail(0) {}
bool Queue::empty() const { return head >= tail; }
std::optional<Value> Queue::pop() {
  if (empty())
    return std::nullopt;
  return std::optional(data[head++]);
}
void Queue::push(Value value) { data[tail++] = value; }
} // namespace part_queue
namespace part_stack {
Stack::Stack() : stack_top(0) {}
bool Stack::empty() const { return stack_top == 0; }
std::optional<Value> Stack::pop() {
  if (empty())
    return std::nullopt;
  return std::optional(data[--stack_top]);
}
void Stack::push(Value value) { data[stack_top++] = value; }
} // namespace part_stack

namespace part_hash_table {
using Status = Slot::Status;
HashTable::HashTable(std::function<size_t(Key)> hash_func)
    : hash_func(hash_func), slots() {}

std::array<Slot, CAPACITY> HashTable::dump() const { return slots; }

bool HashTable::insert(Key key, Value value) {
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

std::optional<Value> HashTable::lookup(Key key) const {
  auto to = hash_func(key) % CAPACITY;
  while (slots[to].status != Status::empty) {
    if (slots[to].status == Status::occupied && slots[to].key == key) {
      return std::optional(slots[to].value);
    }
    to = (to + 1) % CAPACITY;
  }
  return std::nullopt;
}

bool HashTable::erase(Key key) {
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
} // namespace part_hash_table
