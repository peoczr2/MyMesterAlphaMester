/*
Megoldás lényege:
A menetrend minden nap ugyanaz, ezért egy járat indulási ideje az érkezési időtől függ: a legkorábbi olyan időpont kell, amely a járat napi indulási percével egyezik, és nem korábbi a T+60-nál (az induló városban nincs átszállási idő). Mivel később érkezve sosem indulhatunk korábban, a legkorábbi érkezés minden városba optimális részproblémaként kezelhető: Dijkstra-algoritmussal, ahol a csúcs értéke a legkorábbi érkezési idő. Egy járat érkezési ideje a várakozott indulás plusz a repülési idő, így a várakozás a napi (U − (T+60)) mod 1440 perc. Minden csúcsnál eltároljuk, melyik járattal érkeztünk, és a céltól visszafelé követve kapjuk az útvonalat. Az időigény O(M log N).
*/
/*
Hint 1: || Minden városba a legkorábbi érkezési időt keresd, és Dijkstra-algoritmust futtass ezzel az értékkel. Korábbi érkezés soha nem rontja a továbbjutást, mert a későbbi járatra várakozni lehet. ||
Hint 2: || Egy repülőtéren a T+60 időpont utáni első olyan időpontot keresd, amikor a járat indul: a várakozás (U − (T+60)) mod 1440 perc. Az induló városban viszont nincs átszállási idő, ott T=0 és az indulás azonnal lehetséges. ||
Hint 3: || Minden városhoz tárold azt a járatsorszámot, amellyel a legkorábban érkeztél. A céltól visszafelé haladva az induló városig követve megkapod az útvonalat, ezt fordítva írd ki a járatszámokkal együtt. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long DAY = 1440;
const long long TRANSFER = 60;

struct Flight {
    int from, to;
    long long dep, dur;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, c;
    cin >> n >> m;
    cin >> k >> c;

    // A járatokat 1-től számozzuk, így a sorszám közvetlenül a bemeneti sor sorszáma lesz.
    vector<Flight> fl(m + 1);
    vector<vector<int>> out(n + 1);
    for (int i = 1; i <= m; i++) {
        cin >> fl[i].from >> fl[i].to >> fl[i].dep >> fl[i].dur;
        out[fl[i].from].push_back(i);
    }

    const long long INF = LLONG_MAX / 4;
    vector<long long> arr(n + 1, INF);  // legkorábbi érkezési idő
    vector<int> via(n + 1, 0);          // az oda vezető járat sorszáma
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<>> pq;
    arr[k] = 0;
    pq.push({0, k});

    while (!pq.empty()) {
        auto [t, u] = pq.top();
        pq.pop();
        if (t != arr[u]) continue;
        if (u == c) break;

        // Az induló városban nincs átszállás, máshol legalább 60 perc kell.
        long long base = (u == k) ? t : t + TRANSFER;
        for (int id : out[u]) {
            const Flight &f = fl[id];
            long long wait = ((f.dep - base) % DAY + DAY) % DAY;
            long long a = base + wait + f.dur;
            if (a < arr[f.to]) {
                arr[f.to] = a;
                via[f.to] = id;
                pq.push({a, f.to});
            }
        }
    }

    if (arr[c] == INF) {
        cout << 0 << '\n';
        return 0;
    }

    vector<int> route;
    for (int v = c; v != k; v = fl[via[v]].from) {
        route.push_back(via[v]);
    }
    reverse(route.begin(), route.end());

    cout << arr[c] << '\n';
    cout << route.size();
    for (int id : route) cout << ' ' << id;
    cout << '\n';
    return 0;
}
