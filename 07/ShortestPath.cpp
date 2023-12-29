// #7A. Shortest Path
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;

constexpr int kMax = 10050;
constexpr int kMaxInt = 100000009;

typedef pair<int, int> IntPair;
vector<IntPair> g[kMax];
int dist[kMax];

void dijkstra(int s) {
    priority_queue<IntPair, vector<IntPair>, greater<IntPair>> pq;  // 升序
    for (int i = 0; i < kMax; ++i) dist[i] = kMaxInt;
    dist[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        auto top = pq.top();
        pq.pop();
        int x = top.second;
        if (dist[x] < top.first)
            continue;
        for (int i = 0; i < (int)g[x].size(); ++i) {
            int to = g[x][i].first, cost = g[x][i].second;
            if (dist[to] > dist[x] + cost) {
                dist[to] = dist[x] + cost;
                pq.push({dist[to], to});
            }
        }
    }
}

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

int main() {
    int n, m, s, t;
    read(n), read(m), read(s), read(t);
    for (int i = 1; i <= m; ++i) {
        int u, v, w;
        read(u), read(v), read(w);
        g[u].push_back(make_pair(v, w));
    }
    dijkstra(s);

    printf("%d\n", dist[t] == kMaxInt ? -1 : dist[t]);

    return 0;
}
