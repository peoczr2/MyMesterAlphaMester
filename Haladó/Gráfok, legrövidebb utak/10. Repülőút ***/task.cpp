/*
Megoldás lényege:
A járatok minden nap ugyanabban az időpontban indulnak, és várakozni bármelyik reptéren lehet, ezért a legkorábbi érkezési idő szerinti Dijkstra-algoritmus helyes: korábbi érkezésből sosem lesz későbbi indulás, így a legkorábbi érkezés mindig a legjobb. Egy T időben érkezett csúcsból a következő járat a T+60 perc utáni első olyan indulás, amelynek napon belüli ideje a járat U értéke; ezt a T+60 percen belüli maradékból (mod 1440) számoljuk ki. A kiindulási városban nincs átszállás, ott az időt 0-tól kezdjük. Az N≤10000 csúcsú és M≤200000 élű gráfon a Dijkstra O(M log N) időben fut, a visszafelé követett előző járatokból kapjuk a járatok sorszámait.
*/
/*
Hint 1: || Mivel a járatok minden nap ugyanabban az időpontban indulnak, egy adott érkezési időből a következő indulás kiszámolható az érkezési idő 1440-es maradéka alapján. ||
Hint 2: || Futtass Dijkstra-algoritmust úgy, hogy a csúcs távolsága a legkorábbi érkezési idő legyen; a 60 perces átszállási időt csak a kiindulási várostól különböző csúcsoknál vedd figyelembe. ||
Hint 3: || Minden csúcshoz tárold azt a járatot, amellyel a legkorábbi érkezés született, és a célból visszafelé haladva kapod a járatok sorszámát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, c;
    cin >> n >> m >> k >> c;
    vector<int> from(m + 1), to(m + 1), dep(m + 1), dur(m + 1);
    vector<vector<int>> out(n + 1);
    for (int i = 1; i <= m; i++) {
        cin >> from[i] >> to[i] >> dep[i] >> dur[i];
        out[from[i]].push_back(i);
    }

    const int INF = INT_MAX;
    vector<int> dist(n + 1, INF), prevFlight(n + 1, 0);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    dist[k] = 0;
    pq.push({0, k});
    while (!pq.empty()) {
        auto [t, x] = pq.top();
        pq.pop();
        if (t != dist[x]) continue;
        // a kiindulási városban nincs átszállás, máshol legalább 60 perc kell
        int need = (x == k) ? t : t + 60;
        for (int i : out[x]) {
            int wait = (dep[i] - need % 1440 + 1440) % 1440;
            int arrive = need + wait + dur[i];
            if (arrive < dist[to[i]]) {
                dist[to[i]] = arrive;
                prevFlight[to[i]] = i;
                pq.push({arrive, to[i]});
            }
        }
    }

    if (dist[c] == INF) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> route;
    for (int x = c; x != k; x = from[prevFlight[x]]) {
        route.push_back(prevFlight[x]);
    }
    reverse(route.begin(), route.end());

    cout << dist[c] << '\n';
    cout << route.size();
    for (int i : route) cout << ' ' << i;
    cout << '\n';
    return 0;
}
