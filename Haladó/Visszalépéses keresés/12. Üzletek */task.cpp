/*
Hungarian megoldás: kevés pékség esetén visszalépéssel választjuk ki, hogy az
egyes üzletek melyik pékségtől rendeljenek úgy, hogy a napi kapacitások ne
fogyjanak el.

Hint 1: || Mivel a pékségek száma legfeljebb 7, a keresési fa erősen korlátozott. ||
Hint 2: || A legszűkebb üzlettel érdemes kezdeni, vagyis amelynek kevés lehetősége van. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> igeny, kap;
vector<vector<int>> kapcsolatok;
vector<int> ans;
vector<char> hasznalt;

bool jobb(int a, int b) {
    int ca = 0, cb = 0;
    for (int x : kapcsolatok[a]) if (kap[x] >= igeny[a]) ++ca;
    for (int x : kapcsolatok[b]) if (kap[x] >= igeny[b]) ++cb;
    if (ca != cb) return ca < cb;
    return igeny[a] > igeny[b];
}

bool dfs(int placed, long long leftDemand) {
    if (placed == n) return true;
    if (leftDemand > accumulate(kap.begin(), kap.end(), 0LL)) return false;
    int best = -1;
    vector<int> cand;
    for (int i = 0; i < n; ++i) if (!hasznalt[i]) {
        vector<int> v;
        for (int x : kapcsolatok[i]) if (kap[x] >= igeny[i]) v.push_back(x);
        if (v.empty()) return false;
        if (best == -1 || v.size() < cand.size() || (v.size() == cand.size() && igeny[i] > igeny[best])) {
            best = i;
            cand = move(v);
        }
    }
    hasznalt[best] = 1;
    for (int b : cand) {
        kap[b] -= igeny[best];
        ans[best] = b + 1;
        if (dfs(placed + 1, leftDemand - igeny[best])) return true;
        kap[b] += igeny[best];
    }
    hasznalt[best] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    igeny.resize(n);
    for (int i = 0; i < n; ++i) cin >> igeny[i];
    kap.resize(m);
    for (int i = 0; i < m; ++i) cin >> kap[i];
    kapcsolatok.assign(n, {});
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        kapcsolatok[i].resize(p);
        for (int j = 0; j < p; ++j) {
            cin >> kapcsolatok[i][j];
            --kapcsolatok[i][j];
        }
    }
    ans.assign(n, -1);
    hasznalt.assign(n, 0);
    long long total = accumulate(igeny.begin(), igeny.end(), 0LL);
    if (!dfs(0, total)) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}