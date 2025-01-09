#include <bits/stdc++.h>
using namespace std;
const int N = 200005, INF = 0x3f3f3f3f;
int n, p[N], st[N], top;
struct node {
    int x, y, p;
    bool operator < (const node &a)const {
        return x < a.x;
    }
} a[N], b[N];
long long ans;
void solve(int l, int r) {
    if (l == r)
        return;

    int mid = (l + r) / 2;
    solve(l, mid), solve(mid + 1, r);
    int i = l, j = mid + 1;
    top = 0;

    for (int k = l; k <= r; k++) {
        if (j > r || (i <= mid && a[i].y < a[j].y)) {
            while (top && a[i].x > a[st[top]].x)
                top--;

            st[++top] = i;
            b[k] = a[i++];
        } else {
            int L = 1, R = top, Mid, res = 0;

            while (L <= R) {
                Mid = (L + R) / 2;

                if (a[st[Mid]].y >= a[j].p)
                    res = top - Mid + 1, R = Mid - 1;
                else
                    L = Mid + 1;
            }

            ans += res;

            if (res)
                a[j].p = a[st[top]].y;

            b[k] = a[j++];
        }
    }

    for (int k = l; k <= r; k++)
        a[k] = b[k];
}
int main() {
    scanf("%d", &n);

    for (int i = 1; i <= n; i++)
        scanf("%d %d", &a[i].x, &a[i].y);

    sort(a + 1, a + 1 + n);
    solve(1, n);
    printf("%lld", ans);
    return 0;
}