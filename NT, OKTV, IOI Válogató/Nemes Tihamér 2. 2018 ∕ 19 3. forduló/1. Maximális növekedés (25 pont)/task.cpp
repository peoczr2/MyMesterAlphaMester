/*
Megoldás lényege:
Minden i naphoz meghatározzuk, meddig terjedhet a j nap úgy, hogy az i-edik nap eladása a [i, j] szakasz minimuma maradjon: ez a következő nála kisebb eladású napig tart, és monoton veremmel mind az N napra kiszámolható. Az így kapott tartományon egy szegmensfa adja a legnagyobb eladású napot (döntetlennél a kisebb sorszámút), így minden i-hez egy lekérdezés elég. A kapott különbségek közül a legnagyobbat tartjuk meg, döntetlennél a kisebb i, majd a kisebb j nyer. Az időigény O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Rögzíts egy i napot. A j nap csak addig lehet jobbra, amíg az i-edik nap eladása a [i, j] szakasz legkisebbje, vagyis a következő, nála kevesebbet eladó napig. Ezt a határt minden i-re monoton veremmel gyorsan megkapod. ||
Hint 2: || Az [i+1, r] tartományon a legnagyobb eladású napot kell megtalálni. Azonos eladásnál a kisebb sorszám kell, ezért a szegmensfa csomópontjában érdemes (érték, -sorszám) párt tárolni. ||
Hint 3: || Minden i-re számold ki a legjobb j különbségét, és ezek közül a legnagyobbat válaszd. Ha egyik i-hez sincs pozitív különbség, a válasz 1 1, mert az i = j pár 0 különbséget ad. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct SegTree {
    int n;
    vector<pair<int, int>> st;

    static pair<int, int> better(pair<int, int> a, pair<int, int> b) {
        if (a.first != b.first) return (a.first > b.first ? a : b);
        return (a.second > b.second ? a : b); // -index, így a nagyobb érték a kisebb indexet jelenti
    }

    void build(const vector<int>& a) {
        n = (int)a.size() - 1;
        st.assign(4 * n + 4, {0, 0});
        build(1, 1, n, a);
    }

    void build(int p, int l, int r, const vector<int>& a) {
        if (l == r) {
            st[p] = {a[l], -l};
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        st[p] = better(st[p << 1], st[p << 1 | 1]);
    }

    pair<int, int> query(int p, int l, int r, int ql, int qr) const {
        if (ql > r || qr < l) return {-1, 0};
        if (ql <= l && r <= qr) return st[p];
        int mid = (l + r) >> 1;
        return better(query(p << 1, l, mid, ql, qr), query(p << 1 | 1, mid + 1, r, ql, qr));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> nxtSmaller(n + 1, n + 1);
    vector<int> st;
    for (int i = n; i >= 1; --i) {
        while (!st.empty() && a[st.back()] >= a[i]) st.pop_back();
        nxtSmaller[i] = st.empty() ? n + 1 : st.back();
        st.push_back(i);
    }

    SegTree seg;
    seg.build(a);

    int bestDiff = 0;
    int bestI = 1, bestJ = 1;
    for (int i = 1; i <= n; ++i) {
        int l = i + 1, r = nxtSmaller[i] - 1;
        if (l > r) continue;
        auto got = seg.query(1, 1, n, l, r);
        int val = got.first;
        int j = -got.second;
        if (val <= a[i]) continue;
        int diff = val - a[i];
        if (diff > bestDiff || (diff == bestDiff && (i < bestI || (i == bestI && j < bestJ)))) {
            bestDiff = diff;
            bestI = i;
            bestJ = j;
        }
    }

    cout << bestI << ' ' << bestJ << '\n';
    return 0;
}