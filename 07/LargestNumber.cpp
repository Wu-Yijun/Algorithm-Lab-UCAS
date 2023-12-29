// #7B. Largest Number
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <algorithm>
#include <iostream>
using namespace std;
using LL = long long;

constexpr int kNMax = 1050;
constexpr int kDigitMax = 12;
int numbers[kNMax];

inline constexpr LL combine(int a, int b) {
    LL res = a;
    int c = b;
    while (c != 0) res *= 10, c /= 10;
    return res + b;
}

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> numbers[i];
    sort(numbers, numbers + n, [](int a, int b) { return combine(a, b) > combine(b, a); });
    for (int i = 0; i < n; i++) cout << numbers[i];
    cout << endl;
    return 0;
}