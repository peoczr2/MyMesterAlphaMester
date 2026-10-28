/*
Megoldás lényege:
Két ablak távolsága a különböző pozíciók száma. Egy s = j - i eltolásnál a távolságok csúszó ablakként
számolhatók: egy lépésben egy kilépő és egy belépő pozíciópár eltérése változik, így minden ablakpárra
O(1) munka jut, összesen O(W^2) időben (W = n - l + 1). Mivel legfeljebb q (<= 100) különböző k van,
ablakonként elég a párok távolságait a k-küszöbök szerinti vödrökbe gyűjteni: egy távolságot a legkisebb
olyan k-hoz sorolunk, amely már elég neki. A vödrök prefixösszege adja meg, hány másik ablak k-hasonló.
A tárolás O(W * q), így a 32 MB-os memórialimit is betartható.
*/
/*
Hint 1: || Egy fix s = j - i eltolásnál a szomszédos i ablakok távolsága csak két pozícióban változik: a kilépő és a belépő pozícióiban fellépő eltérés. ||
Hint 2: || Ne tárold minden ablakpár távolságát, hanem ablakonként a lekérdezett k-értékek szerinti vödrökben számold a párokat; a végén a vödrök prefixösszege adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, l;
    cin >> n >> l;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    int q;
    cin >> q;
    vector<int> k(q);
    for (int &x : k) cin >> x;

    int W = n - l + 1;  // az ablakok száma

    // a különböző k-értékek rendezve (legfeljebb q darab)
    vector<int> K = k;
    sort(K.begin(), K.end());
    K.erase(unique(K.begin(), K.end()), K.end());
    int Q = K.size();

    // tmap[d]: a legkisebb olyan t, hogy K[t] >= d (Q, ha nincs ilyen)
    vector<int> tmap(l + 1);
    for (int d = 0; d <= l; ++d)
        tmap[d] = lower_bound(K.begin(), K.end(), d) - K.begin();

    // B[t * W + i]: hány j-re esik az (i, j) pár a t-edik vödörbe
    int C = Q + 1;  // az utolsó sor a "túl nagy" távolságok vödre
    vector<uint16_t> B((size_t)C * W, 0);
    vector<unsigned char> mm(n);  // mm[p] = [a[p] != a[p + s]]

    for (int s = 1; s < W; ++s) {
        int cnt = W - s;  // párok: (i, i + s), i = 0 .. cnt - 1
        for (int p = 0; p + s < n; ++p) mm[p] = (a[p] != a[p + s]);
        int d = 0;  // az (i, i + s) ablakok távolsága, i = 0 esetén
        for (int t = 0; t < l; ++t) d += mm[t];
        for (int i = 0; i < cnt; ++i) {
            size_t row = (size_t)tmap[d] * W;
            B[row + i]++;
            B[row + i + s]++;
            d += mm[i + l] - mm[i];  // csúszó ablak: kilép mm[i], belép mm[i + l]
        }
    }

    // prefixösszeg a vödrökön: B[t * W + i] = hány másik ablak i-hez k_t-hasonló
    for (int t = 1; t < Q; ++t)
        for (int i = 0; i < W; ++i)
            B[(size_t)t * W + i] += B[(size_t)(t - 1) * W + i];

    string out;
    out.reserve((size_t)q * W * 6);
    char buf[12];
    for (int j = 0; j < q; ++j) {
        int t = lower_bound(K.begin(), K.end(), k[j]) - K.begin();
        for (int i = 0; i < W; ++i) {
            int v = B[(size_t)t * W + i];
            int len = 0;
            do { buf[len++] = char('0' + v % 10); v /= 10; } while (v);
            while (len) out.push_back(buf[--len]);
            out.push_back(i + 1 < W ? ' ' : '\n');
        }
    }
    cout << out;
    return 0;
}
