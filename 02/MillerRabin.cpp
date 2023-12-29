// #2B. Prime
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using namespace std;

int quickpow(long long a, int m, const int n) {
    long long sum = 1;
    while (m) {
        if (m & 1)
            sum = sum * a % n;
        a = a * a % n;
        m >>= 1;
    }
    return sum;
}

bool MR(const int n) {
    if (n < 2)
        return false;
    if (n == 2)
        return true;
    int m = n - 1, r = 0;
    while (!(m & 1)) {
        m >>= 1;
        r++;
    }
    for (int i = 0; i < 3; ++i) {
        int a = rand() % (n - 2) + 2;
        a = quickpow(a, m, n);
        if (a == 1)
            continue;
        int ak[32];
        ak[0] = a;
        for (int j = 1; j <= r; ++j) {
            ak[j] = a = ((long long)a * a) % n;
        }
        if (a != 1)
            return false;
        for (int j = r - 1; j >= 0; --j) {
            if (ak[j] == 1)
                continue;
            if (ak[j] == n - 1)
                break;
            return false;
        }
        i++;
    }
    return true;
}

int main() {
    int t, n;
    cin >> t;
    for (int i = 0; i < t; i++) {
        cin >> n;
        if (MR(n))
            puts("Yes");
        else
            puts("No");
    }
    return 0;
}