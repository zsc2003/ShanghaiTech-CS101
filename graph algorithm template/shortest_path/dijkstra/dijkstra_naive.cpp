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
bool done[maxn];

void relax(int x) {
  for (auto [v, w] : G[x])
    if (!done[v] && dist[x] + w < dist[v])
      dist[v] = dist[x] + w;
}

void dijkstra(int s) {
  std::fill_n(dist + 1, n, inf);
  std::fill_n(done + 1, n, false);
  dist[s] = 0;
  done[s] = true;
  relax(s);
  for (auto cnt = 1; cnt < n; ++cnt) {
    auto x = 0;
    auto min_dist = inf;
    for (auto i = 1; i <= n; ++i)
      if (!done[i] && dist[i] < min_dist) {
        x = i;
        min_dist = dist[i];
      }
    assert(x != 0);
    done[x] = true;
    relax(x);
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