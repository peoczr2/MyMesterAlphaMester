/*
Megoldás lényege:
Egy járat haszna Ádámnak −C, ahol C a járat ára (negatív árnál Ádám keres, pozitívnál fizet). A maximális haszon tehát
a legkisebb összköltségű L→E útvonal ellentettje. Mivel az élek költsége negatív is lehet, Dijkstra nem használható,
viszont a feladat garantálja, hogy nincs negatív összköltségű kör, ezért a Bellman–Ford-algoritmus helyes: legfeljebb N−1
körben minden éllel frissítjük a távolságokat, és a szülőtömbből visszakövetve megkapjuk az útvonalat.
Az idő O(N·M), ami N ≤ 1000 és M ≤ 100 000 mellett az 1 mp-es korláton belül van, a korai leállás miatt gyakran jóval kevesebb.
*/
/*
Hint 1: || Fordítsd meg a gondolkodást: egy járat haszna a −C szám, így a maximális haszon a legkisebb összköltségű útvonal ellentettje. ||
Hint 2: || Negatív élek miatt Dijkstra nem jó, de a Bellman–Ford algoritmus igen: ismételten frissítsd minden járattal a célállomások távolságát, és jegyezd fel minden csúcs elődjét az útvonal visszakereséséhez. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Bus {
    int from, to;
    long long cost;
};

int main() {
    int n, m;
    cin >> n >> m;
    vector<Bus> buses(m);
    for (auto& bus : buses) cin >> bus.from >> bus.to >> bus.cost;
    int L, E;
    cin >> L >> E;

    const long long INF = LLONG_MAX / 4;
    vector<long long> d(n + 1, INF);
    vector<int> par(n + 1, 0);
    d[L] = 0;
    for (int it = 0; it < n - 1; it++) {
        bool changed = false;
        for (const Bus& bus : buses) {
            if (d[bus.from] < INF && d[bus.from] + bus.cost < d[bus.to]) {
                d[bus.to] = d[bus.from] + bus.cost;
                par[bus.to] = bus.from;
                changed = true;
            }
        }
        if (!changed) break;
    }

    if (d[E] >= INF) { // nem érhető el, ez a feladatból nem következik, de ne menjünk végtelen ciklusba
        cout << 0 << "\n" << 0 << "\n";
        return 0;
    }

    cout << -d[E] << "\n";

    vector<int> path;
    int v = E;
    while (true) {
        path.push_back(v);
        if (v == L) break;
        v = par[v];
    }
    reverse(path.begin(), path.end());

    cout << path.size() << "\n";
    for (size_t i = 0; i < path.size(); i++) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << "\n";
    return 0;
}
