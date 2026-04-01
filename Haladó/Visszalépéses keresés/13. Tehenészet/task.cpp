/*
Hungarian megoldás: kevés tehenészet és kevés tejüzem mellett a tehenészetek
hozzárendelését visszalépéssel keressük, a költséget pedig folyamatosan számoljuk.

Hint 1: || Egy tehenészet teljes tejmennyisége csak egy tejüzembe kerülhet. ||
Hint 2: || A legszűkebb választásokat érdemes előre venni, és az ágonkénti költséget összehasonlítani. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<int> tej, kap;
vector<vector<int>> koltseg;
vector<int> ans, sorrend;
vector<char> hasznalt;
long long best = (1LL << 60);

bool dfs(int placed, long long cost) {
    if (cost >= best) return false;
    if (placed == n) {
        best = cost;
        return true;
    }
    int bestIdx = -1;
    vector<int> cand;
    for (int i = 0; i < n; ++i) if (!hasznalt[i]) {
        vector<int> v;
        for (int b = 0; b < m; ++b) if (kap[b] >= tej[i]) v.push_back(b);
        if (v.empty()) return false;
        if (bestIdx == -1 || v.size() < cand.size() || (v.size() == cand.size() && tej[i] > tej[bestIdx])) {
            bestIdx = i;
            cand = move(v);
        }
    }
    hasznalt[bestIdx] = 1;
    sort(cand.begin(), cand.end(), [&](int a, int b) {
        return koltseg[bestIdx][a] < koltseg[bestIdx][b];
    });
    for (int b : cand) {
        kap[b] -= tej[bestIdx];
        ans[bestIdx] = b + 1;
        dfs(placed + 1, cost + 1LL * tej[bestIdx] * koltseg[bestIdx][b]);
        kap[b] += tej[bestIdx];
    }
    hasznalt[bestIdx] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    tej.resize(n);
    kap.resize(m);
    for (int i = 0; i < n; ++i) cin >> tej[i];
    for (int i = 0; i < m; ++i) cin >> kap[i];
    koltseg.assign(n, vector<int>(m));
    for (int i = 0; i < n; ++i) for (int j = 0; j < m; ++j) cin >> koltseg[i][j];
    ans.assign(n, -1);
    hasznalt.assign(n, 0);
    dfs(0, 0);
    cout << best << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}