/*
Megoldás lényege:
Ha egy csatornát tetszőleges szélességűre kiszélesíthetünk, akkor az A-ból B-be vezető útvonalon a legkeskenyebb csatornát érdemes kiszélesíteni, így az útvonal értéke a második legkisebb csatornaszélesség lesz. Egy w szélesség akkor alkalmas, ha van olyan A-B út, amelyen legfeljebb egy csatorna keskenyebb w-nél. Ez a tulajdonság w növelésével egyre nehezebb lesz, ezért a legnagyobb alkalmas w bináris kereséssel megtalálható. Egy adott w-re a legkevesebb keskeny csatornát tartalmazó út 0-1 BFS-sel számolható ki: a w-nél keskenyebb csatorna költsége 1, a többié 0. A keresés O((N + M) log W) időben fut, ahol W = 10 000 a legnagyobb szélesség.
*/
/*
Hint 1: || Egy w szélességű hajó átjuthat az útvonalon, ha legfeljebb egy csatorna keskenyebb w-nél, mert azt a csatornát kiszélesítjük. Keresd a legnagyobb ilyen w-t. ||
Hint 2: || Bináris kereséssel válassz w-t, és minden lépésben számold ki 0-1 BFS-sel, hogy A-ból B-be legkevesebb hány keskeny csatornán keresztül lehet eljutni. A w-nél keskenyebb csatorna költsége 1, a többié 0. A w jó, ha B legfeljebb 1 költséggel elérhető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, a, b;
    cin >> n >> m >> a >> b;
    --a;
    --b;

    vector<int> eu(m), ev(m), ew(m);
    vector<int> off(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        cin >> eu[i] >> ev[i] >> ew[i];
        --eu[i];
        --ev[i];
        ++off[eu[i] + 1];
        ++off[ev[i] + 1];
    }
    for (int v = 0; v < n; ++v) off[v + 1] += off[v];

    // szomszédsági lista CSR formában
    vector<int> pos(off.begin(), off.end() - 1);
    vector<int> to(2 * m), wt(2 * m);
    for (int i = 0; i < m; ++i) {
        to[pos[eu[i]]] = ev[i];
        wt[pos[eu[i]]] = ew[i];
        ++pos[eu[i]];
        to[pos[ev[i]]] = eu[i];
        wt[pos[ev[i]]] = ew[i];
        ++pos[ev[i]];
    }

    const int INF = 1000000000;
    vector<int> dist(n);

    // igaz, ha van A-B út, amelyen legfeljebb egy w-nél keskenyebb csatorna van
    auto feasible = [&](int w) {
        fill(dist.begin(), dist.end(), INF);
        deque<int> dq;
        dist[a] = 0;
        dq.push_back(a);
        while (!dq.empty()) {
            int v = dq.front();
            dq.pop_front();
            for (int e = off[v]; e < off[v + 1]; ++e) {
                int u = to[e];
                bool narrow = wt[e] < w;
                int nd = dist[v] + (narrow ? 1 : 0);
                if (nd <= 1 && nd < dist[u]) {
                    dist[u] = nd;
                    if (narrow) dq.push_back(u);
                    else dq.push_front(u);
                }
            }
        }
        return dist[b] <= 1;
    };

    if (!feasible(1)) {
        cout << 0 << '\n';
        return 0;
    }

    int lo = 1, hi = 10000;
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
        if (feasible(mid)) lo = mid;
        else hi = mid - 1;
    }
    cout << lo << '\n';
    return 0;
}
