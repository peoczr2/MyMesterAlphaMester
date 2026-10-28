/*
Megoldás lényege:
Az ismeretségek többszörös gráfot alkotnak, a csoportok száma a gráf komponenseinek száma. Ezt egy feszítőerdővel
tartjuk nyilván: a feszítőerdő élei a fa-élek, a többi példány nem fa-él. Felvételkor, ha a két ember már összefügg
az erdőben, az új él nem fa-él lesz, különben fa-él lesz és a csoportok száma eggyel csökken. Törléskor, ha a törölt
pár fa-él és nincs más példánya, a fa két részre esik szét; ha van olyan nem fa-él, amely a két részt összeköti,
azt fa-élre cseréljük, különben a csoportok száma eggyel nő. Minden műveletre egy bejárás (O(N)) elég, a csere
keresése bitset-ekkel gyors.
*/
/*
Hint 1: || Egy törlés után nem mindig változik a csoportok száma: ha az élnek van másik példánya, vagy nem része a feszítőerdőnek, a szám ugyanaz marad. Csak a fa-él törlése igényel további vizsgálatot. ||
Hint 2: || Tartsd nyilván a feszítőerdő éleit és a nem fa-éleket is. Fa-él törlésekor keresd meg azt a nem fa-élet, amely a két keletkező részt köti össze: ha van, cseréld fa-élre, ha nincs, a csoportok száma eggyel nő. ||
Hint 3: || Új ismeretség akkor lesz fa-él, ha a két ember az erdőben még nincs összekötve; ezt egy bejárással lehet ellenőrizni. N ≤ 1000, így minden műveletre az O(N) bejárás belefér az 1 másodperces időlimitbe. ||
*/
#include "ismer.h"
#include <bits/stdc++.h>
using namespace std;

const int MX = 1001;

int n;
int mult[MX][MX];         // a két ember közötti ismeretségek száma
bool inT[MX][MX];         // a pár feszítőerdő-él-e
bitset<MX> nt[MX];        // nt[x][y]: van-e x és y között nem fa-él
vector<int> adj[MX];      // a feszítőerdő szomszédsága
int comps;                // a csoportok száma

void refresh(int x, int y) {
    bool has = mult[x][y] - (inT[x][y] ? 1 : 0) > 0;
    nt[x].set(y, has);
    nt[y].set(x, has);
}

// Bejárás a feszítőerdőben s-ből: a bejárt csúcsok jelölése.
vector<char> reach(int s) {
    vector<char> vis(n + 1, 0);
    vector<int> st = {s};
    vis[s] = 1;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (int v : adj[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                st.push_back(v);
            }
        }
    }
    return vis;
}

void addTree(int x, int y) {
    inT[x][y] = inT[y][x] = true;
    adj[x].push_back(y);
    adj[y].push_back(x);
    comps--;
    refresh(x, y);
}

void removeTree(int x, int y) {
    inT[x][y] = inT[y][x] = false;
    adj[x].erase(find(adj[x].begin(), adj[x].end(), y));
    adj[y].erase(find(adj[y].begin(), adj[y].end(), x));
    comps++;
}

int main() {
    n = kezdet();
    comps = n;
    while (true) {
        char op;
        int a, b;
        muvelet(op, a, b);  // 'v' esetén a könyvtár befejezi a programot
        if (op == 'f') {
            mult[a][b]++;
            mult[b][a]++;
            if (!reach(a)[b]) {
                addTree(a, b);
            } else {
                refresh(a, b);
            }
        } else {
            if (mult[a][b] == 0) {
                // nincs ilyen ismeretség, nincs változás
            } else if (inT[a][b] && mult[a][b] == 1) {
                mult[a][b] = mult[b][a] = 0;
                removeTree(a, b);
                refresh(a, b);
                vector<char> inA = reach(a);
                bitset<MX> notA;
                for (int v = 1; v <= n; v++)
                    if (!inA[v]) notA.set(v);
                for (int u = 1; u <= n; u++) {
                    if (!inA[u]) continue;
                    bitset<MX> cand = nt[u] & notA;
                    if (cand.any()) {
                        int v = 1;
                        while (!cand[v]) v++;
                        addTree(u, v);  // a csere miatt a csoportszám nem változik
                        break;
                    }
                }
            } else {
                mult[a][b]--;
                mult[b][a]--;
                refresh(a, b);
            }
        }
        csoport(comps);
    }
    return 0;
}
