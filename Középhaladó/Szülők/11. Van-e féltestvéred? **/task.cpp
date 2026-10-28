/*
Megoldás lényege:
Két ember féltestvér, ha szüleik közül pontosan egy közös, a másik szülő pedig nem.
A bemeneti szülő-gyerek párokból minden emberhez eltároljuk a szüleit, majd az Y sorszámú
embert összevetjük az összes többi emberrel, és minden esetben megszámoljuk a közös szülők
számát. Ha valakinél ez a szám pontosan 1, Y-nak van féltestvére, és a válasz „Van”. Ha
ilyen ember nincs, a válasz „Nincs”. A mindkét szülőt megosztó embereket (az édestestvéreket)
ki kell hagyni. Minden összevetés legfeljebb néhány lépés, így a teljes megoldás O(N + K)
időben fut, ami N ≤ 1000 és K ≤ 2000 mellett bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Két ember féltestvér, ha pontosan egy szülőt osztanak meg egymással. Gondolj arra, hogy két ember szülői közül hány van közös. ||
Hint 2: || Minden emberhez tárold el a szüleit egy listában a bemenet szülő-gyerek párjaiból. Y szüleit hasonlítsd össze minden más ember szüleivel. ||
Hint 3: || Számold meg minden másik emberre, hány közös szülője van Y-nal. Ha ez pontosan 1, akkor ő féltestvér, a 2 közös szülő pedig már édestestvér, ezt ki kell hagyni. ||
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
        if (kozos == 1) van = true;
    }

    cout << (van ? "Van" : "Nincs") << '\n';
    return 0;
}
