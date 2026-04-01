/*
Megoldás lényege:
A robot csak jobbra és felfelé léphet, ezért a bejárható áruval teli mezők pontosan a
koordináták szerint nemcsökkenő láncot alkotják. Az ilyen lánc leghosszabb részét egy
2D LIS-sel keressük meg a (x+y)<=L+2 feltétel mellett.

*/

// Hint 1: || A mozgás monotón, tehát a látogatott mezők koordinátái is rendezettek. ||
// Hint 2: || A lépésszám korlátja csak azt szűri, hogy mely pontok érhetők el egyáltalán. ||
// Hint 3: || A leghosszabb láncot egy Fenwick-fa és egy elődmező segítségével vissza lehet fejteni. ||

#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int idx;
};

struct Fenwick {
    int n;
    vector<pair<int, int>> bit; // length, index
    Fenwick(int n = 0) { init(n); }
    void init(int n_) { n = n_; bit.assign(n + 1, {0, -1}); }
    static pair<int, int> better(pair<int, int> a, pair<int, int> b) {
        return a.first >= b.first ? a : b;
    }
    void upd(int i, pair<int, int> v) {
        for (; i <= n; i += i & -i) bit[i] = better(bit[i], v);
    }
    pair<int, int> qry(int i) const {
        pair<int, int> res = {0, -1};
        for (; i > 0; i -= i & -i) res = better(res, bit[i]);
        return res;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    long long L;
    if (!(cin >> N >> L)) return 0;

    vector<Pt> pts(N);
    for (int i = 0; i < N; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].idx = i + 1;
    }

    vector<Pt> cand;
    cand.reserve(N);
    for (auto p : pts) {
        if (p.x + p.y - 2 <= L) cand.push_back(p);
    }

    sort(cand.begin(), cand.end(), [](const Pt& a, const Pt& b) {
        if (a.x != b.x) return a.x < b.x;
        if (a.y != b.y) return a.y < b.y;
        return a.idx < b.idx;
    });

    vector<long long> ys;
    ys.reserve(cand.size());
    for (auto& p : cand) ys.push_back(p.y);
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());

    Fenwick fw((int)ys.size());
    vector<int> parent(cand.size(), -1), dp(cand.size(), 1);
    int best = -1;

    for (int i = 0; i < (int)cand.size(); ++i) {
        int yid = (int)(lower_bound(ys.begin(), ys.end(), cand[i].y) - ys.begin()) + 1;
        auto pr = fw.qry(yid);
        dp[i] = pr.first + 1;
        parent[i] = pr.second;
        fw.upd(yid, {dp[i], i});
        if (best == -1 || dp[i] > dp[best]) best = i;
    }

    vector<int> ans;
    for (int v = best; v != -1; v = parent[v]) ans.push_back(cand[v].idx);
    reverse(ans.begin(), ans.end());

    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
