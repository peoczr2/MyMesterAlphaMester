/*
Megoldás lényege: egy lépésben mindig két, értékben egymás melletti halom egyesül, a kisebb értékű halom költözik a nagyobbikba; így a halmok értékkészlete összefüggő szakasz, a halom helye pedig a benne lévő legnagyobb láda pozíciója. Két halom csak akkor egyesíthető, ha pozíció szerint is szomszédos, vagyis egy halom csúcsát pontosan akkor lehet törölni (egyesíteni a felette lévővel), ha a felette lévő halom csúcsa pozíció szerint is a szomszédja. Egy törölhető érték a többi törlés után is törölhető marad, ezért a törlések sorrendje tetszőleges: egy veremmel addig töröljük a törölhető értékeket, amíg lehet. Ha a végén csak az N maradt, a törlések sorrendje adja a N-1 műveletet, különben nincs megoldás; kétirányú láncolt listákkal az időigény O(N).
*/
/*
Hint 1: || Minden lépés két olyan halmot egyesít, amelyek értékkészlete egymás mellett van, a kisebb halom költözik a nagyobbikba. ||
Hint 2: || Két halom csak akkor egyesíthető, ha a köztük lévő pozíciókban nincs más nem üres hely, vagyis pozíció szerint is szomszédosak. ||
Hint 3: || Tartsd nyilván kétirányú láncolt listában az értékek és a pozíciók szerinti szomszédokat, és törlés után csak a szomszédok állapotát frissítsd. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N + 1), pos(N + 2, 0);
    for (int p = 1; p <= N; ++p) {
        cin >> a[p];
        pos[a[p]] = p;
    }

    // Értékek szerinti lista (az aktuális halmok alsó/felső szomszédai),
    // és pozíció szerinti lista (az aktuális nem üres helyek szomszédai).
    vector<int> vnext(N + 2, 0), vprev(N + 2, 0), pnext(N + 2, 0), pprev(N + 2, 0);
    for (int v = 1; v <= N; ++v) {
        vnext[v] = (v < N) ? v + 1 : 0;
        vprev[v] = (v > 1) ? v - 1 : 0;
    }
    for (int p = 1; p <= N; ++p) {
        pnext[a[p]] = (p < N) ? a[p + 1] : 0;
        pprev[a[p]] = (p > 1) ? a[p - 1] : 0;
    }

    vector<char> removed(N + 2, 0);
    vector<int> stk;
    for (int v = 1; v < N; ++v) stk.push_back(v);
    vector<pair<int, int>> moves;

    while (!stk.empty()) {
        int v = stk.back();
        stk.pop_back();
        if (removed[v]) continue;
        int w = vnext[v];
        if (w == 0) continue;                              // a legnagyobb halom nem mozgatható
        if (pnext[v] != w && pprev[v] != w) continue;      // a két halom nincs egymás mellett
        moves.push_back({pos[v], pos[w]});
        removed[v] = 1;

        int u = vprev[v];
        int L = pprev[v], R = pnext[v];
        if (u) {
            vnext[u] = w;
            stk.push_back(u);
        }
        vprev[w] = u;
        if (L) {
            pnext[L] = R;
            stk.push_back(L);
        }
        if (R) {
            pprev[R] = L;
            stk.push_back(R);
        }
    }

    if ((int)moves.size() != N - 1) {
        cout << "0 0\n";
        return 0;
    }
    for (auto [u, v] : moves) cout << u << ' ' << v << '\n';
    return 0;
}
