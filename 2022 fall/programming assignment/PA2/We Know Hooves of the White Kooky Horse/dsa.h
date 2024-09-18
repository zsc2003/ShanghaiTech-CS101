#pragma once

#include <cstdint>      // for `std::size_t` and `std::uint32_t`
#include <forward_list> // for `std::forward_list` and its iterator type

// list sorting namespace
// **OJ**:  marks functions that are implemented by the OJ judger
// **YOU**: marks functions that are implemented by you
namespace lsort {
using Key = std::uint32_t;
using List = std::forward_list<Key>;
using Iter = List::iterator;
using ConstIter = List::const_iterator;

// **OJ**: Count the number of elements in a list.
//
// parameters:
// - `la` reference to a list.
//
// return:
// - `size` of type `size_t`, the number of elements in the given list.
std::size_t list_size(const List &la);

// **OJ**: Generate a random index in range [0,n-1]
//
// parameters:
// - `n` the index upperbound
//
// return:
// - `idx` of type `size_t`, a random valid index.
std::size_t random_index(const std::size_t n);

// **YOU**: merge two sorted list `la` and `lb`, put the result in `out` list
// after `merge(la,lb,out)`, `la` and `lb` should be empty while `out` contains
// all the elements previously in `la` and `lb`.
//
// parameters:
// - `la` reference to a list, one of the sorted list.
// - `lb` reference to a list, one of the sorted list.
// - `out` reference to a list, the merged list.
//    Should contain all the elements in `la` and `lb` in ascending order.
//
// return: No return value
void merge(const List &la, const List &lb, List &out);

// **YOU**: partition a list, `leq` contains the elements less or equal to
// `pivot` and `gt` contains the elements greater than `pivot`.
//
// the sum of sizes`leq` and `gt` should be equal to size of `la`.
//
// parameters:
// - `la` the list to be partitioned.
// - `leq` an output list. The elements leq to `pivot` in `la` gose into `leq`.
// - `gt`  an output list. The elements gt  to `pivot` in `la` gose into `gt`.
//
// return: No return value
void partition(const List &la, List &leq, List &gt, Key pivot);

// **YOU**: pick a random pivot from a list
//
// parameters:
// `la` a non-empty list
// return:
// `pivot` of type `Key`, a random value from the list
Key select_pivot(const List &la);

// **OJ**: merge sort procedure, with `lsort::merge`
void merge_sort(List &list_to_sort);
// **OJ**: quick sort procedure, with `lsort::partition` and
// `lsort::select_pivot`
void quick_sort(List &list_to_sort);

} // namespace lsort
