// #8C. Wireless is the New Fiber (optional)
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>

constexpr int kMaxNode = 100050;
constexpr int kMaxInt = 1000000009;

using LL = long long;

template <typename T>
void read(T& x) {
    x = 0;
    T f = 1;
    char ch = ' ';
    while (ch < '0' || ch > '9') {
        if (ch == '-')
            f = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x = x * f;
}

struct Node {
    int node_id, connect_number;
};
Node nodes[kMaxNode];

int main() {
    int n, m, a, b;
    read(n), read(m);
    if (m == n - 1) {  // 不需要调整
        printf("%d\n%d %d\n", 0, n, n - 1);
        for (int i = 0; i < m; ++i) read(a), read(b), printf("%d %d\n", a, b);
        return 0;
    }
    for (int i = 0; i < n; ++i) nodes[i].node_id = i;
    for (int i = 0; i < m; ++i) {
        read(a), read(b);
        ++nodes[a].connect_number;
        ++nodes[b].connect_number;
    }
    // 从 2m 个连接减为 2n-2 个连接，挑大的下手即可
    std::sort(nodes, nodes + n, [](Node a, Node b) { return a.connect_number > b.connect_number; });
    int res = 0;  // 要调整的节点数
    m = 2 * m - 2 * n + 2;
    while (m > nodes[res].connect_number - 1)
        m -= nodes[res].connect_number - 1, nodes[res++].connect_number = 1;
    nodes[res++].connect_number -= m, m = 0;
    printf("%d\n%d %d\n", res, n, n - 1);

    // 再排一次序，按升序排
    std::sort(nodes, nodes + n, [](Node a, Node b) { return a.connect_number < b.connect_number; });
    // 找一种连接方式
    for (int i = 0, j = 0; i < n - 1; ++i) {
        while (nodes[j].connect_number == 1 && j + 1 < n) ++j;
        nodes[i].connect_number--;
        nodes[j].connect_number--;
        printf("%d %d\n", nodes[i].node_id, nodes[j].node_id);
    }
    return 0;
}