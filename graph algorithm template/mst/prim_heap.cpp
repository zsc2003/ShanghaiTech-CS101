#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

constexpr int maxn = 1e5 + 7;
constexpr int inf = std::numeric_limits<int>::max();

std::vector<std::pair<int, int>> G[maxn];
int n, m;

inline void add_edge(int from, int to, int weight) {
  G[from].emplace_back(to, weight);
}

int dist[maxn];

long long prim(int start) {
  std::priority_queue<std::pair<int, int>> heap; // (-dist[x], x)
  for (auto i = 1; i <= n; ++i)
    dist[i] = inf;
  dist[start] = 0;
  heap.emplace(-dist[start], start);
  auto mst_weight = 0ll;
  while (!heap.empty()) {
    auto [w, x] = heap.top();
    heap.pop();
    w = -w;
    if (w != dist[x])
      continue;
    mst_weight += w;
    // We mark x as covered by setting dist[x] to -inf, so that it won't be
    // pushed into the heap anymore.
    dist[x] = -inf;
    for (auto &&[v, weight] : G[x])
      if (weight < dist[v]) {
        dist[v] = weight;
        heap.emplace(-dist[v], v);
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