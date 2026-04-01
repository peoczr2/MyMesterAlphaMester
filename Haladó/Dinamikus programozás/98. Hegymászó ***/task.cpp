/*
Megoldási ötlet:
A hegymászó a táborok mentén balról jobbra halad, és egy megállásnál legfeljebb annyi élelmet vehet fel, hogy a hátizsák tartalma ne
haladja meg a H kapacitást. Mivel a megállások számát minimalizáljuk, egy állapotot elég a „melyik tábor után járunk” és a távozáskori
hátizsáktartalom párral leírni.

Legyen dp[i][f] a minimális megállásszám, ha az i. táborból f egységnyi élelemmel indulunk tovább. Egy táborban vagy nem állunk meg,
vagy megállunk, és ilyenkor optimálisan mindig annyit veszünk fel, amennyit csak lehet: min(H, jelenlegi + M_i). Innen a következő
táborig vagy a csúcsig egyszerűen levonjuk az úthosszt. A szülőállapotokból visszaállítható a választott megálláslista.
*/
/*
Hint 1: || Egy állomásnál a megállás után sosem érdemes kevesebbet felvenni a maximumnál. ||
Hint 2: || Így az egyetlen kérdés: megállsz-e itt, vagy nem. ||
Hint 3: || A kapacitás kicsi, ezért a tábor sorszáma és a maradék élelem jó DP-állapot. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const uint16_t INF = 60000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t, cap;
    cin >> n >> t >> cap;
    vector<int> dist(n + 1), food(n + 1);
    for (int i = 1; i <= n; ++i) cin >> dist[i] >> food[i];

    int width = cap + 1;
    auto idx = [width](int i, int fuel) {
        return i * width + fuel;
    };

    vector<uint16_t> best((n + 1) * width, INF);
    vector<uint16_t> parentFuel((n + 1) * width, 0);
    vector<char> action((n + 1) * width, 0);

    vector<uint16_t> arrive(width, INF), nextArrive(width, INF);
    arrive[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int f = 0; f <= cap; ++f) best[idx(i, f)] = INF;

        for (int f = 0; f <= cap; ++f) {
            if (arrive[f] == INF) continue;

            int id1 = idx(i, f);
            if (arrive[f] < best[id1]) {
                best[id1] = arrive[f];
                parentFuel[id1] = static_cast<uint16_t>(f);
                action[id1] = 0;
            }

            int nf = min(cap, f + food[i]);
            int id2 = idx(i, nf);
            if (arrive[f] + 1 < best[id2]) {
                best[id2] = arrive[f] + 1;
                parentFuel[id2] = static_cast<uint16_t>(f);
                action[id2] = 1;
            }
        }

        if (i == n) break;

        fill(nextArrive.begin(), nextArrive.end(), INF);
        int need = dist[i + 1] - dist[i];
        for (int f = need; f <= cap; ++f) {
            uint16_t cur = best[idx(i, f)];
            if (cur == INF) continue;
            int rem = f - need;
            nextArrive[rem] = min(nextArrive[rem], cur);
        }
        arrive.swap(nextArrive);
    }

    int needToTop = t - dist[n];
    uint16_t bestStops = INF;
    int bestFuel = -1;
    for (int f = max(0, needToTop); f <= cap; ++f) {
        uint16_t cur = best[idx(n, f)];
        if (cur < bestStops) {
            bestStops = cur;
            bestFuel = f;
        }
    }

    vector<int> stops;
    int curFuel = bestFuel;
    for (int i = n; i >= 1; --i) {
        int id = idx(i, curFuel);
        int arriveFuel = parentFuel[id];
        if (action[id]) stops.push_back(i);
        if (i > 1) {
            curFuel = arriveFuel + (dist[i] - dist[i - 1]);
        }
    }
    reverse(stops.begin(), stops.end());

    cout << bestStops << '\n';
    for (int i = 0; i < (int)stops.size(); ++i) {
        if (i) cout << ' ';
        cout << stops[i];
    }
    cout << '\n';
    return 0;
}