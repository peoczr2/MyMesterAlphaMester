/*
Feladat: N vendég, az i. vendég a P időpontban van jelen, ha E <= P < U, azaz az [E, U-1] egész időpontokban.
A fényképész egy kihíváskor F-től F+T-1-ig marad, és ezalatt legfeljebb D képet készít. Legkevesebb hány
kihívás kell, hogy mindenki rajta legyen legalább egy képen? Meg kell adni a kihívásonkénti fotóidőpontokat is.

Ötlet (mohó, "minél később fotózunk"): Ha minden eddigi kép legfeljebb az f időpontban készült, és minden
E <= f vendég már rajta van egy képen, akkor a többi (E > f) vendéghez a következő képet a lehető legkésőbb
érdemes elkészíteni: a p = min{ U-1 : E > f } időpontban. Ez minden E <= p vendéget lefed (ők p-ben még jelen
vannak), így az állapot újra egyetlen szám lesz: f = p. Minél nagyobb f, annál kevesebb vendég van hátra.
Egy kihívás: az első képet p-ben készítjük, ekkor az ablak [p, p+T-1]. Ezen belül, amíg van még szabad kép
(legfeljebb D), a következő képet min(U-1 : E > f, p+T-1) időpontban készítjük, ha van még olyan hátralévő
vendég, aki az ablak vége előtt megérkezik (különben ez a kép már senkit sem fedne le). Az ablak végén
készült kép után a kihívás befejeződik. Minden lépés a lehető legnagyobbra tolja f-et, ezért kihívásonként
legalább olyan messzire jutunk, mint bármely más megoldás, így a kihívások száma minimális.
Megvalósítás: legkisebbU[x] = min U azon vendégekre, akikre E >= x (hátulról számolt minimum), és
db[x] = hány vendégre E <= x (prefix összeg). Így minden lépés O(1).
Lépésszám: O(N + maxU), memória: O(maxU).
*/
/*
Hint 1: || A legkorábban távozó, még le nem fényképezett vendéget az utolsó jelenléti időpontjában (U-1) érdemes lefotózni: ez mindenkit lefed, aki addigra megérkezett. ||
Hint 2: || Így a lefedett vendégek mindig pontosan azok, akik az utolsó kép idejéig megérkeztek, az állapot egyetlen időpont. ||
Hint 3: || Egy kihívás az első képtől T ideig tart: a további képek ideje a következő hátralévő vendég U-1 értéke, de legfeljebb az ablak vége, és legfeljebb D kép lehet. ||
Hint 4: || Előre számold ki minden x-re az E >= x vendégek legkisebb U értékét és az E <= x vendégek számát, így minden kép ideje O(1) alatt megvan. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás
    int n, t, d;
    cin >> n >> t >> d;
    const int MAXV = 20000;
    const int INF = INT_MAX;
    vector<int> legkisebbU(MAXV + 2, INF), db(MAXV + 1, 0);
    for (int i = 0; i < n; i++) {
        int e, u;
        cin >> e >> u;
        legkisebbU[e] = min(legkisebbU[e], u);
        db[e]++;
    }

    // legkisebbU[x] = min U az E >= x vendégekre; db[x] = az E <= x vendégek száma
    for (int x = MAXV; x >= 1; x--) legkisebbU[x] = min(legkisebbU[x], legkisebbU[x + 1]);
    for (int x = 1; x <= MAXV; x++) db[x] += db[x - 1];

    // f: az utolsó kép ideje; minden E <= f vendég már rajta van egy képen
    int f = 0;
    vector<vector<int>> kihivasok;
    while (db[f] < n) {
        // új kihívás: első kép a legkorábban távozó hátralévő vendég utolsó időpontjában
        int p = legkisebbU[f + 1] - 1;
        int vege = p + t - 1;  // az ablak utolsó időpontja
        vector<int> kepek = {p};
        f = p;

        // további képek ugyanebben az ablakban
        while ((int)kepek.size() < d && db[f] < n) {
            p = min(legkisebbU[f + 1] - 1, vege);
            if (p == vege && db[min(vege, MAXV)] == db[f]) break;  // az ablakban már senkit sem fednénk le
            kepek.push_back(p);
            f = p;
            if (p == vege) break;  // az ablak végén nincs több lehetőség
        }
        kihivasok.push_back(kepek);
    }

    // kiírás
    cout << kihivasok.size() << '\n';
    for (auto &kepek : kihivasok) {
        for (int i = 0; i < (int)kepek.size(); i++) cout << kepek[i] << (i + 1 < (int)kepek.size() ? ' ' : '\n');
    }
    return 0;
}
