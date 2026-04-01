#include <bits/stdc++.h>
using namespace std;

/*
    Minden naphoz megkeressük, meddig terjedhet úgy jobbra, hogy az adott nap
    maradjon a legkisebb értékű. Ezen a tartományon belül a legnagyobb eladási
    értéket kell kiválasztani, mert ez adja a legnagyobb növekedést.
*/

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