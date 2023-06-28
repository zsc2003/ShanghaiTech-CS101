#include <cassert>
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

constexpr int maxn = 5007;
constexpr int inf = std::numeric_limits<int>::max();

std::vector<std::pair<int, int>> G[maxn];
int n, m;

inline void add_edge(int from, int to, int weight) {
  G[from].emplace_back(to, weight);
}

int dist[maxn];
bool covered[maxn];

long long prim(int start) {
  for (auto i = 1; i <= n; ++i)
    dist[i] = inf;
  dist[start] = 0;
  covered[start] = true;
  for (auto &&[v, weight] : G[start])
    dist[v] = weight;
  auto cnt = 1;
  auto mst_weight = 0ll;
  while (cnt < n) {
    auto next = 0, w_min = inf;
    for (auto i = 1; i <= n; ++i)
      if (!covered[i] && dist[i] < w_min) {
        next = i;
        w_min = dist[i];
      }
    assert(next != 0);
    mst_weight += w_min;
    covered[next] = true;
    ++cnt;
    for (auto &&[v, weight] : G[next])
      if (!covered[v] && weight < dist[v])
        dist[v] = weight;
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