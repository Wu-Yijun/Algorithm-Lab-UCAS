#include <iostream>
#include <string>

using namespace std;

int main() {
    string r1, r2;
    cin >> r1 >> r2;
    auto getNum = [](string s) {
        long long res = 1;
        for (auto c : s) res = (res * (c - 'A' + 1)) % 47;
        return res;
    };
    int a1 = getNum(r1), a2 = getNum(r2);
    if (a1 == a2) {
        cout << "GO\nr1=r2=" << a1 << endl;
    } else {
        cout << "STAY\nr1=" << a1 << " r2=" << a2 << endl;
    }
    return 0;
}