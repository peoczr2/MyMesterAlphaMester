/*
Megoldás lényege:
Két ember akkor édestestvér, ha mindkét szülőjük közös, vagyis a szülőik halmaza
legalább két közös elemet tartalmaz. A bemeneti szülő-gyerek párokból minden emberhez
eltároljuk a szüleit, majd az Y sorszámú embert összevetjük az összes többi emberrel.
Ha valakinek Y mindkét szülője is szülője, akkor Y-nak van édestestvére, és a válasz
„Van”. Ha ilyen ember nincs, a válasz „Nincs”. Minden összevetés legfeljebb néhány
lépés, így a teljes megoldás O(N + K) időben fut, ami N ≤ 1000 és K ≤ 2000 mellett
bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Két testvér akkor édestestvér, ha a szüleik közül mindkettő közös. Gondolj arra, hogy két ember szülői közül hány van közös. ||
Hint 2: || Minden emberhez tárold el a szüleit egy listában a bemenet szülő-gyerek párjaiból. Y szüleit hasonlítsd össze minden más ember szüleivel. ||
Hint 3: || Ha valakinek Y mindkét szülője is szülője, akkor ő édestestvér: ilyen ember megléte esetén már kiírható a "Van". Y-t magát ne vedd figyelembe. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> szulok(n + 1);
    for (int i = 0; i < k; ++i) {
        int szulo, gyerek;
        cin >> szulo >> gyerek;
        szulok[gyerek].push_back(szulo);
    }

    int y;
    cin >> y;

    for (int i = 1; i <= n; ++i) {
        sort(szulok[i].begin(), szulok[i].end());
        szulok[i].erase(unique(szulok[i].begin(), szulok[i].end()), szulok[i].end());
    }

    bool van = false;
    for (int masik = 1; masik <= n && !van; ++masik) {
        if (masik == y) continue;

        int kozos = 0;
        for (int szulo : szulok[y]) {
            if (binary_search(szulok[masik].begin(), szulok[masik].end(), szulo)) ++kozos;
        }
        if (kozos == 2) van = true;
    }

    cout << (van ? "Van" : "Nincs") << '\n';
    return 0;
}
