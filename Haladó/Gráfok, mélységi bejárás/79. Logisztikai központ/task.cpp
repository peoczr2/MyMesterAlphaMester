/*
Megoldás lényege:
A városok fát alkotnak, az utak súlya a menetidő, a távolság pedig az úton lévő súlyok összege. Fában bármely csúcsból a legtávolabbi csúcs egy átmérő-végpont (a legnagyobb távolságú csúcspár egyike), ezért elég két bejárás: az 1-es csúcsból megkeressük a legtávolabbi a csúcsot, majd az a-ból a legtávolabbi b csúcsot. Ekkor minden v csúcs excentricitása max(d(a,v), d(b,v)). Ennek minimumát keressük, és kiírjuk az összes olyan csúcsot, ahol ez a minimum van, növekvő sorrendben. A futási idő O(N), a bejárás veremmel történik, így 100 000 csúcsnál sincs rekurziós veszély.
*/
/*
Hint 1: || Fában a legtávolabbi csúcs mindig az átmérő egyik végpontja. Egy tetszőleges csúcsból indulva keress egy legtávolabbi csúcsot a, majd a-ból egy legtávolabbi b csúcsot. ||
Hint 2: || Számold ki a és b felé a távolságokat, és egy v csúcsra a legtávolabbi csúcs távolsága max(d_a(v), d_b(v)). Ez az érték a logisztikai központ lehetséges távolsága, a keresett T ennek a minimuma. ||
Hint 3: || A bejárást veremmel (iteratív DFS-sel) írd meg, és a minimum megkeresése után gyűjtsd ki a minimumot elérő csúcsokat indexük szerint növekvő sorrendben. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<pair<int, long long>>> adj;

vector<long long> distancesFrom(int src) {
    vector<long long> d(n + 1, -1);
    vector<int> st;
    d[src] = 0;
    st.push_back(src);
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (auto [v, w] : adj[u]) {
            if (d[v] == -1) {
                d[v] = d[u] + w;
                st.push_back(v);
            }
        }
    }
    return d;
}

int farthest(const vector<long long> &d) {
    int best = 1;
    for (int v = 1; v <= n; v++) {
        if (d[v] > d[best]) {
            best = v;
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.assign(n + 1, {});
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        long long c;
        cin >> a >> b >> c;
        adj[a].push_back({b, c});
        adj[b].push_back({a, c});
    }

    vector<long long> d1 = distancesFrom(1);
    int a = farthest(d1);
    vector<long long> da = distancesFrom(a);
    int b = farthest(da);
    vector<long long> db = distancesFrom(b);

    vector<long long> ecc(n + 1);
    long long best = LLONG_MAX;
    for (int v = 1; v <= n; v++) {
        ecc[v] = max(da[v], db[v]);
        best = min(best, ecc[v]);
    }

    vector<int> centers;
    for (int v = 1; v <= n; v++) {
        if (ecc[v] == best) {
            centers.push_back(v);
        }
    }

    cout << best << "\n";
    cout << centers.size() << "\n";
    for (size_t i = 0; i < centers.size(); i++) {
        if (i) {
            cout << ' ';
        }
        cout << centers[i];
    }
    cout << "\n";
    return 0;
}
