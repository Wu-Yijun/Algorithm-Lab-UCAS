// #8B. 中位数
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>

constexpr int kMaxMN = 1000060;
// constexpr int kMaxMN = 60;
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

int array[kMaxMN];

int main() {
    int m, n;
    read(n), read(m);
    for (int i = 0; i < m * n; ++i) read(array[i]);
    std::sort(array, array + m * n);
    LL res = 0;
    int stride = m / 2 + 1;
    for (int i = (m - stride) * n; i < m * n; i += stride) res += array[i];
    printf("%d", res);
    return 0;
}