constexpr int maxn = 1e5 + 7;

int fa[maxn], height[maxn];
int n;

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
  else /* height[x] == height[y] */
  {
    fa[x] = y;
    ++height[y];
  }
}

inline void init() {
  for (auto i = 1; i <= n; ++i) {
    fa[i] = i;
    height[i] = 1;
  }
}