#include <bits/stdc++.h>
using namespace std;

/*
    Három kiválasztott hét összegét keressük a lehető legnagyobbnak, de F-nél
    nem nagyobbnak. A rendezett árak miatt kétmutatós technikával minden első
    hétre megkeressük a legjobb párt.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long f;
    cin >> n >> f;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    long long best = -1;
    int bi = -1, bj = -1, bk = -1;

    for (int i = 1; i <= n - 2; ++i) {
        int l = i + 1, r = n;
        while (l < r) {
            long long sum = a[i] + a[l] + a[r];
            if (sum > f) {
                --r;
            } else {
                if (sum > best) {
                    best = sum;
                    bi = i; bj = l; bk = r;
                }
                ++l;
            }
        }
    }

    if (best < 0) {
        cout << -1 << '\n';
    } else {
        cout << bi << ' ' << bj << ' ' << bk << '\n';
    }
    return 0;
}