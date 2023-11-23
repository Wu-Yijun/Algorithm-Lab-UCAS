// #6A. Alice's food
#include <iostream>
using namespace std;

constexpr int kMaxFood = 1100;
constexpr int kMaxX = 25;
constexpr int kMaxY = 85;
constexpr int kMaxInt = 10000007;
int foodX[kMaxFood], foodY[kMaxFood], foodZ[kMaxFood];
// 使用前 i 个 food, 达成 x=j y=k 的目标的最小价格
int dp[kMaxFood][kMaxX][kMaxY];

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

// return a positive num or 0
inline int PosOrZero(int x) { return x >= 0 ? x : 0; }

int main() {
    int x, y, n;
    read(x), read(y), read(n);
    for (int i = 1; i <= n; ++i) read(foodX[i]), read(foodY[i]), read(foodZ[i]);
    for (int j = 0; j <= x; ++j)
        for (int k = 0; k <= y; ++k) dp[0][j][k] = kMaxInt;
    dp[0][0][0] = 0;
    for (int i = 1; i <= n; ++i)
        for (int j = 0; j <= x; ++j)
            for (int k = 0; k <= y; ++k)
                dp[i][j][k] =
                    min(dp[i - 1][j][k],
                        dp[i - 1][PosOrZero(j - foodX[i])][PosOrZero(k - foodY[i])] + foodZ[i]);
            
    cout << dp[n][x][y];
    return 0;
}
