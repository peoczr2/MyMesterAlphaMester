#include <bits/stdc++.h>
using namespace std;

/*
    A leghosszabb ismétlődő rész kereséséhez a két kezdőpozíció közös előtagjának
    hosszát számoljuk dinamikával. A maximális hossz esetén a legkorábbi kezdést
    tartjuk meg.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> nxt(n + 2, 0), cur(n + 2, 0);
    int bestLen = 0, bestPos = n + 1;

    for (int i = n; i >= 1; --i) {
        fill(cur.begin(), cur.end(), 0);
        for (int j = n; j > i; --j) {
            if (a[i] == a[j]) {
                cur[j] = nxt[j + 1] + 1;
                if (cur[j] > bestLen || (cur[j] == bestLen && i < bestPos)) {
                    bestLen = cur[j];
                    bestPos = i;
                }
            }
        }
        swap(cur, nxt);
    }

    if (bestLen == 0) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < bestLen; ++i) {
        if (i) cout << ' ';
        cout << a[bestPos + i];
    }
    cout << '\n';
    return 0;
}