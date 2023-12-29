// #5A. DNA Sequence Alignment
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <cstring>
#include <iostream>

using namespace std;

constexpr int kMaxLength = 10;
char dna1[kMaxLength], dna2[kMaxLength];
int dp[kMaxLength][kMaxLength];

inline int Score(char a, char b) {
    return a == b ? 0 : ((a == 'C' && b == 'G') || (a == 'G' && b == 'C')) ? 4 : 5;
}

int main() {
    std::cin >> dna1 >> dna2;
    int l1 = strlen(dna1), l2 = strlen(dna2);
    for (int i = 0; i <= l1; ++i) dp[i][0] = 3 * i;
    for (int i = 0; i <= l2; ++i) dp[0][i] = 3 * i;
    for (int i = 1; i <= l1; ++i)
        for (int j = 1; j <= l2; ++j)
            dp[i][j] = min(Score(dna1[i - 1], dna2[j - 1]) + dp[i - 1][j - 1],
                           min(dp[i - 1][j] + 3, dp[i][j - 1] + 3));
    cout << dp[l1][l2] << endl;
    return 0;
}