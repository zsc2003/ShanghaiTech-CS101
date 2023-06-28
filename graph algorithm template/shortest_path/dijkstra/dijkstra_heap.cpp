#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>  // std::numeric_limits
#include <queue>   // std::priority_queue
#include <utility> // std::pair
#include <vector>

using dist_t = long long;

constexpr int maxn = 1e5 + 7;
constexpr auto inf = std::numeric_limits<dist_t>::max();

std::vector<std::pair<int, int>> G[maxn];
int n, m;

inline void add_edge(int from, int to, int weight) {
  G[from].emplace_back(to, weight);
}

dist_t dist[maxn];

void dijkstra(int s) {
  std::fill_n(dist + 1, n, inf);
  dist[s] = 0;
  std::priority_queue<std::pair<dist_t, int>> heap; // (-dist[x], x)
  heap.emplace(0, s);
  while (!heap.empty()) {
    auto [d, x] = heap.top();
    heap.pop();
    d = -d;
    if (d != dist[x]) {
      assert(d > dist[x]);
      continue;
    }
    for (auto [v, w] : G[x])
      if (dist[x] + w < dist[v]) {
        dist[v] = dist[x] + w;
        heap.emplace(-dist[v], v);
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