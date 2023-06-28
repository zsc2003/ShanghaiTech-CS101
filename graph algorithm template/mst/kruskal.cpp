#include <algorithm>
#include <iostream>
#include <vector>

constexpr int maxn = 1e5 + 7;

int fa[maxn], height[maxn];

struct Edge {
  int from, to, weight;
};

std::vector<Edge> edges;
int n, m;

inline void init() {
  for (auto i = 1; i <= n; ++i) {
    fa[i] = i;
    height[i] = 1;
  }
}

int findfa(int x) {
  return fa[x] == x ? x : fa[x] = findfa(fa[x]);
}

void merge(int x, int y) {
  x = findfa(x);
  y = findfa(y);
  if (x == y)
    return;
  if (height[x] < height[y])
    fa[x] = y;
  else if (height[y] < height[x])
    fa[y] = x;
  else { // height[x] == height[y]
    fa[x] = y;
    ++height[y];
  }
}

int main() {
  std::cin >> n >> m;
  for (auto i = 0; i != m; ++i) {
    int x, y, z;
    std::cin >> x >> y >> z;
    edges.push_back({.from = x, .to = y, .weight = z});
  }
  // C++20: std::ranges::sort(edges, {}, &Edge::weight);
  std::sort(edges.begin(), edges.end(),
            [](const auto &a, const auto &b) { return a.weight < b.weight; });
  init();
  long long mst_weight = 0;
  for (auto &&[u, v, w] : edges) {
    if (findfa(u) != findfa(v)) {
      mst_weight += w;
      merge(u, v);
    }
  }
  std::cout << mst_weight << std::endl;
  return 0;
}