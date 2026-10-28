/*
Megoldás lényege:
Mindig két láda van nyitva, ezért az állapot a két nyitott láda terhelése (z, o); a költség a felhasznált ládák száma
(kezdetben 2). Egy tárgy belekerülhet valamelyik nyitott ládába, ha belefér. Ha egy ládát bezárunk, helyére új, üres
láda nyílik, ez +1 költség. Az olcsóbb állapotból a másik ládát bezárva ugyanannyi (plusz 1) költséggel legalább olyan jó
állapot érhető el, mint a drágábbé, ezért ugyanazzal a z terheléssel elég csak a legjobb (költség, o) párt tárolni.
Ezt egyetlen egészben kódoljuk (költség * 2^14 + o), így a minimum lexikografikus minimumot ad.
Tárgyanként minden tárolt állapotból legfeljebb három átmenet képződik: a tárgy az egyik vagy a másik ládába kerül,
vagy új ládába nyílik. Az összidő O(N * L). A végén a mohó, egyetlen ládával kapott eredményt is figyelembe vesszük:
ha minden tárgy egy ládába fér, a két kezdőládát számoló DP túlbecsülné a választ.
*/
/*
Hint 1: || Mindig két láda van nyitva, ezért elég nyilvántartani a két láda aktuális terhelését és a felhasznált ládák számát. ||
Hint 2: || Ha ugyanakkora terheléssel egy nyitott láda kétféle állapotban fordulhat elő, a kisebb költségű állapot mindig jobb; azonos költségnél a másik láda kisebb terhelése jobb. ||
Hint 3: || Egy láda bezárása után az új láda üres, és a tárgyat ide is be lehet tenni; ez +1 költség. Egy állapotot tehát tömbben tárolhatsz a nyitott láda terhelése szerint indexelve. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, n;
    cin >> L >> n;
    vector<int> w(n);
    for (auto &x : w) cin >> x;

    // Egyetlen láda mohó pakolása: ha minden tárgy egy ládába fér, ez 1.
    long long greedy = 1, load = 0;
    for (int x : w) {
        if (load + x <= L) {
            load += x;
        } else {
            ++greedy;
            load = x;
        }
    }

    // Kulcs = költség * 2^14 + másik láda terhelése (L <= 10000 < 2^14).
    const int SH = 14, MASK = (1 << SH) - 1;
    const int INF = INT_MAX / 2;
    const int DUMP = L + 1;  // "szemetes" index a sűrű átmenetekhez

    // A: aktuális állapotok indexelve az egyik láda terhelése szerint, B: a következő lépés (mindkettő INF-tiszta)
    vector<int> A(L + 2, INF), B(L + 2, INF);
    vector<int> cur, nxt;  // ritka módban az aktív indexek listája
    A[0] = (2 << SH) | 0;  // kezdetben két üres láda, költség 2
    cur.push_back(0);
    bool dense = false;

    for (int i = 0; i < n; ++i) {
        int wt = w[i];
        if (!dense) {
            int fresh = INF;  // a tárgy új ládába kerül, a másik láda terhelése mellett
            nxt.clear();
            for (int z : cur) {
                int k = A[z];
                int c = k >> SH, o = k & MASK;
                int t = z + wt;  // tárgy a z-s ládába
                if (t <= L) {
                    if (B[t] == INF) nxt.push_back(t);
                    if (k < B[t]) B[t] = k;
                }
                t = o + wt;  // tárgy a másik ládába
                if (t <= L) {
                    int v = (c << SH) | z;
                    if (B[t] == INF) nxt.push_back(t);
                    if (v < B[t]) B[t] = v;
                }
                int f = ((c + 1) << SH) | (z < o ? z : o);  // új láda: a lezárt láda helyett
                if (f < fresh) fresh = f;
            }
            if (fresh < INF) {
                if (B[wt] == INF) nxt.push_back(wt);
                if (fresh < B[wt]) B[wt] = fresh;
            }
            for (int z : cur) A[z] = INF;
            swap(A, B);
            swap(cur, nxt);
            if ((long long)cur.size() * 8 >= (long long)(L + 1)) dense = true;
        } else {
            int fresh = INF;
            long long cntA = 0;
            for (int z = 0; z <= L; ++z) {
                int k = A[z];
                A[z] = INF;
                cntA += (k < INF);
                int c = k >> SH, o = k & MASK;
                int t1 = min(z + wt, DUMP);
                int t2 = min(o + wt, DUMP);
                int v = (c << SH) | z;
                int f = ((c + 1) << SH) | (z < o ? z : o);
                B[t1] = min(B[t1], k);
                B[t2] = min(B[t2], v);
                fresh = min(fresh, f);
            }
            if (fresh < INF) B[wt] = min(B[wt], fresh);
            B[DUMP] = INF;
            swap(A, B);
            if (cntA * 8 < (long long)(L + 1)) {
                dense = false;
                cur.clear();
                for (int t = 0; t <= L; ++t) {
                    if (A[t] < INF) cur.push_back(t);
                }
            }
        }
    }

    int best = INF;
    if (!dense) {
        for (int z : cur) best = min(best, A[z] >> SH);
    } else {
        for (int z = 0; z <= L; ++z) {
            if (A[z] < INF) best = min(best, A[z] >> SH);
        }
    }

    cout << min<long long>(best, greedy) << "\n";
    return 0;
}
