/*
   Inverzió: a legnagyobb távolságú inverziót kell megadni. Jobbról balra
   haladva egy Fenwick-fa tárolja, hogy egy kisebb értékhez mekkora jobb oldali
   pozíció tartozik a legjobban.
*/
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n = 0) : n(n), bit(n + 1, -1) {}
    void update(int idx, int val) {
        for (; idx <= n; idx += idx & -idx) bit[idx] = max(bit[idx], val);
    }
    int query(int idx) {
        int res = -1;
        for (; idx > 0; idx -= idx & -idx) res = max(res, bit[idx]);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) cin >> a[i];

    Fenwick fw(N);
    int bestI = -1, bestJ = -1, bestD = -1;
    for (int i = N; i >= 1; --i) {
        int j = fw.query(a[i] - 1);
        if (j != -1 && j - i > bestD) {
            bestD = j - i;
            bestI = i;
            bestJ = j;
        }
        fw.update(a[i], i);
    }

    if (bestI == -1) cout << -1 << '\n';
    else cout << bestI << ' ' << bestJ << '\n';
    return 0;
}