// #8A. 使徒行者
#include <algorithm>
#include <iostream>

constexpr int kMaxSpy = 1000050;
constexpr int kMaxInt = 1000000009;

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

struct Spy {
    int attack, tenacious;
};
Spy spies[kMaxSpy];

int main() {
    int n;
    read(n);
    for (int i = 0; i < n; ++i) read(spies[i].attack), read(spies[i].tenacious);
    std::sort(spies, spies + n,
              [](Spy a, Spy b) { return a.attack + a.tenacious < b.attack + b.tenacious; });
    int min_att_damage = kMaxInt, fear_value = 0;
    for (int i = 0; i < n; ++i)
        min_att_damage = std::min(min_att_damage, spies[i].attack - fear_value),
        fear_value += spies[i].tenacious;
    printf("%d", min_att_damage);
    return 0;
}