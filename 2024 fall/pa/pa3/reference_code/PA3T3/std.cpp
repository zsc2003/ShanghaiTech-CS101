#include <cstdio>
#include <iostream>
#include <queue>

inline int read() {
    int r, s = 0, c;
    for (; !isdigit(c = getchar()); s = c)
        ;
    for (r = c ^ 48; isdigit(c = getchar()); (r *= 10) += c ^ 48)
        ;
    return s ^ 45 ? r : -r;
}

const int N = 1000010;
const long long inf = 1e18;

struct edge {
    int to, next;
    long long val, start_time, duration;
} mem[N];
int head[N], cnt;
inline void add(int u, int v, long long val, long long start_time, long long duration) {
    mem[++cnt].next = head[u];
    mem[cnt].to = v;
    mem[cnt].val = val;
    mem[cnt].start_time = start_time;
    mem[cnt].duration = duration;
    head[u] = cnt;
}

int a[N];

struct node {
    int u;
    long long val;
    friend bool operator<(const node& a, const node& b) {
        return a.val > b.val;
    }
} f;

long long d[N];
bool vis[N];

void dijkstra(int n, int s, long long t0) {
    for (int i = 1; i <= n; ++i)
        d[i] = inf;
    std::priority_queue<node> q{};
    q.push({s, t0});
    d[s] = t0;

    while (!q.empty()) {
        f = q.top();
        q.pop();
        if (vis[f.u])
            continue;
        vis[f.u] = 1;

        for (int e = head[f.u]; e != 0; e = mem[e].next) {
            long long earlist_start_time = mem[e].start_time;
            if (earlist_start_time < d[f.u]) {
                long long times = (d[f.u] - earlist_start_time) / mem[e].duration;
                if ((d[f.u] - earlist_start_time) % mem[e].duration != 0)
                    ++times;
                earlist_start_time += times * mem[e].duration;
            }

            int to = mem[e].to;
            if (d[to] > earlist_start_time + mem[e].val) {
                d[to] = earlist_start_time + mem[e].val;
                q.push({to, d[to]});
            }
        }
    }

    return;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("bus.in", "r", stdin);
    freopen("bus_zsc.out", "w", stdout);
#endif
    int n = read(), m = read();
    long long t0 = read();
    int s = read(), t = read();
    while (m--) {
        int l = read();
        long long start_time = read(), duration = read();
        for (int i = 1; i <= l; ++i)
            a[i] = read();
        for (int i = 1; i < l; ++i) {
            long long val = read();
            add(a[i], a[i + 1], val, start_time, duration);
            start_time += val;
        }
    }

    dijkstra(n, s, t0);
    if (d[t] == inf)
        d[t] = -1;
    std::cout << d[t];

    return 0;
}