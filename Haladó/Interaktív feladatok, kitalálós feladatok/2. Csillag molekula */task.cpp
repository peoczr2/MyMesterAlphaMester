/*
Megoldás lényege:
A molekula egy fa, amelynek egyetlen központi atomja legalább három szomszéddal rendelkezik.
A Kozte(x,y) művelet eldönti, hogy x és y közvetlen szomszédok-e: ha az eredmény x vagy y,
akkor igen, egyébként nem. Ezzel egy atom szomszédai megkereshetők. Az atomokat sorban
végigvizsgáljuk, és az első olyan atomnál, amelynek legalább három szomszédját megtaláltuk,
kiírjuk a központot. A már lekérdezett párokat tároljuk, így minden párt legfeljebb egyszer
kérdezünk le. Az időigény O(N^2) kérdés a legrosszabb esetben.
*/
/*
Hint 1: || Két atom közvetlen szomszédságát egyetlen Kozte híváss el lehet dönteni: ha az eredmény a két atom valamelyike, akkor szomszédosak. ||
Hint 2: || Egy atom szomszédait úgy kapod meg, hogy ezt az ellenőrzést elvégzed az összes többi atommal. A központ az, akinek legalább három szomszédja van. ||
*/
#include "muszer.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n = Atomszam();

    // adj[x][y]: -1 = még nem kérdeztük, 0 = nem szomszéd, 1 = szomszéd
    vector<vector<signed char>> adj(n + 1, vector<signed char>(n + 1, -1));
    auto szomszed = [&](int x, int y) {
        if (adj[x][y] < 0) {
            int r = Kozte(x, y);
            adj[x][y] = adj[y][x] = (r == x || r == y) ? 1 : 0;
        }
        return adj[x][y] == 1;
    };

    for (int v = 1; v <= n; v++) {
        int cnt = 0;
        for (int y = 1; y <= n && cnt < 3; y++) {
            if (y != v && szomszed(v, y)) cnt++;
        }
        if (cnt >= 3) {
            Kozpont(v);
        }
    }
    return 0;
}
