/*
Megoldás lényege:
Egy járat Ádámnak C forint fizetést jelent, ha C pozitív, és -C forint hasznot, ha C negatív, mert ekkor ő vezeti a buszt; így egy élnek a haszna -C. A feladat tehát a legnagyobb összegű L-ből E-be vezető út keresése a -C élsúlyokkal. Mivel nincs pozitív haszonú körutazás, a Bellman-Ford algoritmus (maximalizálásra) N-1 körben relaxálva megadja az optimumot, az előd-tömbből pedig az útvonal visszafejthető. Az időigény O(N*M), ami N=1000 és M=100000 mellett legfeljebb 10^8 egyszerű művelet. Az eredmény negatív is lehet: ekkor Ádámnak fizetnie kell, a legkisebb költség az eredmény mínusza.
*/
/*
Hint 1: || Egy járat Ádámnak -C hasznot jelent, így a feladat a legnagyobb összegű L-ből E-be vezető út keresése a -C élsúlyokkal. ||
Hint 2: || Mivel vannak negatív élsúlyok, a Dijkstra nem használható. N-1 körös Bellman-Ford relaxálás megadja az optimumot, és minden javításkor jegyezd meg az előző csúcsot, hogy E-ből visszafelé követve kirakhasd az útvonalat. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int a, b;
    long long w;  // Ádám haszna a járaton: -C
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<Edge> edges(m);
    for (auto& e : edges) {
        long long c;
        cin >> e.a >> e.b >> c;
        e.w = -c;
    }
    int s, t;
    cin >> s >> t;

    const long long NEG = LLONG_MIN / 4;
    vector<long long> best(n + 1, NEG);
    vector<int> pre(n + 1, 0);
    best[s] = 0;
    for (int it = 0; it < n - 1; it++) {
        bool changed = false;
        for (const Edge& e : edges) {
            if (best[e.a] == NEG) continue;
            if (best[e.a] + e.w > best[e.b]) {
                best[e.b] = best[e.a] + e.w;
                pre[e.b] = e.a;
                changed = true;
            }
        }
        if (!changed) break;
    }

    if (best[t] == NEG) return 0;  // a feladat szerint E elérhető L-ből

    vector<int> path;
    for (int v = t;;) {
        path.push_back(v);
        if (v == s || (int)path.size() > n) break;
        v = pre[v];
    }
    reverse(path.begin(), path.end());

    cout << best[t] << '\n';
    cout << path.size() << '\n';
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i] << (i + 1 < path.size() ? ' ' : '\n');
    }
    return 0;
}
