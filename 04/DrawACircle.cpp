// #4A. Draw a circle
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <algorithm>
#include <cmath>
#include <iostream>

constexpr double kDoubleMax = 1e300;

struct Point {
    double x, y;
};
inline double PointDistance2(const Point &p1, const Point &p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

// 寻找最小距离两点的距离的平方
double getMinDistance2(const Point *p, int n, Point *tmp) {
    if (n <= 2) {
        if (n == 2)
            return PointDistance2(p[0], p[1]);
        return kDoubleMax;
    }
    double d1 = getMinDistance2(p, n / 2, tmp);
    double d2 = getMinDistance2(p + n / 2, n - n / 2, tmp);
    double d3 = std::min(d1, d2);
    double d0 = std::sqrt(d3);

    int n2 = 0;
    for (int i = 0; i < n; i++)
        if (p[i].x > p[n / 2].x - d0 && p[i].x <= p[n / 2].x + d0)
            tmp[n2++] = p[i];
    std::sort(tmp, tmp + n2, [](const auto &i, const auto &j) { return i.y < j.y; });

    for (auto i = 0; i < n2; ++i) {
        for (auto j = i + 1; j < n2 && j < i + 5; ++j)
            d3 = std::min(d3, PointDistance2(tmp[i], tmp[j]));
    }
    return d3;
}

double findMinOn2(const Point *p, int n) {
    auto d2 = kDoubleMax;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++) d2 = std::min(d2, PointDistance2(p[i], p[j]));
    return d2;
}

int main() {
    int n;
    std::cin >> n;
    Point *arr = new Point[n * 2];
    for (int i = 0; i < n; ++i) std::cin >> arr[i].x >> arr[i].y;
    std::sort(arr, arr + n, [](const auto &i, const auto &j) { return i.x < j.x; });

    auto d2 = getMinDistance2(arr, n, arr + n);
    printf("%.3lf\n", std::sqrt(d2) / 2);
    delete[] arr;
    return 0;
}