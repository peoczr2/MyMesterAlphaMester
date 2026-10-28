/*
Megoldás lényege:
A fát a T csúcsból gyökerezzük. Az egér az M-ből a T felé haladó úton (p_0 = M, ..., p_{k-1}) halad, és minden úton lévő csúcs azon gyermekeit, amelyek nem az úton vannak, Dumbonak egy lépéssel le kell zárnia, különben az egér bemehet. Egy mellékág W(v) értéke azt adja, mennyi plusz lépés kényszeríthető ki, ha az egér bemegy a v csúcsba: W(v) = (v gyermekeinek száma) + (a gyermekei W-értékei közül a második legnagyobb), levélre 0.
A p_i csúcs döntése előtt Dumbonak legfeljebb i+1 lépése van, ezért egy X küszöbnél nagyobb W-jű mellékágakat időben le kell zárnia: minden i-re a p_0..p_i csúcsok ilyen ágainak száma legyen legfeljebb i+1. A legkisebb ilyen X-et bináris kereséssel keressük, a válasz a mellékágak száma plusz X.
Az időigény O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Gyökerezd a fát a T csúcsban. Az egér az M-ből a T felé halad, és az út minden csúcsánál a nem az úton lévő gyermekeket Dumbonak le kell zárnia, különben az egér befordul egy mellékágba. Gondold végig, hogy ha az egér bemegy egy mellékágba, mennyi lépést kell Dumbónak tennie, mire visszajut az útra. ||
Hint 2: || Egy mellékág költségét a gyermekek száma és a gyermekek költségei határozzák meg: a második legnagyobb gyermek-költség adja a legrosszabb esetet, mert Dumbo az egyik legdrágább ágat le tudja zárni. A költségeket a fa alulról felfelé való bejárásával számold ki. ||
Hint 3: || Az i-edik úton lévő csúcsnál Dumbo legfeljebb i+1 lépést tett, így egy X-nél drágább mellékág legfeljebb csak az időben lezárt számú lehet. Keresd meg bináris kereséssel a legkisebb X-et, amelyre minden i-re a p_0..p_i csúcsok X-nél drágább mellékágainak száma legfeljebb i+1, a válasz a mellékágak száma plusz X. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t, m;
    cin >> n >> t >> m;
    vector<int> ea(max(0, n - 1)), eb(max(0, n - 1)), deg(n + 2, 0);
    for (int i = 0; i < n - 1; i++) {
        cin >> ea[i] >> eb[i];
        deg[ea[i]]++;
        deg[eb[i]]++;
    }
    if (m == t) {
        cout << 0 << '\n';
        return 0;
    }

    // Szomszédsági lista (CSR): a v csúcs szomszédai adj[start[v] .. start[v+1]-1].
    vector<int> start(n + 2, 0);
    for (int v = 1; v <= n; v++) start[v + 1] = start[v] + deg[v];
    vector<int> adj(2 * max(0, n - 1));
    vector<int> pos(start.begin(), start.end());
    for (int i = 0; i < n - 1; i++) {
        adj[pos[ea[i]]++] = eb[i];
        adj[pos[eb[i]]++] = ea[i];
    }

    // BFS a T gyökérből: szülők és bejárási sorrend.
    vector<int> par(n + 1, 0), order;
    order.reserve(n);
    vector<char> vis(n + 1, 0);
    order.push_back(t);
    vis[t] = 1;
    for (size_t h = 0; h < order.size(); h++) {
        int v = order[h];
        for (int j = start[v]; j < start[v + 1]; j++) {
            int w = adj[j];
            if (!vis[w]) {
                vis[w] = 1;
                par[w] = v;
                order.push_back(w);
            }
        }
    }

    // W(v) = gyermekek száma + a gyermekek W-értékeinek második legnagyobbika (levélre 0).
    vector<int> W(n + 1, 0);
    for (int h = (int)order.size() - 1; h >= 0; h--) {
        int v = order[h];
        int mx1 = 0, mx2 = 0, cnt = 0;
        for (int j = start[v]; j < start[v + 1]; j++) {
            int u = adj[j];
            if (u == par[v]) continue;
            cnt++;
            int w = W[u];
            if (w > mx1) {
                mx2 = mx1;
                mx1 = w;
            } else if (w > mx2) {
                mx2 = w;
            }
        }
        W[v] = cnt + mx2;
    }

    // Az M -> T út csúcsai: path[0] = M, ..., path[k-1] (T nélkül).
    vector<int> path;
    for (int v = m; v != t; v = par[v]) path.push_back(v);
    int k = (int)path.size();

    // Igaz, ha az X-nél drágább mellékágak időben lezárhatók.
    auto feasible = [&](int X) -> bool {
        long long cum = 0;
        for (int i = 0; i < k; i++) {
            int v = path[i];
            int prev = (i > 0) ? path[i - 1] : 0;
            for (int j = start[v]; j < start[v + 1]; j++) {
                int u = adj[j];
                if (u == par[v] || u == prev) continue;
                if (W[u] > X) cum++;
            }
            if (cum > i + 1) return false;
        }
        return true;
    };

    int lo = 0, hi = n; // hi biztosan elérhető, mert W(v) <= n
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (feasible(mid)) hi = mid;
        else lo = mid + 1;
    }

    // A mellékágak száma: minden úton lévő csúcs szomszédai a szülőn és az úton lévő gyermeken kívül.
    long long base = 0;
    for (int i = 0; i < k; i++) {
        int v = path[i];
        base += deg[v] - 1 - (i > 0 ? 1 : 0);
    }

    cout << base + lo << '\n';
    return 0;
}
