// #5C. Posterize (optional)
#include <cstring>
#include <iostream>

using namespace std;
using LL = long long;

constexpr LL kSize = 256 + 10;
constexpr LL kMaxLL = 1LL << 60;
LL dp[kSize][kSize], cost[kSize][kSize];
LL ri[kSize], pi[kSize];

template <typename T>
void read(T &x) {
    x = 0;
    LL f = 1;
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

LL main() {
    LL len, k;
    read(len), read(k);
    for (LL i = 0; i < len; ++i) read(ri[i]), read(pi[i]);

    // cost[i][j] i<=k<=j the min total cost
    memset(cost, 0xf, sizeof(cost));
    for (LL t = 0; t < 256; ++t)
        for (LL i = 0; i < len; ++i) {
            LL res = 0;
            for (LL j = i; j < len; ++j) {
                res += (ri[j] - t) * (ri[j] - t) * pi[j];
                cost[i][j] = min(cost[i][j], res);
            }
        }

    // dp[i][j] devide 0<=k<i into j part
    // dp[i][j] = min(dp[t][j-1] + cost[t][i-1])    t in j-1..i+1
    memset(dp, 0xf, sizeof(dp));
    dp[0][0] = 0;
    for (LL j = 1; j <= k; ++j)
        for (LL i = j; i <= len; ++i) {
            LL res = kMaxLL;
            for (LL t = j - 1; t <= i; ++t) res = min(res, dp[t][j - 1] + cost[t][i - 1]);
            dp[i][j] = res;
        }

    cout << dp[len][k] << endl;

    return 0;
}