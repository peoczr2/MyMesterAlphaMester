/*
Megoldás lényege:
Minden zsákfaluból elindulunk az egyetlen úton, és csak két úttal rendelkező településeken haladunk
tovább, amíg el nem érünk egy elágazást (legalább három út) vagy másik zsákfalut. Az út éleinek
súlyát összegezzük: ez a zsákfaluhoz vezető elágazásmentes út hossza, és az A válasz a leghosszabb ilyen.
A B kérdésre a legtöbb úttal rendelkező települések (a fokszámok maximuma) adják a választ, minden
sorszámot növekvő sorrendben kiírva. A C kérdésnél egy település legközelebbi szomszédjának távolsága
a hozzá illeszkedő élek legkisebb súlya; ezek közül a legnagyobbat választjuk, egyenlőségnél a legkisebb
sorszámút. Az időigény O(N + M), mivel minden él legfeljebb egyszer kerül bejárásra.
*/
/*
Hint 1: || Egy zsákfalutól indulva kövesd az egyetlen utat: minden lépésnél a még nem járt szomszédot választod, és megállsz, ha olyan településhez érsz, ahonnan nem két út vezet tovább. ||
Hint 2: || A zsákfalutól az elágazásig tartó út hosszát az érintett élek súlyainak összegeként kapod meg; a B kérdésre a fokszámok maximumát keresd. ||
Hint 3: || A C kérdésben minden településhez számold ki a rá illeszkedő élek legkisebb súlyát, és azt a települést keresd, amelyiknek ez a szám a legnagyobb; egyenlőségnél a kisebb sorszám nyer. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, long long>>> g(n + 1);
    vector<int> fok(n + 1, 0);
    vector<long long> legkozelebbi(n + 1, LLONG_MAX);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        g[u].push_back({v, w});
        g[v].push_back({u, w});
        fok[u]++;
        fok[v]++;
        legkozelebbi[u] = min(legkozelebbi[u], w);
        legkozelebbi[v] = min(legkozelebbi[v], w);
    }

    // A: a zsákfalvakhoz vezető leghosszabb, elágazásmentes út hossza
    long long leghosszabbUt = 0;
    for (int z = 1; z <= n; z++) {
        if (fok[z] != 1) continue;
        long long hossz = g[z][0].second;
        int elozo = z, aktualis = g[z][0].first;
        while (fok[aktualis] == 2) {
            int kovetkezo = -1;
            long long w = 0;
            for (auto [v, ww] : g[aktualis])
                if (v != elozo) {
                    kovetkezo = v;
                    w = ww;
                }
            if (kovetkezo == -1) break;
            hossz += w;
            elozo = aktualis;
            aktualis = kovetkezo;
        }
        leghosszabbUt = max(leghosszabbUt, hossz);
    }

    // B: a legtöbb úttal rendelkező települések
    int maxFok = 0;
    for (int v = 1; v <= n; v++) maxFok = max(maxFok, fok[v]);
    vector<int> legtobbUt;
    for (int v = 1; v <= n; v++)
        if (fok[v] == maxFok) legtobbUt.push_back(v);

    // C: az a település, amelynek legközelebbi szomszédja a legtávolabb van
    long long legtavolabb = -1;
    int legtavolabbi = 1;
    for (int v = 1; v <= n; v++) {
        if (fok[v] == 0) continue;
        if (legkozelebbi[v] > legtavolabb) {
            legtavolabb = legkozelebbi[v];
            legtavolabbi = v;
        }
    }

    cout << leghosszabbUt << '\n';
    for (size_t i = 0; i < legtobbUt.size(); i++) {
        if (i) cout << ' ';
        cout << legtobbUt[i];
    }
    cout << '\n' << legtavolabbi << '\n';
    return 0;
}
