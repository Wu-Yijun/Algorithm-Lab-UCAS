// #2A. MinMaxMinusMin
/***
 * @author Yijun-Wu, UCAS
 * @date 12-Dec-2023
 *
 ***/
#include <algorithm>
#include <climits>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> arr(n), lmin(n), rmin(n + 1), lmax(n), rmax(n + 1);
    int min0 = INT_MAX, max0 = 0;
    for (int i = 0; i < n; ++i)
        cin >> arr[i], lmin[i] = min0 = min(min0, arr[i]), lmax[i] = max0 = max(max0, arr[i]);
    min0 = INT_MAX, max0 = 0;
    rmax[n] = 0, rmin[n] = INT_MAX;
    for (int i = n - 1; i >= 0; --i)
        rmin[i] = min0 = min(min0, arr[i]), rmax[i] = max0 = max(max0, arr[i]);
    int diff = rmax[k] - rmin[k];
    for (int i = 1; i <= n - k; ++i)
        diff = min(diff, max(lmax[i - 1], rmax[i + k]) - min(lmin[i - 1], rmin[i + k]));
    cout << diff << endl;
    return 0;
}