/*
Megoldás lényege:
A vágások után az A-rész mindig összefüggő marad, és a végén pontosan N/2 csúcsot tartalmaz. Minden vágás egyetlen élt szüntet meg, ezért a vágások száma az A-rész határán lévő élek számával egyezik, így a feladat olyan N/2 csúcsú összefüggő részfa keresése, amelynek a határ-éleinek száma minimális. A fát az 1. csúcsból gyökerezzük, és minden v csúcsra DP-vel számoljuk: f[v][k] az a minimális határ-élszám, ha v a részfa legfelső csúcsa, és az A-rész k csúcsú a v részfájában. A gyerekek összevonása zsákprobléma-szerű: egy gyerek kizárása 1 vágás, a bevétele j csúcsnyi részfát jelent. Az egész O(N^2), ami N <= 4000 mellett bőven belefér. A válasz min_v (f[v][N/2] + 1), ha v nem a gyökér, különben f[1][N/2].
*/
/*
Hint 1: || Figyeld meg, hogy az A-rész végig összefüggő marad, és minden vágás pontosan egy élt szüntet meg. A végső A-rész tehát egy N/2 csúcsú összefüggő részfa, a vágások száma pedig a részfa határán lévő élek száma. ||
Hint 2: || Gyökerezd a fát az 1. csúcsnál. Minden v csúcsra DP-vel számold ki, hogy ha v az A-rész legfelső csúcsa és az A-rész k csúcsú, akkor legkevesebb hány határ-él kell a v részfájában. Egy gyereket vagy kizársz (+1 vágás), vagy beveszel a részfájából j csúcsot a megfelelő DP-érték szerint. ||
Hint 3: || A válasz min(f[v][N/2] + 1) a nem gyökér v csúcsokra, és f[1][N/2] a gyökérre. A gyerekek tömbjeit az összevonás után szabadítsd fel, hogy a memória is kicsi maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // BFS a gyökérből: a feldolgozás sorrendjében a gyerekek a szülő előtt jönnek
    vector<int> order, par(n + 1, 0);
    vector<bool> seen(n + 1, false);
    order.push_back(1);
    seen[1] = true;
    for (size_t i = 0; i < order.size(); i++) {
        int v = order[i];
        for (int u : adj[v]) {
            if (!seen[u]) {
                seen[u] = true;
                par[u] = v;
                order.push_back(u);
            }
        }
    }

    const int INF = 1e9;
    const int half = n / 2;
    vector<vector<int>> f(n + 1);  // f[v][k], k = 1..méret(v)
    int best = INF;

    for (int idx = n - 1; idx >= 0; idx--) {
        int v = order[idx];
        vector<int> cur(2, INF);
        cur[1] = 0;  // csak v van az A-ban, még nincs gyerek
        for (int c : adj[v]) {
            if (c == par[v]) continue;
            const vector<int>& fc = f[c];
            int sc = (int)fc.size() - 1;
            vector<int> nxt(cur.size() + sc, INF);
            for (int k = 1; k < (int)cur.size(); k++) {
                if (cur[k] >= INF) continue;
                // a c gyerek kimarad az A-ból: a v-c él vágás
                nxt[k] = min(nxt[k], cur[k] + 1);
                // a c gyerek bekerül: j csúcs a c részfájából
                for (int j = 1; j <= sc; j++) {
                    if (fc[j] >= INF) continue;
                    nxt[k + j] = min(nxt[k + j], cur[k] + fc[j]);
                }
            }
            cur.swap(nxt);
            vector<int>().swap(f[c]);
        }
        f[v] = move(cur);
        if (half < (int)f[v].size() && f[v][half] < INF) {
            int cand = f[v][half] + (v != 1 ? 1 : 0);  // v fölötti él is határ, ha v nem gyökér
            best = min(best, cand);
        }
    }

    cout << best << '\n';
    return 0;
}
