// #6B. 跳舞机
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <iostream>
using namespace std;

constexpr int kMaxLen = 10;
// constexpr int kMaxLen = 1000000 + 100;
constexpr int kMaxInt = 10000000;
int seq[kMaxLen];
int dp[kMaxLen][4][4];

constexpr int Score[4][4] = {
    {0, 3, 2, 4},  // from L to j
    {1, 0, 3, 2},  // from R to j
    {3, 2, 0, 2},  // from U to j
    {1, 3, 2, 0}   // from D to j
};

inline constexpr int MoveToInt(char c) {
    switch (c) {
        case 'L':
            return 0;
        case 'R':
            return 1;
        case 'U':
            return 2;
        case 'D':
            return 3;
    }
    return 0;
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

void ReadAndCalc(){
    int len = 0;
    char c;
    while ((c = getchar()) != '\n') seq[len++] = MoveToInt(c);
    for (int i = 0; i <= len; ++i)
        for (int j = 0; j < 4; ++j)
            for (int k = 0; k < 4; ++k) dp[i][j][k] = kMaxInt;
    dp[0][MoveToInt('L')][MoveToInt('R')] = 0;  // 初始状态

    for (int i = 0; i < len; ++i) {
        // 迈右脚
        for (int j = 0, k = seq[i]; j < 4; ++j) {
            if (k == j)  // 不能到同一脚
                continue;
            int score = kMaxInt;
            for (int k0 = 0; k0 < 4; ++k0)
                if (k0 != j)  // 不能从同一脚出发
                    score = min(score, Score[k0][k] + 1 + dp[i][j][k0]);
            dp[i + 1][j][k] = score;
        }
        // 迈左脚
        for (int k = 0, j = seq[i]; k < 4; ++k) {
            if (k == j)  // 不能到同一脚
                continue;
            int score = kMaxInt;
            for (int j0 = 0; j0 < 4; ++j0)
                if (j0 != k)  // 不能从同一脚出发
                    score = min(score, Score[j0][j] + 1 + dp[i][j0][k]);
            dp[i + 1][j][k] = score;
        }
    }

    int score = kMaxInt;
    for (int j = 0; j < 4; ++j)
        for (int k = 0; k < 4; ++k)
            if (k != j)
                score = min(score, dp[len][j][k]);
    printf("%d\n", score);
}

int main() {
    int n;
    read(n);
    while(n--)
        ReadAndCalc();
    return 0;
}