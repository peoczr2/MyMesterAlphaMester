/*
Hungarian megoldás: a buszos változat ugyanaz a visszalépéses beosztás,
mint a fesztiválos, csak sikertelenség esetén 0-t kell írni.

Hint 1: || A korábbi utasokkal való összeférhetetlenséget érkezési sorrendben ellenőrizzük. ||
Hint 2: || A buszok létszámkorlátja miatt minden döntés lokálisan ellenőrizhető. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, h;
vector<vector<int>> tilt;
vector<int> hely, darab;
bool dfs(int i) {
    if (i == n) return true;
    for (int p = 0; p < m; ++p) {
        if (darab[p] >= h) continue;
        bool ok = true;
        for (int x : tilt[i]) if (x < i && hely[x] == p + 1) { ok = false; break; }
        if (!ok) continue;
        hely[i] = p + 1;
        ++darab[p];
        if (dfs(i + 1)) return true;
        --darab[p];
        hely[i] = 0;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> h;
    tilt.assign(n, {});
    for (int i = 1; i < n; ++i) {
        int x;
        while (cin >> x && x != 0) tilt[i].push_back(x - 1);
    }
    hely.assign(n, 0);
    darab.assign(m, 0);
    if (!dfs(0)) {
        cout << 0 << '\n';
        return 0;
    }
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << hely[i];
    }
    cout << '\n';
    return 0;
}