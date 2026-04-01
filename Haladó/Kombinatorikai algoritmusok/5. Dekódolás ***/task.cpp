/*
   Dekódolás: a b_i érték a balra eső nagyobb elemek száma, vagyis egy
   inverziós kód. Jobbról balra haladva mindig a még szabad számok közül
   a megfelelő sorszámút választjuk ki Fenwick-fával.
*/
#include <bits/stdc++.h>
using namespace std;

struct Fenwick {
    int n;
    vector<int> bit;
    Fenwick(int n = 0) { init(n); }
    void init(int n_) { n = n_; bit.assign(n + 1, 0); }
    void add(int idx, int val) { for (; idx <= n; idx += idx & -idx) bit[idx] += val; }
    int kth(int k) const {
        int idx = 0;
        int pw = 1;
        while ((pw << 1) <= n) pw <<= 1;
        for (int d = pw; d; d >>= 1) {
            int ni = idx + d;
            if (ni <= n && bit[ni] < k) {
                idx = ni;
                k -= bit[ni];
            }
        }
        return idx + 1;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> b(N + 1);
    for (int i = 1; i <= N; ++i) cin >> b[i];

    Fenwick ft(N);
    for (int i = 1; i <= N; ++i) ft.add(i, 1);

    vector<int> a(N + 1);
    for (int i = N; i >= 1; --i) {
        int pos = ft.kth(i - b[i]);
        a[i] = pos;
        ft.add(pos, -1);
    }

    for (int i = 1; i <= N; ++i) {
        if (i > 1) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}