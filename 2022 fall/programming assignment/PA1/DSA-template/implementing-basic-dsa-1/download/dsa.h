#pragma once

#include <array>
#include <cstddef>
#include <functional>
#include <limits>
#include <optional>

namespace part_hash_table {
const size_t CAPACITY = 100000;
using Key = size_t;
using Value = size_t;

// a slot in the hash table: at any given time, a slot must be in exactly one of
// three following status
// - empty
// - occupied by a key-value pair
// - marked as erased
//
// the state transition looks something like this: (current_state, action,
// next_state)
// - (empty, insert, occupied)
// - (erased, insert, occupied)
// - (occupied, erase, erased)
// (initialize) empty -> occupied -> erased -> occupied -> ...
struct Slot {
  enum class Status {
    empty,
    occupied,
    erased,
  } status;
  Key key;
  Value value;
  Slot() : status(Status::empty), key(), value() {}
  bool operator==(const Slot &s0) const {
    return status == s0.status && key == s0.key && value == s0.value;
  }
};

// a linear-probing hash table with lazy erasure strategy
class HashTable {
public:
  // construct an empty hash hash table
  // where the hash function is `hash_func`
  HashTable(std::function<size_t(Key)> hash_func);

  // dump the hash table slots
  // for correctness checking
  std::array<Slot, CAPACITY> dump() const;

  // insert a key-value pair.
  // if the key already presents in the table, do nothing and return `false`
  // otherwise place the key-value pair in a slot and return `true`.
  // it is guaranteed that the table is never full.
  bool insert(Key key, Value value);

  // find the value corresponds to the given key,
  // if the key does not appear in the table, `std::nullopt` should be returned,
  // otherwise give a non-empty option with the corresponding value in it.
  std::optional<Value> lookup(Key key) const;

  // erase the key-value pair where the key matches the parameter
  // if such pair does not exists, do nothing and return `false`,
  // otherwise, return `true` and delete the key-value pair in slots.
  bool erase(Key key);

private:
  // the hash function used to map keys,
  // it is not guaranteed that the return value of `hash_func` will fall in
  // range [0,CAPACITY-1]
  std::function<size_t(Key)> hash_func;
  // the slots used to store the key-value pairs in the hash table
  std::array<Slot, CAPACITY> slots;
};
} // namespace part_hash_table

namespace part_stack {
const size_t CAPACITY = 100000;
using Value = size_t;

// a stack built on a fixed-size array
class Stack {
public:
  // create an empty stack
  Stack();

  // check if the stack is empty
  bool empty() const;

  // push a new value onto the stack top.
  // it is guaranteed that the stack is never full.
  void push(Value value);

  // try to pop the element at the stack top,
  // do nothing and return `std::nullopt` if the stack is empty,
  // otherwise remove the element at stack top and return an `std::optional`
  // object with it.
  std::optional<Value> pop();

private:
  std::array<Value, CAPACITY> data;
  size_t stack_top;
};
} // namespace part_stack

namespace part_queue {
const size_t CAPACITY = 100000;
using Value = size_t;

// a queue built on a fixed-size ring-buffer
class Queue {
public:
  // create an empty queue
  Queue();

  // check if the queue is empty
  bool empty() const;

  // push a new value behind the queue tail.
  // it is guaranteed that the queue is never full.
  void push(Value value);

  // try to pop the element at the queue head,
  // do nothing and return `std::nullopt` if the queue is empty,
  // otherwise remove the element at queue head and return an `std::optional`
  // wrapping it.
  std::optional<Value> pop();

private:
  std::array<Value, CAPACITY> data;
  size_t head, tail;
};
} // namespace part_queue
