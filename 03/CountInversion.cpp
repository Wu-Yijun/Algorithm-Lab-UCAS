// #3A. Count Inversion
/***
 * @author Yijun-Wu, UCAS
 * @date 30-Dec-2023
 *
 ***/
#include <iostream>

using LL = long long;

LL CountMerge(int *data_l, int *data_r, int *dest, int len_l, int len_r) {
    LL count = 0;
    // Significant 逆序对的定义：大于三倍
    int i = 0, j = 0, k = 0, strong_count = 0;
    while (i < len_l && j < len_r) {
        if (data_l[i] <= data_r[j]) {
            dest[k++] = data_l[i++];
        } else {
            while (strong_count < len_l && data_l[strong_count] <= 3LL * data_r[j]) strong_count++;
            count += len_l - strong_count;
            dest[k++] = data_r[j++];
        }
    }
    while (i < len_l) dest[k++] = data_l[i++];
    while (j < len_r) dest[k++] = data_r[j++];
    return count;
}

/* read from data and write sorted array into dest */
LL CountInverse(const int *data, int n, int *dest, int *temp) {
    if (n < 1)
        return 0;
    if (n == 1) {
        *dest = *data;
        return 0;
    }
    LL count = 0;
    count += CountInverse(data, n / 2, temp, dest);
    count += CountInverse(data + n / 2, n - n / 2, temp + n / 2, dest);
    count += CountMerge(temp, temp + n / 2, dest, n / 2, n - n / 2);
    return count;
}

/* Test Count Time Complixity O(n^2) */
LL CountON2(const int *data, int n) {
    LL count = 0;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (data[i] > 3LL * data[j])
                ++count;
    return count;
}

int main() {
    int n;
    std::cin >> n;
    int *data = new int[n];
    int *dest = new int[n];
    int *temp = new int[n];
    for (int i = 0; i < n; ++i) std::cin >> data[i];
    LL num = CountInverse(data, n, dest, temp);
    std::cout << num << std::endl;
    delete[] data;
    delete[] dest;
    delete[] temp;
    return 0;
}