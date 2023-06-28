#include <queue>
#include <utility>
#include <vector>

constexpr int maxn = 1e5 + 7;

std::vector<int> G[maxn];
int n, m;

inline void add_edge(int from, int to) {
  G[from].push_back(to);
}

bool vis[maxn];

void dfs(int x) {
  vis[x] = true;
  for (auto v : G[x])
    if (!vis[v]) {
      dfs(v);
    }
}

void bfs(int s) {
  std::queue<int> q;
  q.push(s);
  vis[s] = true;
  while (!q.empty()) {
    auto x = q.front();
    q.pop();
    for (auto v : G[x])
      if (!vis[v]) {
        vis[v] = true;
        q.push(v);
      }
  }
}