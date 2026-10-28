/*
Megoldás lényege: Válasszuk ki, mely ládák maradnak helyben (ezek a tornyok alapjai), a többi láda egy szomszédos alapra kerül. Két alap között a köztes ládák egy prefixe a bal, egy suffixe a jobb alapra megy, mert távolabbi ládához csak a közelebbi elmozgatása után lehet hozzáférni. Egy alapra rakott ládák alulról felfelé szigorúan csökkennek, ezért mindkét oldalon külön-külön kifelé csökkenő sorozat kell, a két oldal magasságai nem egyezhetnek, és az alappal együtt az összeg legfeljebb M. A szabadított hely a mozgatott ládák száma, ezért az alapok számát minimalizáljuk: R[x] az eddigi legkevesebb alapszám, ha az utolsó alap jobb oldali ládái pontosan x-ig érnek. Mivel a mozgatott ládák magassága különböző pozitív egész, egy toronyban legfeljebb kb. 44 láda lehet, így az időigény O(N * 45).
*/
/*
Hint 1: || Egy láda csak nála nagyobbra kerülhet, így egy torony alulról felfelé szigorúan csökken, és az alap magassága is beleszámít az M korlátba. ||
Hint 2: || Két helyben maradó láda között a köztes ládák egy része a bal, másik része a jobb alaphoz kerül; mindig a közelebbi ládát kell előbb mozgatni. ||
Hint 3: || Az alap két oldalát külön lehet vizsgálni, de a két oldal magasságai között nem lehet egyezés; az állapotot az utolsó alap jobb oldali végpozíciója szerint érdemes tárolni. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    vector<int> L(N + 1);
    for (int i = 1; i <= N; ++i) cin >> L[i];

    const int INF = INT_MAX / 2;
    // R[x]: az eddigi legkevesebb alapszám, ha a legutóbbi alap jobb oldali ládái pontosan x-ig érnek.
    // R[0] = 0: még nincs alap.
    vector<int> R(N + 1, INF);
    R[0] = 0;
    vector<int> mark(M + 1, 0);  // mark[v] == b, ha v szerepel a b-edik alap bal oldali láncában
    vector<int> xs, ys, sx, sy, fval, G;

    for (int b = 1; b <= N; ++b) {
        const int base = L[b];
        const int budget = M - base;  // a torony mozgatott ládáinak összege legfeljebb ennyi

        // bal oldali lánc: b-1, b-2, ... szigorúan csökkenő magasságokkal
        xs.clear();
        sx.assign(1, 0);
        for (int a = 1; b - a >= 1; ++a) {
            int v = L[b - a];
            int prev = (a == 1) ? base : xs.back();
            if (v >= prev || sx.back() + v > budget) break;
            xs.push_back(v);
            sx.push_back(sx.back() + v);
        }
        const int VL = (int)xs.size();

        // jobb oldali lánc: b+1, b+2, ... szigorúan csökkenő magasságokkal
        ys.clear();
        sy.assign(1, 0);
        for (int c = 1; b + c <= N; ++c) {
            int v = L[b + c];
            int prev = (c == 1) ? base : ys.back();
            if (v >= prev || sy.back() + v > budget) break;
            ys.push_back(v);
            sy.push_back(sy.back() + v);
        }
        const int VR = (int)ys.size();

        // fval[a]: a bal oldali a láda mozgatásakor az alapok száma R[b-1-a] + 1
        fval.assign(VL + 1, INF);
        for (int a = 0; a <= VL; ++a) {
            int x = b - 1 - a;
            if (R[x] < INF) fval[a] = R[x] + 1;
        }

        // G[c]: a legkevesebb alapszám, ha b jobb oldalán c láda mozog
        G.assign(VR + 1, INF);
        for (int a = 0; a <= VL; ++a) {
            if (a >= 1) mark[xs[a - 1]] = b;
            if (fval[a] >= INF) continue;
            for (int c = 0; c <= VR; ++c) {
                if (sx[a] + sy[c] > budget) break;
                if (c >= 1 && mark[ys[c - 1]] == b) break;  // közös magasság: nagyobb c sem jó
                G[c] = min(G[c], fval[a]);
            }
        }

        for (int c = 0; c <= VR; ++c) {
            if (G[c] < INF) R[b + c] = min(R[b + c], G[c]);
        }
    }

    cout << N - R[N] << '\n';
    return 0;
}
