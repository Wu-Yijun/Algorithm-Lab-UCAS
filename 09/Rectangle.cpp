// #9A. Rectangle
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>

constexpr int kMaxPoints = 5050;

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

struct Point {
    int x, y;
};
Point points[kMaxPoints];
Point stack[kMaxPoints];

int main() {
    int m, n, k;
    read(n), read(m), read(k);
    for (int i = 0; i < k; ++i) read(points[i].x), read(points[i].y);
    std::sort(points, points + k, [](Point a, Point b) { return a.x < b.x; });
    int area = std::max(m, n);
    for (int i = 0; i < k; ++i) {
        int x = points[i].x, y = points[i].y;
        int up = m, down = 0;
        for (int j = i + 1; j < k; ++j) {
            if (points[j].x == x)
                continue;
            // p[i] 位于左边界 p[j] 位于右边界 （不包含顶点）
            if (points[j].y > y) {
                if (points[j].y > up)
                    continue;
                area = std::max(area, (up - down) * (points[j].x - x));
                up = points[j].y;
            } else if (points[j].y < y) {
                if (points[j].y < down)
                    continue;
                area = std::max(area, (up - down) * (points[j].x - x));
                down = points[j].y;
            } else {
                // y 相等
                area = std::max(area, (up - down) * (points[j].x - x));
                up = down;
                break;
            }
        }
        area = std::max(area, (up - down) * (n - x));
    }
    // 一条边在左侧边界上，最大的面积
    // 类似于直方图中最大的矩形面积
    std::sort(points, points + k, [](Point a, Point b) { return a.y < b.y; });
    int stack_top = 0;
    stack[0] = {n, 0};
    int i = 0;
    points[k] = {0, m};
    while (i <= k) {
        if (stack_top != -1 && points[i].x < stack[stack_top].x) {
            area = std::max(
                area, stack[stack_top].x *
                          (stack_top == 0 ? points[i].y : points[i].y - stack[stack_top - 1].y));
            --stack_top;
        } else {
            stack[++stack_top] = points[i++];
        }
    }
    // 最大贯穿横条
    int max_hei = points[0].y;
    for (i = 1; i <= k; ++i) max_hei = std::max(max_hei, points[i].y - points[i - 1].y);
    area = std::max(area, max_hei * n);
    printf("%d", area);
    return 0;
}
