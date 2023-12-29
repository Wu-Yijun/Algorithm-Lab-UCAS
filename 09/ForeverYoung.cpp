// #9B. Forever Young (optional)
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <algorithm>
#include <cmath>
#include <iostream>

using LL = long long;
constexpr LL kMaxLL = 1LL << 60;

inline bool Modable(LL a, LL b) {
    while (a) {
        if (a % b > 9)
            return false;
        a /= b;
    }
    return true;
}

bool ABaseBLessThanC(char *a, LL b, LL c) {
    __uint128_t res = 0;
    for (int i = 0; a[i]; ++i) {
        res = res * b + (a[i] - '0');
        if (res > (__uint128_t)c)
            return false;
    }
    return true;
}

int main() {
    LL y, nl;
    char l[30];
    scanf("%lld %lld", &y, &nl);
    LL bl = 10, br = y + 1;
    sprintf(l, "%lld", nl);
Retry:
    // 二分查找 bl 保证该基下大于 l ，br 保证该基下小于 y
    while (bl < br - 1) {
        LL m = (bl + br) / 2;
        if (ABaseBLessThanC(l, m, y))
            bl = m;
        else
            br = m;
    }
    // 如果找到了，那么就是最小的基
    if (Modable(y, bl)) {
        printf("%lld", bl);
        return 0;
    }
    if (br > 50000000) {
        // 如果不是 Modable，那么就是不够大，所以直接加一
        sprintf(l, "%lld", ++nl);
        bl = 10;
        goto Retry;
    }
    // 现在可以遍历所有的基，找到最大的 bl 满足 Modable
    while (!Modable(y, bl)) --bl;
    printf("%lld", bl);
    return 0;
}