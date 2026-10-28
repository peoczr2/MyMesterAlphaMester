/*
Megoldás lényege:
Minden sorban három fajta szomszédos helypár lehet: a bal oldali blokkban egymás melletti helyek, a jobb oldali blokkban egymás melletti helyek, és a középen átívelő pár, vagyis a bal és a jobb oldal legbelső (utolsó) helye. A két oldalt két N×M-es tömbbe olvassuk be, majd minden sorra megnézzük mindhárom típusú párt. Ha valamelyik pár mindkét tagja szabad (értéke 0), a válasz IGEN, különben NEM. Az időigény O(N·M).
*/
/*
Hint 1: || Két hely akkor szomszédos, ha a bal vagy a jobb oldalon közvetlenül egymás mellett vannak, vagy ha ugyanabban a sorban a két oldal legbelső (a középhez legközelebbi) helye. ||
Hint 2: || Tárold a bal és a jobb oldalt külön kétdimenziós tömbben. Soronként a j és j+1 indexű elemek párjait, az utolsó (j = M-1) indexű elemek párját pedig külön ellenőrizd, és jegyezd meg, találtál-e két szabad szomszédos helyet. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> bal(n, vector<int>(m)), jobb(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> bal[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> jobb[i][j];
        }
    }

    bool van = false;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j + 1 < m; j++) {
            if (bal[i][j] == 0 && bal[i][j + 1] == 0) van = true;
            if (jobb[i][j] == 0 && jobb[i][j + 1] == 0) van = true;
        }
        if (bal[i][m - 1] == 0 && jobb[i][m - 1] == 0) van = true;
    }

    cout << (van ? "IGEN" : "NEM") << '\n';
    return 0;
}
