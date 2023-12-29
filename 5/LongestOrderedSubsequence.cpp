// #5B. Longest Ordered Subsequence
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <cstring>
#include <iostream>

using namespace std;

constexpr int kMaxLength = 1100000;
int dp[kMaxLength];

template <typename T>
void read(T &x) {
    x = 0;
    int f = 1;
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
    int n;
    read(n);
    int len = 0;
    for (int i = 0; i < n; ++i) {
        int ai;
        read(ai);
        if (len == 0 || dp[len - 1] < ai) {
            dp[len++] = ai;
        } else {
            auto it = lower_bound(dp, dp + len, ai);
            *it = ai;
        }
    }
    cout << len << endl;
    return 0;
}