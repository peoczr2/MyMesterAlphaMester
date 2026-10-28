/*
Megoldás lényege: visszalépéses keresést (DFS) futtatunk a bejárati csomópontból. Minden lépésnél
csak olyan szomszédba megyünk, amelyet az aktuális úton még nem érintettünk, így minden csúcsot
legfeljebb egyszer látogatunk. Ha elérjük Árpád szobrát, egy utat találtunk, és a keresés az
ágon visszalép. A bejárt csúcsokat bitmaszkban tároljuk, a szomszédok bitenkénti műveletekkel
válogathatók ki. A párhuzamos utakat külön útnak számoljuk. Az időigény az utak számával arányos,
ezért sűrű gráfon, sok úttal lassabb lehet, de N ≤ 25 mellett ez a szokásos megoldás.
*/
/*
Hint 1: || Minden út egyszerű út, tehát a bejárt csúcsokat jelölni kell. ||
Hint 2: || A keresés a célcsúcs elérésénél egy útat számol. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n, m, b, a;
unsigned adj[26];   // adj[u]: u szomszédainak bitmaszkja
int mult[26][26];   // mult[u][v]: az u és v közötti utak száma

// v: az aktuális csúcs, used: az eddig érintett csúcsok bitmaszkja (benne v is)
long long dfs(int v, unsigned used) {
    long long res = 0;
    unsigned cand = adj[v] & ~used;
    while (cand) {
        int to = __builtin_ctz(cand);
        cand &= cand - 1;
        if (to == a) res += mult[v][to];
        else res += (long long)mult[v][to] * dfs(to, used | (1u << to));
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> b >> a;
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u] |= 1u << v;
        adj[v] |= 1u << u;
        ++mult[u][v];
        ++mult[v][u];
    }
    cout << dfs(b, 1u << b) << '\n';
    return 0;
}
