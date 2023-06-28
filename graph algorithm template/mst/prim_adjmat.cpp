#include <cassert>
#include <iostream>
#include <limits>

constexpr int maxn = 5007;
constexpr int inf = std::numeric_limits<int>::max();

bool adj[maxn][maxn];
int weight[maxn][maxn];
int n, m;

int dist[maxn];
bool covered[maxn];

long long prim(int start) {
  for (auto i = 1; i <= n; ++i)
    if (adj[i][start])
      dist[i] = weight[i][start];
    else
      dist[i] = inf;
  dist[start] = 0;
  covered[start] = true;
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
    for (auto i = 1; i <= n; ++i)
      if (adj[i][next] && !covered[i] && weight[i][next] < dist[i])
        dist[i] = weight[i][next];
  }
  return mst_weight;
}

int main() {
  std::cin >> n >> m;
  for (auto i = 0; i != m; ++i) {
    int x, y, z;
    std::cin >> x >> y >> z;
    adj[x][y] = adj[y][x] = true;
    weight[x][y] = weight[y][x] = z;
  }
  std::cout << prim(1) << std::endl;
  return 0;
}