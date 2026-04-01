/*
Hungarian megoldás: ugyanaz a vezér-elhelyezéses visszalépés, mint az összes
megoldásnál, de az első jó megoldásnál azonnal megállunk.

Hint 1: || Soronként haladva csak az oszlop- és átlóütközéseket kell figyelni. ||
Hint 2: || Elég az első működő kirakást megtalálni, nem kell az összeset felsorolni. ||
Hint 3: || Ha nincs megoldás, egyetlen -1-et kell írni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> oszlop, fdiag, bdiag, hely;
bool megvan = false;

void dfs(int sor) {
    if (megvan) return;
    if (sor == n) {
        for (int i = 0; i < n; ++i) {
            if (i) cout << ' ';
            cout << hely[i];
        }
        cout << '\n';
        megvan = true;
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
    if (!megvan) cout << -1 << '\n';
    return 0;
}