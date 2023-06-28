#include <algorithm>
#include <cassert>
#include <iostream>
#include <limits>  // std::numeric_limits
#include <utility> // std::pair
#include <vector>
#include <queue>

using dist_t = long long;

constexpr int maxn = 1e5 + 7;
constexpr auto inf = std::numeric_limits<dist_t>::max();

std::vector<std::pair<int, int>> G[maxn];
int n, m;

inline void add_edge(int from, int to, int weight) {
  G[from].emplace_back(to, weight);
}

dist_t dist[maxn];

void spfa(int s) {
  for (auto i = 1; i <= n; ++i)
    dist[i] = inf;
  dist[s] = 0;
  std::queue<int> q;
  q.push(s);
  while (!q.empty()) {
    auto x = q.front();
    q.pop();
    for (auto [v, w] : G[x])
      if (dist[x] + w < dist[v]) {
        dist[v] = dist[x] + w;
        q.emplace(v);
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
  spfa(s);
  for (auto i = 1; i <= n; ++i)
    std::cout << dist[i] << ' ';
  std::cout << std::endl;
  return 0;
}