#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>  // std::numeric_limits
#include <utility> // std::pair
#include <vector>

using dist_t = long long;

constexpr int maxn = 5007;
constexpr auto inf = std::numeric_limits<dist_t>::max();

std::vector<std::pair<int, int>> G[maxn];
int n, m;

inline void add_edge(int from, int to, int weight) {
  G[from].emplace_back(to, weight);
}

dist_t dist[maxn];

void bellman_ford(int s) {
  for (auto i = 1; i <= n; ++i)
    dist[i] = inf;
  dist[s] = 0;
  for (auto i = 1; i <= n - 1; ++i) {
    for (auto v = 1; v <= n; ++v) {
      if (dist[v] < inf)
        for (auto [x, w] : G[v])
          dist[x] = std::min(dist[x], dist[v] + w);
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
  bellman_ford(s);
  for (auto i = 1; i <= n; ++i)
    std::cout << dist[i] << ' ';
  std::cout << std::endl;
  return 0;
}