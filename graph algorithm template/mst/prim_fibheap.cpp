#include <boost/heap/fibonacci_heap.hpp>
#include <cassert>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

constexpr int maxn = 1e5 + 7;
constexpr int inf = std::numeric_limits<int>::max();

std::vector<std::pair<int, int>> G[maxn];
int n, m;

inline void add_edge(int from, int to, int weight) {
  G[from].emplace_back(to, weight);
}

using fib_heap = boost::heap::fibonacci_heap<std::pair<int, int>>;

int dist[maxn];
fib_heap::handle_type handles[maxn];

long long prim(int start) {
  fib_heap heap;
  for (auto i = 1; i <= n; ++i)
    dist[i] = inf;
  dist[start] = 0;
  for (auto i = 1; i <= n; ++i)
    handles[i] = heap.emplace(-dist[i], i);
  auto mst_weight = 0ll;
  while (!heap.empty()) {
    auto [w, x] = heap.top();
    heap.pop();
    w = -w;
    assert(w == dist[x]);
    mst_weight += w;
    dist[x] = -inf;
    for (auto &&[v, weight] : G[x])
      if (weight < dist[v]) {
        dist[v] = weight;
        heap.increase(handles[v], std::pair{-dist[v], v});
      }
  }
  return mst_weight;
}

int main() {
  std::cin >> n >> m;
  for (auto i = 0; i != m; ++i) {
    int x, y, z;
    std::cin >> x >> y >> z;
    add_edge(x, y, z);
    add_edge(y, x, z);
  }
  std::cout << prim(1) << std::endl;
  return 0;
}