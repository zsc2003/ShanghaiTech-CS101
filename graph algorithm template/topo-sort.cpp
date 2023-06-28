#include <iostream>
#include <queue>
#include <vector>

constexpr int maxn = 1e5 + 7;

std::vector<int> G[maxn];
int n, m;
int indegree[maxn];

inline void add_edge(int from, int to) {
  G[from].emplace_back(to);
}

int main() {
  std::cin >> n >> m;
  for (auto i = 0; i != m; ++i) {
    int x, y;
    std::cin >> x >> y;
    add_edge(x, y);
    ++indegree[y];
  }
  std::queue<int> q;
  for (auto i = 1; i <= n; ++i)
    if (!indegree[i])
      q.push(i);
  while (!q.empty()) {
    auto x = q.front();
    q.pop();
    std::cout << x << ' ';
    for (auto v : G[x])
      if (!--indegree[v])
        q.push(v);
  }
  std::cout << std::endl;
  return 0;
}