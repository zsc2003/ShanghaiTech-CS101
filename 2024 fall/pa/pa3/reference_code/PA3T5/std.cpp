#include <algorithm>
#include <cstdio>
#include <vector>

using std::vector;

int n, W, k;
struct eqp {
    int l, w, v;
    eqp(int N, int W, int V)
        : l(N), w(W), v(V) {}
};
vector<eqp> equipment;

/*
You can share a public variable(function) sets since only 1 mission will be executed once.
*/

bool cmp(const eqp& e1, const eqp& e2) {
    return (long long)e1.v * e2.w > (long long)e1.w * e2.v;
}

// MISSION1: all equipment with l = -1
int Mission1() {
    int ans;
    // TODO: Finish Mission 1.
    using std::max;
    vector<eqp> eq1, eq2;
    for (auto eq : equipment) {
        if (eq.l == -1) {
            eq1.push_back(eq);
            continue;
        }
        for (int k = 1; k < eq.l; k *= 2) {
            eq2.push_back(eqp(k, eq.w, eq.v));
            eq.l -= k;
        }
        if (eq.l > 0) {
            eq2.push_back(eq);
        }
    }
    vector<long long> f(W + 1, 0);
    for (auto eq : eq1) {
        for (int j = eq.w; j <= W; j++) {
            f[j] = max(f[j], (f[j - eq.w] + eq.v));
        }
    }
    for (auto eq : eq2) {
        for (int j = W; j >= eq.w; j--) {
            f[j] = max(f[j], (f[j - eq.w] + eq.v));
        }
    }
    ans = 0;
    for (int i = 0; i <= W; i++) {
        ans = max(ans, (int)f[i]);
    }
    return ans;
}

// MISSION2: all equipment with l = 1
int Mission2() {
    int ans;
    // TODO: Finish Mission 2.
    using std::max;
    vector<long long> f(W + 1, 0);
    for (auto eq : equipment) {
        for (int j = W; j >= eq.w; j--) {
            f[j] = max(f[j], (f[j - eq.w] + eq.v));
        }
    }
    ans = 0;
    for (int i = 0; i <= W; i++) {
        ans = max(ans, (int)f[i]);
    }
    return ans;
}

// MISSION3: Liquid tanks: Can bring any fractional unit of liquid, w|v
int Mission3() {
    int ans;
    // TODO: Finish Mission 3.
    using std::min;
    using std::sort;
    sort(equipment.begin(), equipment.end(), cmp);
    int cc = W;
    ans = 0;
    for (auto eq : equipment) {
        long long ww = std::min(eq.w * eq.l, cc);
        if (ww < 0) {
            ww = cc;
        }
        ans = (ans + eq.v / eq.w * ww);
        cc -= ww;
        if (!cc) {
            break;
        }
    }
    return ans;
}

// Input Part, you can modify this.
void getInput() {
    scanf("%d%d%d", &k, &n, &W);
    for (int i = 1; i <= n; i++) {
        int N, W, V;
        scanf("%d%d%d", &N, &W, &V);
        equipment.emplace_back(N, W, V);
    }
}

// You'd better not to modify things below.

int (*MISSION_FUNC[])() = {nullptr, Mission1, Mission2, Mission3};

int main() {
#ifndef ONLINE_JUDGE
    freopen("starcraft.in", "r", stdin);
    freopen("T5_zulk.out", "w", stdout);
#endif

    getInput();
    int ans = MISSION_FUNC[k]();
    printf("%d", ans);
    return 0;
}
