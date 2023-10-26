// #4B. Money for Nothing (optional)
#include <algorithm>
#include <cmath>
#include <iostream>

using LL = long long;
constexpr int N=503000;
struct Point {
    int x, y;
} pa[N], pb[N];

inline LL Area(const Point a, const Point b) { return ((LL)(b.x - a.x)) * (b.y - a.y); }

template <typename T>
void read(T &res) {
    T x = 0, f = 1;
    char c = ' ';
    for (; !isdigit(c); c = getchar())
        if (c == '-')
            f = -1;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    res = x * f;
}

// from la to ra(included)
LL FindMaxArea(int la, int ra, int lb, int rb) {
    if (la > ra)
        return 0;
    int mida = (la + ra) / 2, midb = lb;
    LL maxA = -1e18;
    for (int i = rb; i >= lb; --i)
        if (pa[mida].x <= pb[i].x)
            if (LL max = Area(pa[mida], pb[i]); max > maxA)
                midb = i, maxA = max;
    maxA = std::max(maxA, FindMaxArea(la, mida - 1, midb, rb));
    maxA = std::max(maxA, FindMaxArea(mida + 1, ra, lb, midb));
    return maxA;
}

// return num of useful points
int GetPointsA(int n) {
    for (int i = 0; i < n; ++i) read(pa[i].x), read(pa[i].y);
    std::sort(pa, pa + n, [](Point a, Point b) { return a.x < b.x || (a.x == b.x && a.y < b.y); });
    int res = 0;
    for (int i = 1; i < n; ++i)
        if (pa[i].y < pa[res].y)
            pa[++res] = pa[i];
    return res;
}
int GetPointsB(int m) {
    for (int i = 0; i < m; ++i) read(pb[i].x), read(pb[i].y);
    std::sort(pb, pb + m, [](Point a, Point b) { return a.x > b.x || (a.x == b.x && a.y > b.y); });
    int res = 0;
    for (int i = 1; i < m; ++i)
        if (pb[i].y > pb[res].y)
            pb[++res] = pb[i];
    return res;
}

int main() {
    int a, b;
    read(a), read(b);
    a = GetPointsA(a);
    b = GetPointsB(b);
    std::cout << FindMaxArea(0, a, 0, b) << std::endl;
    return 0;
}