/*
Hungarian megoldás: a boltokat egyenként olyan pékségekhez rendeljük, amelyek
kapacitása még elbírja a teljes megrendelést, és a teljes költséget minimalizáljuk.

Hint 1: || Egy bolt csak egy pékségtől rendelhet, ezért a döntés boltonként egyetlen választás. ||
Hint 2: || Kevés bolt és kevés pékség mellett visszalépéses kereséssel lehet minimális költséget találni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int l, k;
vector<int> igeny, kap, ar;
vector<vector<int>> kapcsolat;
vector<int> ans;
vector<char> hasznalt;
long long best = (1LL << 60);

long long lowerBound() {
    long long sum = 0;
    for (int i = 0; i < l; ++i) if (!hasznalt[i]) {
        long long mn = (1LL << 60);
        for (int b : kapcsolat[i]) if (kap[b] >= igeny[i]) mn = min(mn, 1LL * igeny[i] * ar[b]);
        if (mn == (1LL << 60)) return (1LL << 60);
        sum += mn;
    }
    return sum;
}

bool dfs(int placed, long long cost) {
    if (cost >= best) return false;
    long long lb = lowerBound();
    if (lb == (1LL << 60) || cost + lb >= best) return false;
    if (placed == l) {
        best = cost;
        return true;
    }
    int bestIdx = -1;
    vector<int> cand;
    for (int i = 0; i < l; ++i) if (!hasznalt[i]) {
        vector<int> v;
        for (int b : kapcsolat[i]) if (kap[b] >= igeny[i]) v.push_back(b);
        if (v.empty()) return false;
        if (bestIdx == -1 || v.size() < cand.size() || (v.size() == cand.size() && igeny[i] > igeny[bestIdx])) {
            bestIdx = i;
            cand = move(v);
        }
    }
    hasznalt[bestIdx] = 1;
    sort(cand.begin(), cand.end(), [&](int a, int b) {
        return 1LL * igeny[bestIdx] * ar[a] < 1LL * igeny[bestIdx] * ar[b];
    });
    for (int b : cand) {
        kap[b] -= igeny[bestIdx];
        ans[bestIdx] = b + 1;
        dfs(placed + 1, cost + 1LL * igeny[bestIdx] * ar[b]);
        kap[b] += igeny[bestIdx];
    }
    hasznalt[bestIdx] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> l >> k;
    kap.resize(k);
    ar.resize(k);
    igeny.resize(l);
    kapcsolat.assign(l, {});
    for (int i = 0; i < k; ++i) cin >> kap[i];
    for (int i = 0; i < k; ++i) cin >> ar[i];
    for (int i = 0; i < l; ++i) {
        for (int j = 0; j < k; ++j) {
            int x;
            cin >> x;
            if (x) kapcsolat[i].push_back(j);
        }
        cin >> igeny[i];
    }
    ans.assign(l, -1);
    hasznalt.assign(l, 0);
    dfs(0, 0);
    if (best == (1LL << 60)) {
        cout << -1 << '\n';
        return 0;
    }
    for (int i = 0; i < l; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}