#include <bits/stdc++.h>
using namespace std;

/*
    Pozitív tömegű sorozaton kétmutatós ablakkal keressük a pontosan K összegű
    legrövidebb szakaszt. Egyenlő hossz esetén a kisebb bal szélső indexű marad.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    int l = 1;
    long long sum = 0;
    int bestL = -1, bestR = -1;
    for (int r = 1; r <= n; ++r) {
        sum += a[r];
        while (l <= r && sum > k) sum -= a[l++];
        if (sum == k) {
            bestL = l;
            bestR = r;
            break;
        }
    }

    if (bestL == -1) cout << -1 << '\n';
    else cout << bestL << ' ' << bestR << '\n';
    return 0;
}