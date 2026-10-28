/*
Megoldás lényege:
Ádám kék korongjai mindig egy összefüggő B halmazt alkotnak, amely tartalmazza az 1. pontot. Éva akkor zárja le a játékot, ha B minden szomszédját pirosra tette; ekkor a piros korongok száma pontosan |B|, így a végeredmény a legkisebb olyan összefüggő B (1 ∈ B), amelyre a B szomszédainak száma legfeljebb |B|.
Ilyen B-t két módon érdemes keresni, és a kettő közül a kisebb adja a választ. (1) Ha az 1. ponttól különböző, legfeljebb 2 szomszédú pont elérhető, a belőle az 1. pontba vezető BFS-út (pontok száma) jó: a fokszám-számolásból adódóan a határ már nem nagyobb, mint a terület. (2) Ha van olyan u pont (u ≠ 1), amelynek két szomszédja p és q, és u nélkül a p-t és q-t az 1. ponttal összekötő legkisebb fa mérete elég, akkor a határban u már csak egyszer számít, és a terület is jó. Ez a fa egy középső v pontból adódik: d(v,1)+d(v,p)+d(v,q)+1 minimuma, u kihagyásával számolva.
Az 1. pont mindig része a területnek, az egész összefüggő komponens pedig mindig megfelelő (határa üres), így ez a visszaesési érték. A keresést a levágások gyorsítják: csak az 1. ponthoz közeli u pontokat nézzük, mert a jelölt mérete legalább d(1,u). Az időigény O(N·(N+M)) legrosszabb esetben, ami N ≤ 1000 esetén belefér.
*/
/*
Hint 1: || Ádám területe az 1. pont köré összefüggően nő, és Éva akkor zárja le, ha a terület szomszédait mind pirosra tette: a piros korongok száma ekkor a terület méretével egyezik. Keresd a legkisebb ilyen összefüggő területet. ||
Hint 2: || Ha a területben van az 1. ponton kívül legfeljebb 2 szomszédú pont, a legrövidebb út odáig már elég; ezt BFS-sel kapod meg. Ha nincs ilyen, nézd meg, hogy van-e olyan u pont, amelynek két szomszédja a területbe fér. ||
Hint 3: || Egy ilyen u kihagyásával BFS-sel számold ki az 1., p és q pontokból a távolságokat; a három pontot összekötő legkisebb fa mérete min_v (d(v,1)+d(v,p)+d(v,q))+1, ahol v a három távolság összege által adott középső pont. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int INF = 1000000000;

int n;
vector<vector<int>> adj;
vector<int> qbuf;

// BFS a banned pont kihagyásával; a src-ből mért távolságokat a d tömbbe írja
void bfs(int src, int banned, vector<int> &d) {
    fill(d.begin(), d.end(), INF);
    int head = 0, tail = 0;
    d[src] = 0;
    qbuf[tail++] = src;
    while (head < tail) {
        int v = qbuf[head++];
        for (int u : adj[v]) {
            if (u == banned || d[u] != INF) continue;
            d[u] = d[v] + 1;
            qbuf[tail++] = u;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    adj.assign(n, {});
    for (int i = 0; i < n; i++) {
        int x;
        while (cin >> x && x != 0) {
            int j = x - 1;
            if (j < 0 || j >= n || j == i) continue;
            adj[i].push_back(j);
            adj[j].push_back(i);
        }
    }
    for (auto &lst : adj) {
        sort(lst.begin(), lst.end());
        lst.erase(unique(lst.begin(), lst.end()), lst.end());
    }

    qbuf.assign(n, 0);
    vector<int> d0(n), du(n), dp(n), dq(n);
    bfs(0, -1, d0);

    // a teljes összefüggő komponens határ nélkül is jó megoldás
    int best = 0;
    for (int v = 0; v < n; v++)
        if (d0[v] != INF) best++;

    // 1) legközelebbi, 2-nél kisebb fokszámú pont (az 1. ponttól különböző)
    for (int v = 1; v < n; v++)
        if (d0[v] != INF && adj[v].size() <= 2) best = min(best, d0[v] + 1);

    // 2) u kihagyásával, u két szomszédja p és q: legkisebb összekötő fa
    //    (a jelölt mérete legalább d0[u], ezért csak az 1.-hez közeli u-kat nézzük)
    for (int u = 1; u < n; u++) {
        if (d0[u] == INF || d0[u] >= best || adj[u].size() < 2) continue;
        bfs(0, u, du);
        for (size_t i = 0; i < adj[u].size(); i++) {
            for (size_t j = i + 1; j < adj[u].size(); j++) {
                int p = adj[u][i], q = adj[u][j];
                if (max(d0[p], d0[q]) + 1 >= best) continue;
                bfs(p, u, dp);
                bfs(q, u, dq);
                for (int v = 0; v < n; v++) {
                    if (v == u) continue;
                    if (du[v] == INF || dp[v] == INF || dq[v] == INF) continue;
                    best = min(best, du[v] + dp[v] + dq[v] + 1);
                }
            }
        }
    }

    cout << best << '\n';
    return 0;
}
