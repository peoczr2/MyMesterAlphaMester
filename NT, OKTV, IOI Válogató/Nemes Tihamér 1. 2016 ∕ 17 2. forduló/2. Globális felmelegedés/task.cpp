#include <bits/stdc++.h>
using namespace std;

/*
    Az éves átlagok összegekkel helyettesíthető, mert minden évben ugyanannyi
    napot figyelünk meg. A feladat többi része egyszerű szélsőérték-keresés a
    sorok és oszlopok mentén.
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> t(n + 1, vector<int>(m + 1));
    vector<long long> evosszeg(n + 1);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> t[i][j];
            evosszeg[i] += t[i][j];
        }
    }

    int legjobb_ev = 1;
    for (int i = 2; i <= n; ++i) {
        if (evosszeg[i] > evosszeg[legjobb_ev]) {
            legjobb_ev = i;
        }
    }

    int kezdo_ev = legjobb_ev;
    while (kezdo_ev > 1 && evosszeg[kezdo_ev - 1] < evosszeg[kezdo_ev]) {
        --kezdo_ev;
    }

    int melegebb_idei_napok = 0;
    vector<int> egyedi_max_ev(m + 1, 0);
    for (int j = 1; j <= m; ++j) {
        int legnagyobb = t[1][j], ev = 1, db = 1;
        for (int i = 2; i <= n; ++i) {
            if (t[i][j] > legnagyobb) {
                legnagyobb = t[i][j];
                ev = i;
                db = 1;
            } else if (t[i][j] == legnagyobb) {
                ++db;
            }
        }
        if (t[n][j] == legnagyobb && db == 1) {
            ++melegebb_idei_napok;
        }
        if (db == 1) {
            egyedi_max_ev[j] = ev;
        }
    }

    int legregibb_ev = n + 1;
    for (int j = 1; j <= m; ++j) {
        if (egyedi_max_ev[j] != 0) {
            legregibb_ev = min(legregibb_ev, egyedi_max_ev[j]);
        }
    }

    cout << legjobb_ev << '\n';
    if (kezdo_ev < legjobb_ev) cout << kezdo_ev << '\n';
    else cout << '\n';
    cout << melegebb_idei_napok << '\n';
    if (legregibb_ev <= n) cout << legregibb_ev << '\n';
    else cout << '\n';
    return 0;
}