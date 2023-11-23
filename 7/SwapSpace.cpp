// #7C. Swap Space (optional)
#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>
using namespace std;
using LL = long long;

constexpr int kMax = 1000010;

typedef pair<LL, LL> LLPair;
LLPair change[kMax + 50];
LLPair change2[kMax + 50];

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
    int n, add_num = 0, reduce_num = 0;
    read(n);
    for (int i = 0; i < n; ++i) {
        LL a, b;
        read(a), read(b);
        if (a <= b) {
            change[add_num] = {a, b};
            ++add_num;
        } else {
            change2[reduce_num] = {a, b};
            ++reduce_num;
        }
    }
    sort(change, change + add_num, [](LLPair a, LLPair b) {
        return a.first < b.first || (a.first == b.first && a.second > b.second);
    });
    sort(change2, change2 + reduce_num, [](LLPair a, LLPair b) {
        return a.second > b.second || (a.second == b.second && a.first < b.first);
    });

    LL free_mem = 0, extra_mem = 0;
    for (int i = 0; i < add_num; ++i) {
        free_mem -= change[i].first;
        if (free_mem < 0)
            extra_mem += -free_mem, free_mem = 0;
        free_mem += change[i].second;
    }
    for (int i = 0; i < reduce_num; ++i) {
        free_mem -= change2[i].first;
        if (free_mem < 0)
            extra_mem += -free_mem, free_mem = 0;
        free_mem += change2[i].second;
    }

    printf("%lld", extra_mem);

    return 0;
}
