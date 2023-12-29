// #3B. River
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>

using LL = long long;

bool IsEasy(const int *distance, int n, int m, int min_jump) {
    int i = 0, d = 0;
    while (i <= n) {
        d += distance[i];
        if (d >= min_jump) {
            // needn't remove this stone
            d = 0;
        } else if (m > 0) {
            // remove stone
            m--;
        } else if (distance[i] < min_jump) {
            // can not remove
            return false;
        }
        i++;
    }
    // now we get to other side
    // min jump > min_jump
    return true;
}

int main() {
    int l, n, m;
    std::cin >> l >> n >> m;
    int *dis = new int[n + 1];
    for (int i = 0; i < n; ++i) std::cin >> dis[i];
    std::sort(dis, dis + n);
    dis[n] = l;
    for (int i = n; i > 0; --i) dis[i] -= dis[i - 1];

    int l_dis = 1;      // always ok;
    int r_dis = l + 1;  // impossible
    while (l_dis + 1 < r_dis) {
        int m_dis = (l_dis + r_dis) / 2;
        if (IsEasy(dis, n, m, m_dis)) {
            // possible
            l_dis = m_dis;
        } else {
            r_dis = m_dis;
        }
    }
    std::cout << l_dis;
    delete[] dis;
    return 0;
}