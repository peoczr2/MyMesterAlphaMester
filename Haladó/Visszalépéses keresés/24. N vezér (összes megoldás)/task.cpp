/*
Hungarian megoldás: az N vezér összes megoldásához soronként építjük fel a
kirakást, és minden lépésben kizárjuk az elfoglalt oszlopokat és átlókat.

Hint 1: || Ha minden sorba pontosan egy vezér kerül, akkor már csak az oszlopok
és a kétféle átló ütközését kell figyelni. ||
Hint 2: || Az összes megoldást visszalépéses kereséssel, soronként lehet felsorolni. ||
Hint 3: || Ha egyetlen megoldás sincs, a kimenet -1. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> oszlop, fdiag, bdiag, hely;
bool van = false;

void kiir() {
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << hely[i];
    }
    cout << '\n';
    van = true;
}

void dfs(int sor) {
    if (sor == n) {
        kiir();
        return;
    }
    for (int c = 0; c < n; ++c) {
        int fd = sor + c;
        int bd = sor - c + n - 1;
        if (oszlop[c] || fdiag[fd] || bdiag[bd]) continue;
        oszlop[c] = fdiag[fd] = bdiag[bd] = 1;
        hely[sor] = c + 1;
        dfs(sor + 1);
        oszlop[c] = fdiag[fd] = bdiag[bd] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    oszlop.assign(n, 0);
    fdiag.assign(2 * n - 1, 0);
    bdiag.assign(2 * n - 1, 0);
    hely.assign(n, 0);
    dfs(0);
    if (!van) cout << -1 << '\n';
    return 0;
}