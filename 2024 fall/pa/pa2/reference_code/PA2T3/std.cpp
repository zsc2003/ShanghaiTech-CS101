#include <climits>
#include <iostream>
#include <tuple>
const int N = 1e6 + 9;
int v[N], p[N];
std::tuple<bool, int, int> IsPostOrd(int l, int r) {
    bool ok = true;
    int minv = INT_MAX, maxv = INT_MIN;
    if (l == r) {
        minv = maxv = v[l];
    } else if (l < r) {
        int k = l, kr = r - 1;
        while (true) {
            if (v[k] > v[r])
                break;
            else if (v[kr] < v[r]) {
                k = kr + 1;
                break;
            }
            ++k;
            --kr;
        }
        if (l <= k - 1)
            p[k - 1] = r;
        if (k <= r - 1)
            p[r - 1] = r;
        auto [lok, lminv, lmaxv] = IsPostOrd(l, k - 1);
        auto [rok, rminv, rmaxv] = IsPostOrd(k, r - 1);
        ok = lok and rok and lmaxv < v[r] and rminv > v[r];
        minv = std::min(v[r], std::min(lminv, rminv));
        maxv = std::max(v[r], std::max(lmaxv, rmaxv));
        // for (int i = l; i <= r; ++i)
        //     std::cerr << v[i] << ' ';
        // std::cerr << "ok=" << ok << ' ' << lmaxv << ' ' << rminv << std::endl;
    }
    return {ok, minv, maxv};
}
int main() {
#ifndef ONLINE_JUDGE
    freopen("in.in", "r", stdin);
    freopen("divide_leftright.out", "w", stdout);
#endif
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; ++i)
        std::cin >> v[i];
    auto [ok, minv, maxv] = IsPostOrd(1, n);
    if (ok) {
        for (int i = 1; i <= n - 1; ++i)
            std::cout << p[i] << ' ';
        std::cout << std::endl;
    } else
        std::cout << "Not exist" << std::endl;
}