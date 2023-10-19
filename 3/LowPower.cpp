// #3C. Low power (optional)
// 选做题不计入课程分数
// @Source: This problem is from ACM/ICPC World Final 2013

// 思路：一台机器分配2k个电池，那它的能量之差最小值一定是最小的两个电池的差
// 因此，我们要寻找到 n 对能量之差最小的

#include <algorithm>
#include <iostream>

bool IsPowerable(const int *power_diff, int n, int k, int max_diff) {
    for (int i = 0, count = 0; count < n; ++i) {
        if (i > count * 2 * k)  // 配不平了
            return false;
        if (power_diff[i] <= max_diff)  // 找到一组
            ++i, ++count;
    }
    return true;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    int *power = new int[2 * n * k];

    int l_diff = -1;  // always impossible
    int r_diff = 0;  // fine
    for (int i = 0; i < 2 * n * k; ++i) std::cin >> power[i], r_diff = std::max(r_diff, power[i]);
    std::sort(power, power + 2 * n * k);
    for (int i = 0; i < 2 * n * k - 1; ++i) power[i] = power[i + 1] - power[i];

    IsPowerable(power, n, k, 2);

    while (l_diff + 1 < r_diff) {
        int m_diff = (l_diff + r_diff) / 2;
        if (IsPowerable(power, n, k, m_diff))
            r_diff = m_diff;
        else
            l_diff = m_diff;
    }
    std::cout << r_diff << std::endl;
    delete[] power;
    return 0;
}