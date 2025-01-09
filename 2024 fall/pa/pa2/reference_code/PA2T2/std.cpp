#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using Node = std::pair<size_t, size_t>;

Node getMin(std::deque<Node>& p, std::deque<Node>& q) {
    Node ret;
    if (!p.empty() and (q.empty() or p.front().first < q.front().first)) {
        ret = p.front();
        p.pop_front();
    } else {
        ret = q.front();
        q.pop_front();
    }
    return ret;
}

size_t get_huffman_length(const std::vector<Node>& data) {
    std::deque<Node> p(data.begin(), data.end()), q;
    std::sort(p.begin(), p.end(),
              [](const Node& a, const Node& b) { return a.first < b.first; });
    size_t length = 0;
    while (true) {
        auto [f1, c1] = getMin(p, q);
        if (p.empty() and q.empty() and c1 == 1)
            return length;
        if (c1 > 1) {
            q.push_back({f1 * 2, c1 / 2});
            length += (f1 * 2) * (c1 / 2);
            if (c1 % 2 == 1)
                q.push_front({f1, 1});
        } else {
            auto [f2, c2] = getMin(p, q);
            q.push_back({f1 + f2, 1});
            length += f1 + f2;
            if (c2 > 1)
                q.push_front({f2, c2 - 1});
        }
    }
    return 0;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("akinator.in", "r", stdin);
    freopen("akinator.out", "w", stdout);
#endif
    int m, f, c;
    std::vector<Node> data;
    std::cin >> m;
    for (int i = 1; i <= m; ++i) {
        std::cin >> f >> c;
        data.push_back({f, c});
    }
    std::cout << get_huffman_length(data) << std::endl;
}