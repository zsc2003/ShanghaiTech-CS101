#include <iostream>
#include <limits>

constexpr int maxn = 2007;

using dist_t = long long;

// Be careful! Setting `inf` too large may result in integer overflow, which is
// undefined behavior.
constexpr auto inf = std::numeric_limits<dist_t>::max() / 3;

dist_t dist[maxn][maxn];
int n;

void floyd_warshall() {
  // dist[i][i] == 0
  // dist[i][j] == inf if i and j are not adjacent.
  for (auto k = 1; k <= n; ++k)
    for (auto i = 1; i <= n; ++i)
      for (auto j = 1; j <= n; ++j)
        if (dist[i][k] + dist[k][j] < dist[i][j])
          dist[i][j] = dist[i][k] + dist[k][j];
}