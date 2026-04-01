/*
Hungarian megoldás: a témákat kapacitásuk szerint rendezve olyan csoportokra
osztjuk, amelyek összege pontosan L.

Hint 1: || Minden téma teljes egészében egyetlen szekcióba kerül. ||
Hint 2: || A legnagyobb témákkal érdemes kezdeni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int k, l, n;
vector<string> nev;
vector<int> db, szekcio;
vector<int> sorrend;
vector<vector<int>> eredmeny;

bool dfs(int idx, vector<int> marad, vector<vector<int>> &csoportok) {
    if (idx == n) return true;
    int best = -1, bestCnt = 100;
    for (int i = 0; i < n; ++i) if (szekcio[i] == -1) {
        int cnt = 0;
        for (int s = 0; s < k; ++s) if (marad[s] >= db[i]) ++cnt;
        if (cnt < bestCnt) bestCnt = cnt, best = i;
    }
    if (best == -1) return false;
    for (int s = 0; s < k; ++s) if (marad[s] >= db[best]) {
        marad[s] -= db[best];
        csoportok[s].push_back(best);
        szekcio[best] = s + 1;
        if (dfs(idx + 1, marad, csoportok)) return true;
        csoportok[s].pop_back();
        szekcio[best] = -1;
        marad[s] += db[best];
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> l >> n;
    nev.resize(n); db.resize(n);
    for (int i = 0; i < n; ++i) cin >> nev[i] >> db[i];
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return db[a] > db[b]; });
    vector<int> marad(k, l);
    szekcio.assign(n, -1);
    vector<vector<int>> csoportok(k);
    dfs(0, marad, csoportok);
    for (int s = 0; s < k; ++s) {
        bool first = true;
        for (int idx : csoportok[s]) {
            for (int rep = 0; rep < db[idx]; ++rep) {
                if (!first) cout << ' ';
                cout << nev[idx];
                first = false;
            }
        }
        cout << '\n';
    }
    return 0;
}