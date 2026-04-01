/*
Megoldás lényege:
A B kód i-edik eleme azt mutatja, hány korábbi elem nagyobb az A[i]-nél.
Ez pontosan a prefixben még előfordult számok számából számítható ki.

Mivel A permutáció, egy Fenwick-fával minden lépésben gyorsan megkapjuk,
hány kisebb vagy egyenlő elem szerepelt már.
*/

#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n) : n(n), bit(n + 1, 0) {}
    void add(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] += val;
    }
    int sum(int idx) const {
        int res = 0;
        for (; idx > 0; idx -= idx & -idx) res += bit[idx];
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    Fenwick fw(n);
    for (int i = 1; i <= n; ++i) {
        int x;
        cin >> x;
        int smallerOrEqual = fw.sum(x);
        int code = (i - 1) - smallerOrEqual;
        if (i > 1) cout << ' ';
        cout << code;
        fw.add(x, 1);
    }
    cout << '\n';
    return 0;
}