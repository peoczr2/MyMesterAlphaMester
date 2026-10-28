/*
Megoldás lényege:
Egy tanuló akkor felel meg, ha minden versenyen elindult, és ott elérte a versenyhez tartozó minimális pontszámot. Minden tanulóhoz egy igaz kezdőértéket rendelünk, amely versenyenként hamissá válik, ha a tanuló az adott versenyen nem indult, vagy a minimumot nem érte el. Egy versenyen ehhez egy segédtömbbe jelöljük azokat, akik teljesítettek, majd a többieket kizárjuk. A végén azok sorszámát írjuk ki növekvő sorrendben, a darabszámukkal együtt. Az időigény O(N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Egy tanuló pontosan akkor felel meg, ha minden versenyen szerepel, és ott legalább a versenyhez tartozó minimumot éri el. Ezért versenyenként külön kell ellenőrizni, kik teljesítenek. ||
Hint 2: || Tarts nyilván minden tanulóról egy jelzőt, ami kezdetben igaz. Minden versenyen azokat a tanulókat, akik nem szerepeltek vagy nem érték el a minimumot, állítsd hamisra. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mins(m);
    for (int i = 0; i < m; i++) {
        cin >> mins[i];
    }

    vector<bool> ok(n + 1, true);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        vector<bool> good(n + 1, false);
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p >= mins[i]) {
                good[s] = true;
            }
        }

        for (int s = 1; s <= n; s++) {
            if (!good[s]) {
                ok[s] = false;
            }
        }
    }

    vector<int> ans;
    for (int s = 1; s <= n; s++) {
        if (ok[s]) {
            ans.push_back(s);
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
