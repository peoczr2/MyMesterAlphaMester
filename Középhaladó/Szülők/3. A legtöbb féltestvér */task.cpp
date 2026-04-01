/*
Megoldás ötlete:
Minden emberhez eltároljuk a szüleit, és minden szülőhöz a gyerekeit.
Egy ember féltestvérei pontosan azok az emberek, akik vele legalább egy szülőt
megosztanak, de nem mindegyiket, ezért elég végigjárni az illető szüleinek
gyerekeit, és megszámolni, hány különböző emberhez jutunk el pontosan egyszer.
Ha valaki két szülőt is közösen kap meg, akkor a számlálója 2 lesz, így ő már
nem féltestvér, csak teljes testvér. Minden emberre kiszámítjuk a féltestvérek
számát, majd a legnagyobb értékűt keressük; holtversenyben a kisebb sorszám marad.
*/
/*
Hint 1: || Töltsd fel két listába az adatokat: szulok[gyerek] és gyerekek[szulo]. ||
Hint 2: || Egy ember féltestvéreihez minden szülőjén végig kell menni, és a
          szülő összes gyerekét meg kell jelölni, kivéve magát az embert. ||
Hint 3: || A megjelölt emberek közül csak azokat számold féltestvérnek, akikhez
          pontosan egy közös szülő vezet. ||
Hint 4: || A válasz keresésénél a nagyobb féltestvérszámot preferáld, egyenlőség
          esetén pedig a kisebb sorszámú embert. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> szulok(n + 1), gyerekek(n + 1);
    for (int i = 0; i < k; ++i) {
        int szulo, gyerek;
        cin >> szulo >> gyerek;
        szulok[gyerek].push_back(szulo);
        gyerekek[szulo].push_back(gyerek);
    }

    for (int i = 1; i <= n; ++i) {
        sort(szulok[i].begin(), szulok[i].end());
        szulok[i].erase(unique(szulok[i].begin(), szulok[i].end()), szulok[i].end());

        sort(gyerekek[i].begin(), gyerekek[i].end());
        gyerekek[i].erase(unique(gyerekek[i].begin(), gyerekek[i].end()), gyerekek[i].end());
    }

    int valasz = 1;
    int legjobb = -1;

    for (int ember = 1; ember <= n; ++ember) {
        vector<int> kozos(n + 1, 0);
        for (int szulo : szulok[ember]) {
            for (int masik : gyerekek[szulo]) {
                if (masik != ember) {
                    ++kozos[masik];
                }
            }
        }

        int db = 0;
        for (int masik = 1; masik <= n; ++masik) {
            if (kozos[masik] == 1) {
                ++db;
            }
        }

        if (db > legjobb) {
            legjobb = db;
            valasz = ember;
        }
    }

    cout << valasz << '\n';
    return 0;
}
