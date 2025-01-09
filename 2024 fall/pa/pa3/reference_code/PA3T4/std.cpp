#include <cstdio>
#include <iostream>

inline int read() {
    int r, s = 0, c;
    for (; !isdigit(c = getchar()); s = c)
        ;
    for (r = c ^ 48; isdigit(c = getchar()); (r *= 10) += c ^ 48)
        ;
    return s ^ 45 ? r : -r;
}

const int N = 100010;
const int mod = 1e9 + 7;
int dp[N][10];
bool modulo[N][10];
char ans[N];

void calc(int sum, int k, int digit) {
    int tot = dp[1][digit];
    if (modulo[1][digit])
        tot += mod;
    if (sum > tot || sum <= 0) {
        puts("-1");
        return;
    }

    ans[k + 1] = '\0';
    for (int i = 1; i <= k; ++i) {
        ans[i] = digit + '0';
        if (digit == 0)
            digit = 1;
        else if (digit == 9)
            digit = 8;
        else {
            tot = dp[i + 1][digit - 1];
            if (modulo[i + 1][digit - 1])
                tot += mod;
            if (tot >= sum)
                --digit;
            else {
                sum -= dp[i + 1][digit - 1];
                ++digit;
            }
        }
    }
    puts(ans + 1);
    return;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("continuous.in", "r", stdin);
    freopen("t4_zsc.out", "w", stdout);
#endif

    int s = read(), t = read(), k = read(), m = read();
    dp[k][t] = 1;
    for (int i = k - 1; i >= 1; --i) {
        dp[i][0] = dp[i + 1][1];
        modulo[i][0] = modulo[i + 1][1];

        for (int j = 1; j <= 8; ++j) {
            dp[i][j] = dp[i + 1][j - 1] + dp[i + 1][j + 1];
            if (dp[i][j] >= mod) {
                dp[i][j] -= mod;
                modulo[i][j] = 1;
            }
            modulo[i][j] |= modulo[i + 1][j - 1] | modulo[i + 1][j + 1];
        }

        dp[i][9] = dp[i + 1][8];
        modulo[i][9] = modulo[i + 1][8];
    }

    // for(int i=1;i<=k;++i){for(int j=0;j<=9;++j)std::cout<<dp[i][j]<<' ';std::cout<<'\n';}

    std::cout << dp[1][s] << '\n';
    while (m--) {
        int x = read();
        calc(x, k, s);
    }

    return 0;
}