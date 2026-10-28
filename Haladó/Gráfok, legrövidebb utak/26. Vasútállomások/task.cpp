/*
Megoldás lényege:
Minden menetrendi elemet (vonat, megálló) egy csúcsnak tekintünk. Két csúcs-típust használunk: az A(e) jelentése "megérkeztem az e megállóba", a B(e) pedig "az e megállóban az adott vonaton állva indulok". A vonaton maradás (A(e) → B(e)) és a vonaton haladás (B(e) → A(következő megálló), a menetdíjjal) fix éleket adnak, az átszállás pedig az A(e) csúcsból azokra az B-csúcsokra mehet, amelyek ugyanabban az állomásban később indulnak. Az átszállásokat állomásonként, az indulási idő szerint rendezett láncon (várakozó csúcsokon) keresztül kezeljük, így az élek száma lineáris. Az 1. állomás minden indulása kezdő B-csúcs, 0 költséggel; a kezdő indulási időt a harmadik szempont (a legkésőbbi indulás) miatt tároljuk. Dijkstra-algoritmust futtatunk a (költség, -indulási idő) rendezett párral, így minden A-csúcsra a legkisebb költség és azon belül a legkésőbbi indulás marad meg. Végül állomásonként a legkisebb érkezési idő, azon belül a legkisebb költség, majd a legkésőbbi indulás a válasz. Az időigény O(E log E), ahol E ≤ 200 000 a menetrendi elemek száma.
*/
/*
Hint 1: || Egy menetrendi elem (vonat egy megállója) legyen csúcs, és két állapotot különböztess meg: megérkezés és a vonaton állva indulás. Az átszállás mindig egy megérkezési állapotból indul. ||
Hint 2: || Az átszállás csak olyan indulásra lehet, amely ugyanabban az állomásban később indul, mint ahova megérkeztél. Ezeket az indulásokat állomásonként időrendbe rendezve, egy "várakozó" láncon végigmenve kevés élből összerakható a gráf. ||
Hint 3: || Dijkstra-algoritmust futtass (költség, majd a kezdő indulás negáltja szerint), és a végeredményt állomásonként válogasd ki: előbb a legkorábbi érkezés, aztán a legkisebb költség, végül a legkésőbbi indulás. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Menetrendi elemek: a vonatok megállói egymás után, egy globális sorszámmal.
    vector<int> st, arr, dep, fare;
    vector<char> hasNext;
    for (int i = 0; i < m; i++) {
        int cnt;
        cin >> cnt;
        for (int j = 0; j < cnt; j++) {
            int s, a, d, f;
            cin >> s >> a >> d >> f;
            st.push_back(s);
            arr.push_back(a);
            dep.push_back(d);
            fare.push_back(f);
            hasNext.push_back(j + 1 < cnt);
        }
    }
    const int E = (int)st.size();

    // Az indulások állomásonként, indulási idő szerint rendezve (várakozó lánc).
    vector<int> order(E);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int x, int y) {
        if (st[x] != st[y]) return st[x] < st[y];
        return dep[x] < dep[y];
    });
    vector<int> depOrd(E), grpEnd(E);
    for (int p = 0; p < E; p++) depOrd[p] = dep[order[p]];
    // grpEnd[p]: az a állomás indulásainak (p-t tartalmazó csoport) vége (kizárva).
    for (int p = E - 1; p >= 0; p--) {
        if (p == E - 1 || st[order[p]] != st[order[p + 1]]) grpEnd[p] = p + 1;
        else grpEnd[p] = grpEnd[p + 1];
    }
    // posOfStart[s]: az s állomás első indulásának pozíciója (csak ha van ilyen).
    vector<int> posOfStart(n + 2, -1);
    for (int p = E - 1; p >= 0; p--) posOfStart[st[order[p]]] = p;

    // Csúcsok: A(e) = e, B(e) = E + e, várakozó W(p) = 2E + p.
    const ll INF = LLONG_MAX / 4;
    vector<ll> costOf(3 * (ll)E, INF), negDep(3 * (ll)E, 0);
    using Item = tuple<ll, ll, int>;  // (költség, -kezdő indulás, csúcs)
    priority_queue<Item, vector<Item>, greater<Item>> pq;

    auto relax = [&](int node, ll c, ll nd) {
        if (c < costOf[node] || (c == costOf[node] && nd < negDep[node])) {
            costOf[node] = c;
            negDep[node] = nd;
            pq.push({c, nd, node});
        }
    };

    // Kezdés: az 1. állomásról bármely vonat indulhat, költség 0, a kezdő indulás az indulási idő.
    for (int e = 0; e < E; e++) {
        if (st[e] == 1) relax(E + e, 0, -(ll)dep[e]);
    }

    while (!pq.empty()) {
        auto [c, nd, node] = pq.top();
        pq.pop();
        if (c != costOf[node] || nd != negDep[node]) continue;

        if (node < E) {
            // A(e): megérkeztem az e megállóba; maradhatok a vonaton, vagy átszállhatok.
            int e = node;
            relax(E + e, c, nd);
            int s = st[e];
            int lo = posOfStart[s];  // az állomás indulásainak kezdete (e miatt biztosan van)
            int hi = grpEnd[lo];
            // Első olyan indulás ugyanebben az állomásban, amely később van, mint az érkezés.
            int p = (int)(upper_bound(depOrd.begin() + lo, depOrd.begin() + hi, arr[e]) - depOrd.begin());
            if (p < hi) relax(2 * E + p, c, nd);
        } else if (node < 2 * E) {
            // B(e): a vonaton állva indulok; a következő megállóig utazom.
            int e = node - E;
            if (hasNext[e]) relax(e + 1, c + fare[e], nd);
        } else {
            // W(p): várakozás, a későbbi indulások felé lépek.
            int p = node - 2 * E;
            relax(E + order[p], c, nd);
            if (p + 1 < grpEnd[p]) relax(2 * E + p + 1, c, nd);
        }
    }

    // Állomásonként: legkorábbi érkezés, azon belül legkisebb költség, azon belül legkésőbbi indulás.
    vector<ll> bestT(n + 1, -1), bestC(n + 1, 0), bestD(n + 1, 0);
    for (int e = 0; e < E; e++) {
        if (costOf[e] >= INF) continue;
        int s = st[e];
        ll t = arr[e], c = costOf[e], d = -negDep[e];
        if (bestT[s] < 0 || t < bestT[s] || (t == bestT[s] && (c < bestC[s] || (c == bestC[s] && d > bestD[s])))) {
            bestT[s] = t;
            bestC[s] = c;
            bestD[s] = d;
        }
    }

    for (int s = 2; s <= n; s++) {
        if (bestT[s] < 0) cout << "0 0 0\n";
        else cout << bestT[s] << ' ' << bestC[s] << ' ' << bestD[s] << '\n';
    }
    return 0;
}
