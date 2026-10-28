/*
Megoldás lényege:
Ha Jerry egy szobornál leejt egy kenyeret, a szomszédos szobrok galambjai oda gyűlnek, ezért
Tom és Jerry különbsége egy leejtésre csak a szoborhoz és az útvonalon megelőző szoborhoz
kapcsolódik: a v szobor leejtése c_v - p_u értéket ad, ahol c_v a v szomszédainak galambjainak
összege, u pedig az útvonalon v előtt álló szobor (kezdőszobornál c_v). Egy adott úton így a
legfeljebb V legnagyobb ilyen érték összege a válasz. Az optimális utat fa-DP-vel keressük:
gyökerezett fán minden csúcsra tároljuk a felfelé és a lefelé haladó láncok 0..V kenyérre
vonatkozó legjobb értékeit, és a legmagasabb csúcsban két különböző gyermekágat kombinálunk.
A kombinálás a tömbök monotonitása miatt O(V) időben elvégezhető, így az összidő O(N*V).
*/
/*
Hint 1: || Figyeld meg, hogy egy leejtés hatása csak a szobor és az útvonalon közvetlenül előtte álló szobor galambjaitól függ, a többi szobor galambjai nem számítanak. ||
Hint 2: || Ha c_v a v szomszédainak galambösszege, akkor az útvonalon v-t megelőző u szoborral a v-nél leejtett kenyér értéke c_v - p_u, a kezdőszobornál pedig c_v. Egy útvonal értéke így a legfeljebb V legnagyobb ilyen érték összege, és a válasz az összes útvonal maximuma. ||
Hint 3: || Gyökerezd a fát. Minden csúcsra számold ki, hogy a csúcs felé és a csúcsból lefelé haladó láncok legjobb értéke hány kenyérrel mennyi (0..V). A legmagasabb csúcsban két különböző gyermekág láncait úgy kombináld, hogy a prefixum-maximumok és a monotonitás miatt elég O(V) lépés. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, V;
    cin >> n >> V;
    vector<ll> p(n + 1, 0);
    for (int i = 1; i <= n; i++) cin >> p[i];
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    vector<ll> c(n + 1, 0);
    for (int v = 1; v <= n; v++)
        for (int u : adj[v]) c[v] += p[u];

    vector<int> par(n + 1, 0), order;
    order.reserve(n);
    vector<char> vis(n + 1, 0);
    order.push_back(1);
    vis[1] = 1;
    for (size_t i = 0; i < order.size(); i++) {
        int v = order[i];
        for (int u : adj[v])
            if (!vis[u]) {
                vis[u] = 1;
                par[u] = v;
                order.push_back(u);
            }
    }

    const int K = V + 1;
    vector<ll> U((size_t)(n + 1) * K, 0), D((size_t)(n + 1) * K, 0);
    vector<ll> PU(K), PD(K), W(K);
    ll ans = 0;

    for (int idx = n - 1; idx >= 0; idx--) {
        int t = order[idx];
        for (int j = 0; j < K; j++) {
            PU[j] = j >= 1 ? max(0LL, c[t]) : 0LL;
            PD[j] = 0;
        }
        for (int u : adj[t]) {
            if (u == par[t]) continue;
            ll wt = c[t] - p[u];
            const ll *Uu = &U[(size_t)u * K];
            const ll *Du = &D[(size_t)u * K];
            W[0] = Uu[0];
            for (int j = 1; j < K; j++) W[j] = max(Uu[j], Uu[j - 1] + wt);
            for (int j = 0; j < K; j++) ans = max(ans, PU[j] + Du[V - j]);
            for (int j = 0; j < K; j++) ans = max(ans, W[j] + PD[V - j]);
            for (int j = 0; j < K; j++) {
                PU[j] = max(PU[j], W[j]);
                PD[j] = max(PD[j], Du[j]);
            }
        }
        ans = max(ans, PU[V]);
        ll *Ut = &U[(size_t)t * K];
        for (int j = 0; j < K; j++) Ut[j] = PU[j];
        if (t != 1) {
            ll wd = c[t] - p[par[t]];
            ll *Dt = &D[(size_t)t * K];
            Dt[0] = PD[0];
            for (int j = 1; j < K; j++) Dt[j] = max(PD[j], PD[j - 1] + wd);
        }
    }
    cout << ans << "\n";
    return 0;
}
