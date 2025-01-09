#include <algorithm>
#include <cstdio>
#include <iostream>
#include <vector>

using std::vector;

int n, W, k;  // n: number of equipment, W: capacity, k: mission number
struct eqp {
    int l, w, v;  // l: limit, w: weight, v: value
    eqp(int _l, int _w, int _v)
        : l(_l), w(_w), v(_v) {}
};
vector<eqp> equipment;

/*
You can share a public variable(function) sets since only 1 mission will be executed once.
*/

// MISSION1: all equipment with l = -1
int Mission1() {
    int ans = 0;
    // TODO: Finish Mission 1.

    return ans;
}

// MISSION2: all equipment with l = 1
int Mission2() {
    int ans = 0;
    // TODO: Finish Mission 2.

    return ans;
}

// MISSION3: Liquid tanks: Can bring any fractional unit of liquid, w|v
int Mission3() {
    int ans = 0;
    // TODO: Finish Mission 3.

    return ans;
}

// Input Part, you can modify this.
void getInput() {
    scanf("%d%d%d", &k, &n, &W);
    for (int i = 1; i <= n; ++i) {
        int l, w, v;
        scanf("%d%d%d", &l, &w, &v);
        equipment.emplace_back(l, w, v);
    }
}

// You'd better not to modify things below.
int (*MISSION_FUNC[])() = {nullptr, Mission1, Mission2, Mission3};

int main() {
    getInput();
    int ans = MISSION_FUNC[k]();
    std::cout << ans;
    return 0;
}