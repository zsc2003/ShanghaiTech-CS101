#include <algorithm>
#include <functional>
#include <iostream>
const int N = 2e5 + 9;
int n, k;
int a[N], b[N], w[N];

int main() {
#ifndef ONLINE_JUDGE
    freopen("difficulty.in", "r", stdin);
    freopen("std_flash.out", "w", stdout);
#endif
    std::cin >> n >> k;
    for (int i = 1; i <= n; ++i)
        std::cin >> a[i];
    for (int i = 1; i <= n; ++i)
        std::cin >> b[i];
    for (int i = 1; i + k <= n + 1; ++i) {
        ++w[i];
        --w[i + k];
    }
    for (int i = 1; i <= n; ++i) {
        w[i] += w[i - 1];
        a[i] *= w[i];
    }
    std::sort(a + 1, a + n + 1);
    std::sort(b + 1, b + n + 1, std::greater<int>());
    long long ans = 0;
    for (int i = 1; i <= n; ++i)
        ans += (long long)a[i] * b[i];
    std::cout << ans << std::endl;
    return 0;
}