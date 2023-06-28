#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>  // std::numeric_limits
#include <utility> // std::pair
#include <vector>
#include <boost/heap/fibonacci_heap.hpp>

using dist_t = long long;

constexpr int maxn = 1e5 + 7;
constexpr auto inf = std::numeric_limits<dist_t>::max();

std::vector<std::pair<int, int>> G[maxn];
int n, m;

inline void add_edge(int from, int to, int weight) {
  G[from].emplace_back(to, weight);
}

using fib_heap = boost::heap::fibonacci_heap<std::pair<dist_t, int>>; // (-dist[x], x)

fib_heap::handle_type handles[maxn];
dist_t dist[maxn];

void dijkstra(int s) {
  std::fill_n(dist + 1, n, inf);
  dist[s] = 0;
  fib_heap heap;
  for (auto i = 1; i <= n; ++i)
    handles[i] = heap.emplace(-dist[i], i);
  while (!heap.empty()) {
    auto [d, x] = heap.top();
    heap.pop();
    d = -d;
    assert(d == dist[x]);
    for (auto [v, w] : G[x])
      if (dist[x] + w < dist[v]) {
        dist[v] = dist[x] + w;
        heap.increase(handles[v], std::pair{-dist[v], v});
      }
  }
}

int main() {
  std::cin >> n >> m;
  for (auto i = 0; i != m; ++i) {
    int x, y, z;
    std::cin >> x >> y >> z;
    add_edge(x, y, z);
    add_edge(y, x, z);
  }
  int s;
  std::cin >> s;
  dijkstra(s);
  for (auto i = 1; i <= n; ++i)
    std::cout << dist[i] << ' ';
  std::cout << std::endl;
  return 0;
}