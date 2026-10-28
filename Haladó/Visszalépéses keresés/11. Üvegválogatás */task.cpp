/*
Megoldás lényege: minden üvegfajtához külön ládát jelölünk ki (K ≤ N), és azt keressük, hogy a
kijelölt ládákban összesen hány üveg marad a helyén. A fajtákat sorban vesszük, és visszalépéssel
kipróbáljuk az összes még szabad ládát; a legjobb összeget megjegyezzük. Ha a fajtákhoz már csak
kevés hasznos hely maradhat, a fajtánkénti legnagyobb darabszámok összege alapján levágjuk az ágat.
Az átrakások száma az összes üveg és a helyben maradók számának különbsége. N ≤ 10 esetén a
visszalépéses keresés belefér az időkorlátba.
*/
/*
Hint 1: || A kijelölt ládában már meglévő darabszám az, amit nem kell átrakni: az összes üvegből ezt kell levonni. ||
Hint 2: || Különböző fajtákhoz különböző ládák tartoznak, ezért a fajtákat sorban véve visszalépéssel próbáld végig a még szabad ládákat. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, k;
vector<vector<int>> a;
vector<long long> ub;
vector<int> cur, best;
vector<char> used;
long long bestKept = -1;

void dfs(int j, long long kept) {
    if (j == k) {
        if (kept > bestKept) {
            bestKept = kept;
            best = cur;
        }
        return;
    }
    if (kept + ub[j] <= bestKept) return;
    for (int c = 0; c < n; ++c) {
        if (used[c]) continue;
        used[c] = 1;
        cur[j] = c;
        dfs(j + 1, kept + a[c][j]);
        used[c] = 0;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    a.assign(n, vector<int>(k));
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            cin >> a[i][j];
            total += a[i][j];
        }
    }
    ub.assign(k + 1, 0);
    for (int j = k - 1; j >= 0; --j) {
        int mx = 0;
        for (int i = 0; i < n; ++i) mx = max(mx, a[i][j]);
        ub[j] = ub[j + 1] + mx;
    }
    cur.assign(k, 0);
    used.assign(n, 0);
    dfs(0, 0);
    cout << total - bestKept << '\n';
    for (int j = 0; j < k; ++j) {
        if (j) cout << ' ';
        cout << best[j] + 1;
    }
    cout << '\n';
    return 0;
}
