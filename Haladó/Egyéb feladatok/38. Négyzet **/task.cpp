/*
Megoldás lényege:
Minden keresett négyzet bal alsó csúcsából (p) indulunk ki. Ha p-vel azonos sorban jobbra vannak pontok, az alsó oldal jobb csúcsa egy ilyen pont; ha p-vel azonos oszlopban felfelé vannak pontok, a bal oldal felső csúcsa egy ilyen pont. Egy d oldalhossz akkor jó, ha p jobbra lévő sorbeli pontjai és p feletti oszlopbeli pontjai között van d távolságú pár, és a négyzet jobb felső sarka is pont. A két távolságlista metszetét rendezett listákkal, kétmutatós bejárással vagy a rövidebb listából bináris kereséssel határozzuk meg, csökkenő d szerint. A jobb felső sarkot csak a metszetbeli d-knél keressük meg rendezett kulcsok között. Az első találat p-re a legnagyobb négyzet, és ha d már nem nagyobb a globális legjobbnál, a bejárást abbahagyjuk.
*/
/*
Hint 1: || Egy négyzet alsó oldalának két csúcsa ugyanabban a vízszintes sorban van, bal oldalának két csúcsa ugyanabban az oszlopban. Rögzíts egy bal alsó csúcsot, és keresd a hozzá tartozó sorbeli és oszlopbeli pontokat. ||
Hint 2: || A bal alsó csúcs jobbra lévő sorbeli pontjainak és felette lévő oszlopbeli pontjainak távolságai közül kell egyezést találni: ha ugyanaz a d mindkét listában szerepel, a jobb alsó és a bal felső csúcs már megvan, csak a jobb felső csúcsot kell ellenőrizni. ||
Hint 3: || A két rendezett távolságlista metszetét a rövidebb listából kiindulva, bináris kereséssel, vagy két mutatóval, csökkenő sorrendben határozd meg. A jobb felső csúcsot csak a találatoknál keresd kulcsok között. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> x(n), y(n);
    for (int i = 0; i < n; ++i) cin >> x[i] >> y[i];

    // A pontok kulcsa x * 2^21 + y; a koordináták és a négyzet csúcsai 2^21 alatt maradnak.
    const long long SH = 1LL << 21;
    vector<pair<long long, int>> keys(n);
    for (int i = 0; i < n; ++i) keys[i] = {x[i] * SH + y[i], i};
    sort(keys.begin(), keys.end());

    // Megkeresi az (X, Y) pont sorszámát, vagy -1-et, ha nincs ilyen pont.
    auto find = [&](long long X, long long Y) -> int {
        long long k = X * SH + Y;
        auto it = lower_bound(keys.begin(), keys.end(), make_pair(k, -1));
        if (it != keys.end() && it->first == k) return it->second;
        return -1;
    };

    // Sorok: y szerint, azon belül x szerint. Oszlopok: x szerint, azon belül y szerint.
    vector<int> byRow(n), byCol(n);
    iota(byRow.begin(), byRow.end(), 0);
    iota(byCol.begin(), byCol.end(), 0);
    sort(byRow.begin(), byRow.end(), [&](int a, int b) {
        return y[a] != y[b] ? y[a] < y[b] : x[a] < x[b];
    });
    sort(byCol.begin(), byCol.end(), [&](int a, int b) {
        return x[a] != x[b] ? x[a] < x[b] : y[a] < y[b];
    });

    // A sorban/oszlopban álló koordináták tömbösítve (folytonos memória a gyors bejáráshoz).
    vector<long long> rowX(n), colY(n);
    for (int t = 0; t < n; ++t) {
        rowX[t] = x[byRow[t]];
        colY[t] = y[byCol[t]];
    }

    // Minden pontra: helye a sorában/oszlopában, és a sor/oszlop vége (kizárva).
    vector<int> rowPos(n), rowEnd(n), colPos(n), colEnd(n);
    for (int s = 0; s < n;) {
        int e = s;
        while (e < n && y[byRow[e]] == y[byRow[s]]) ++e;
        for (int t = s; t < e; ++t) {
            rowPos[byRow[t]] = t;
            rowEnd[byRow[t]] = e;
        }
        s = e;
    }
    for (int s = 0; s < n;) {
        int e = s;
        while (e < n && x[byCol[e]] == x[byCol[s]]) ++e;
        for (int t = s; t < e; ++t) {
            colPos[byCol[t]] = t;
            colEnd[byCol[t]] = e;
        }
        s = e;
    }

    long long best = 0;
    int c1 = -1, c2 = -1, c3 = -1, c4 = -1;  // bal alsó, jobb alsó, jobb felső, bal felső

    for (int p = 0; p < n; ++p) {
        long long X = x[p], Y = y[p];
        // p jobbra lévő sorbeli pontjai: [rs, re) a rowX-ben, p feletti oszlopbeli pontjai: [us, ue) a colY-ban
        int rs = rowPos[p] + 1, re = rowEnd[p];
        int us = colPos[p] + 1, ue = colEnd[p];
        int r = re - rs, u = ue - us;
        if (r <= 0 || u <= 0) continue;

        int lo = min(r, u), hi = max(r, u);
        int lg = 32 - __builtin_clz((unsigned)hi);
        bool useSearch = (long long)lo * (lg + 1) < (long long)(r + u);

        if (!useSearch) {
            // Kétmutatós metszet, csökkenő távolság szerint.
            int i = re - 1, j = ue - 1;
            while (i >= rs && j >= us) {
                long long dR = rowX[i] - X;  // jobb alsó csúcs távolsága
                long long dU = colY[j] - Y;  // bal felső csúcs távolsága
                if (max(dR, dU) <= best) break;
                if (dR > dU) { --i; continue; }
                if (dU > dR) { --j; continue; }
                int tr = find(X + dR, Y + dR);
                if (tr >= 0) {
                    best = dR;
                    c1 = p; c2 = byRow[i]; c3 = tr; c4 = byCol[j];
                    break;
                }
                --i; --j;
            }
        } else if (r <= u) {
            // A rövidebb sorbeli lista elemeire bináris keresés az oszlopban.
            for (int t = re - 1; t >= rs; --t) {
                long long d = rowX[t] - X;
                if (d <= best) break;
                long long target = Y + d;
                int j = int(lower_bound(colY.begin() + us, colY.begin() + ue, target) - colY.begin());
                if (j >= ue || colY[j] != target) continue;
                int tr = find(X + d, Y + d);
                if (tr < 0) continue;
                best = d;
                c1 = p; c2 = byRow[t]; c3 = tr; c4 = byCol[j];
                break;
            }
        } else {
            // A rövidebb oszlopbeli lista elemeire bináris keresés a sorban.
            for (int j = ue - 1; j >= us; --j) {
                long long d = colY[j] - Y;
                if (d <= best) break;
                long long target = X + d;
                int t = int(lower_bound(rowX.begin() + rs, rowX.begin() + re, target) - rowX.begin());
                if (t >= re || rowX[t] != target) continue;
                int tr = find(X + d, Y + d);
                if (tr < 0) continue;
                best = d;
                c1 = p; c2 = byRow[t]; c3 = tr; c4 = byCol[j];
                break;
            }
        }
    }

    if (best == 0) {
        cout << 0 << '\n';
    } else {
        cout << best * best << '\n';
        cout << c1 + 1 << ' ' << c2 + 1 << ' ' << c3 + 1 << ' ' << c4 + 1 << '\n';
    }
    return 0;
}
