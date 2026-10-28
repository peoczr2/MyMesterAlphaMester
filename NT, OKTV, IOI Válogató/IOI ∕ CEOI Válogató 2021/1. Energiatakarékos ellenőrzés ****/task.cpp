/*
Megoldás lényege:
Gyökerezzük a fát az 1-es szobánál, Antal mélységi sorrendben járja be a részfákat. Jelölje D(v,k) a v részfa teljes bejárásának minimális energiáját, ha Antal v-ben áll, v lámpája ég, a részfán kívül még k lámpa ég (ezek minden lépésnél fogyasztanak), és a bejárás végén Antal újra v-ben áll, v lámpája ég, a részfa többi lámpája pedig le van kapcsolva. Egy v-beli gyerek d részfájára két módszer van. (1) „Marad”: v lámpája égve marad, Antal bemegy d-be, felkapcsolja a lámpáját és bejár: 2(k+1) + D(d,k+1). (2) „Viszi a fényt”: bemegy d-be, felkapcsol, visszalép v-be, ott lekapcsolja a v lámpáját, újra bemegy (3k+4 energia), bejárja a részfát D(d,k) áron, majd visszalép v-be, felkapcsolja, d-be lép, lekapcsolja d-t, és visszalép v-be (újabb 3k+4): összesen 6k+8 + D(d,k). Levél gyerek költsége 2(k+1). D(v,k) a gyerekek költségének összege; a válasz D(1,0). Hasznos k legfeljebb 2 (a „marad” csak kicsi részfáknál éri meg), ezért elég k = 0..3 értéket tárolni. Időigény O(N).
*/
/*
Hint 1: || Ha minden szülő lámpája égve marad, a lépések költsége a mélységgel nő (négyzetes lesz). Érdemes a „fényt” továbbvinni: ha Antal d-ben van és d lámpája ég, a szülő szobája is látható, így a szülő lámpáját le lehet kapcsolni (de ehhez vissza kell lépni oda). ||
Hint 2: || Gyökerezd a fát az 1-esnél, és egy részfára számold ki: D(v,k) = a v részfa bejárásának minimális energiája, ha v lámpája ég az elején és a végén is, és a részfán kívül k lámpa ég (ezek is fogyasztanak minden lépésnél). Elég a k = 0, 1, 2 (3) értékeket tárolni. ||
Hint 3: || Egy d gyerekre két lehetőség van: a szülő lámpája égve marad (2(k+1) + D(d,k+1)), vagy a lámpát átviszed d-be, bejárod, majd visszahozod (6k+8 + D(d,k)). A levélgyerek költsége 2(k+1). Vedd mindig a kisebbet, és add össze a gyerekekre. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    const int K = 3;

    // szülők és bejárási sorrend (BFS), hogy ne legyen mély rekurzió
    vector<int> par(n, -1), order;
    order.reserve(n);
    vector<char> seen(n, 0);
    order.push_back(0);
    seen[0] = 1;
    for (size_t i = 0; i < order.size(); i++) {
        int u = order[i];
        for (int w : adj[u]) {
            if (!seen[w]) {
                seen[w] = 1;
                par[w] = u;
                order.push_back(w);
            }
        }
    }

    vector<array<long long, K + 1>> D(n);
    for (auto &a : D) a.fill(0);
    vector<int> children(n, 0);
    for (int v = 1; v < n; v++) children[par[v]]++;

    for (int i = n - 1; i >= 1; i--) {
        int v = order[i];
        int p = par[v];
        for (int k = 0; k <= K; k++) {
            long long cost;
            if (children[v] == 0) {
                cost = 2LL * (k + 1);
            } else {
                cost = 6LL * k + 8 + D[v][k];  // a fényt átvisszük v-be és vissza
                if (k + 1 <= K) cost = min(cost, 2LL * (k + 1) + D[v][k + 1]);  // a szülő lámpája égve marad
            }
            D[p][k] += cost;
        }
    }

    cout << D[0][0] << '\n';
    return 0;
}
