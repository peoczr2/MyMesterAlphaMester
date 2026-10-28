/*
Megoldás lényege:
Az ajánlatok közül mindig a minimális feszítőerdőt kell üzemeltetni: így a működtetés a lehető legolcsóbb, és minden
összeköthető épület továbbra is elérhető marad. Minden új ajánlatnál először a régi, ugyanarra a párra vonatkozó él
szűnik meg, ha az üzemel. Ezután, ha az új él két olyan épületet köt össze, amelyek már összeköttetésben vannak,
megkeressük a köztük lévő úton a legdrágább élt; ha az drágább az újnál, kicseréljük. Ha nincs út, az új élt
egyszerűen üzembe állítjuk. Minden ajánlatra egy bejárás elég, így az időigény O(N) ajánlatonként.
*/
/*
Hint 1: || Mindig a legolcsóbb, mégis mindenkit összekötő élhalmazt tartsd fenn. Ha egy új él két már összekötött épületet köt össze, a körben a legdrágább élt kell elhagyni, ha az drágább az újnál. ||
Hint 2: || Az üzemelő éleket szomszédsági listában tárold, az egyes élek költségét pedig egy mátrixban. Az úton a legdrágább él megkereséséhez egy bejárás (DFS vagy BFS) az erdőben elég. ||
Hint 3: || Ha ugyanarra a párra olcsóbb ajánlat jön, a régi élt előbb az elvesz eljárással kell megszüntetni, és csak utána az újat a hozzaad eljárással üzembe állítani. ||
*/
#include "halo.h"
#include <bits/stdc++.h>
using namespace std;

int n;
int w[1001][1001];       // a pár aktuális ajánlatának költsége
bool inF[1001][1001];    // üzemel-e a kapcsolat
vector<int> adj[1001];   // az üzemelő kapcsolatok szomszédsága

void addEdge(int a, int b) {
    inF[a][b] = inF[b][a] = true;
    adj[a].push_back(b);
    adj[b].push_back(a);
    hozzaad(a, b);
}

void removeEdge(int a, int b) {
    inF[a][b] = inF[b][a] = false;
    adj[a].erase(find(adj[a].begin(), adj[a].end(), b));
    adj[b].erase(find(adj[b].begin(), adj[b].end(), a));
    elvesz(a, b);
}

// Bejárás az üzemelő erdőben a-tól b felé. Ha van út, a legdrágább élét (mx, my) adja vissza.
bool findMaxEdge(int a, int b, int &mx, int &my) {
    vector<int> par(n + 1, -1);
    vector<int> st = {a};
    par[a] = a;
    while (!st.empty()) {
        int u = st.back();
        st.pop_back();
        for (int v : adj[u]) {
            if (par[v] == -1) {
                par[v] = u;
                st.push_back(v);
            }
        }
    }
    if (par[b] == -1) return false;
    bool first = true;
    for (int v = b; v != a; v = par[v]) {
        int u = par[v];
        if (first || w[u][v] > w[mx][my]) {
            mx = u;
            my = v;
            first = false;
        }
    }
    return true;
}

int main() {
    n = kezdet();
    while (true) {
        int a, b, c;
        ajanlat(a, b, c);  // a = 0 esetén a könyvtár befejezi a programot
        w[a][b] = w[b][a] = c;
        if (inF[a][b]) removeEdge(a, b);
        int mx = 0, my = 0;
        if (!findMaxEdge(a, b, mx, my)) {
            addEdge(a, b);
        } else if (w[mx][my] > c) {
            removeEdge(mx, my);
            addEdge(a, b);
        }
    }
    return 0;
}
