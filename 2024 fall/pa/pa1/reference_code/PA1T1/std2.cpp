#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define N 10000005
using namespace std;
typedef long long ll;
typedef double db;
int n, m, p, tot;
ll ans[N];
void work(ll nn, ll mm)
{
    ll Next = (mm / n + 1) * n;
    int tmp;
    if (!nn)
        return;
    if (nn >= p)
    {
        ll ci = nn / p, now = 0;
        while (mm + ci >= Next)
        {
            ci -= Next - mm, now += (Next - mm) * p, mm = Next;
            ans[++tot] = now;
            Next = (mm / n + 1) * n;
        }
        mm += ci;
        now += ci * p;
        tmp = tot, work(nn - nn / p, mm);
        for (int i = tmp + 1; i <= tot; ++i)
        {
            if (ans[i] <= nn - now)
                ans[i] += now;
            else
                ans[i] -= (nn - now), ans[i] += (ans[i] - 1) / (p - 1);
        }
    }
    else
    {
        int x = p % nn;
        if (x == 0)
            x = nn;
        if (mm + 1 == Next)
            ans[++tot] = x;
        tmp = tot;
        work(nn - 1, mm + 1);
        for (int i = tmp + 1; i <= tot; ++i)
        {
            if (ans[i] <= nn - x)
                ans[i] += x;
            else
                ans[i] -= nn - x;
        }
    }
}
int main()
{
    scanf("%d%d%d", &n, &m, &p);
    p++;
    work((ll)n * m - 1, 1);
    for (int i = 1; i <= tot; ++i)
        ans[i]++;
    sort(ans + 1, ans + tot + 1);
    for (int i = 1; i <= tot; ++i)
        printf("%lld\n", ans[i]);
    return 0;
}