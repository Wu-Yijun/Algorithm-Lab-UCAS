// #6C. Branch Assignment (optional)
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
// Note: 这个代码是我网上找的
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
typedef long long ll;
constexpr int kMax = 5010;
vector<int> g[2][kMax], d[2][kMax];
ll sum[kMax], f[kMax][kMax];

const int inf = 1e9;
typedef pair<int, int> pii;
int dist[kMax], sumd[kMax];
void dijkstra(vector<int> g[], vector<int> d[], int s) {
    priority_queue<pii> pq;
    for (int i = 0; i < kMax; ++i) dist[i] = inf;
    dist[s] = 0;
    pq.push(pii(0, s));
    while (!pq.empty()) {
        pii tmp = pq.top();
        pq.pop();
        int x = tmp.second;
        if (dist[x] < -tmp.first)
            continue;
        for (int i = 0; i < (int)g[x].size(); ++i) {
            int to = g[x][i], cost = d[x][i];
            if (dist[to] > dist[x] + cost) {
                dist[to] = dist[x] + cost;
                pq.push(pii(-dist[to], to));
            }
        }
    }
}

void solve(int i, int l, int r, int pl, int pr) {
    int p = -1;
    int m = (l + r) / 2;
    for (int j = pl; j <= min(pr, m - 1); ++j) {
        ll tmp = f[i - 1][j] + (m - j - 1) * (sum[m] - sum[j]);
        if (tmp < f[i][m])
            f[i][m] = tmp, p = j;
    }
    if (m > l)
        solve(i, l, m - 1, pl, p);
    if (m < r)
        solve(i, m + 1, r, p, pr);
}

template <typename T>
void read(T &x) {
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
    int n, b, s, r;
    read(n), read(b), read(s), read(r);
    for (int i = 1; i <= r; ++i) {
        int u, v, w;
        read(u), read(v), read(w);
        g[0][u].push_back(v), d[0][u].push_back(w);
        g[1][v].push_back(u), d[1][v].push_back(w);
    }
    int S = b + 1;
    for (int i = 0; i < 2; ++i) {
        dijkstra(g[i], d[i], S);
        for (int j = 1; j <= b; ++j) sumd[j] += dist[j];
    }
    sort(sumd + 1, sumd + 1 + b);
    for (int i = 1; i <= b; ++i) sum[i] = sum[i - 1] + sumd[i];
    for (int i = 0; i < kMax; ++i)
        for (int j = 0; j < kMax; ++j) f[i][j] = 1e18;
    f[0][0] = 0;
    for (int i = 1; i <= s; ++i) solve(i, i, b, i - 1, b - 1);
    printf("%lld\n", f[s][b]);
    return 0;
}