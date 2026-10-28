/*
Megoldás lényege:
Egy versenyző akkor előzi meg a korábban lőtt versenyzőt, ha annak pontszáma kisebb az övénél. Ezért minden i-edik versenyzőnél azt kell megszámolni, hány korábbi versenyző pontszáma kisebb P_i-nél.
Mivel a pontszám legfeljebb M≤1000, minden pontszámhoz nyilvántartjuk, hány korábbi versenyzőnek lett az a pontszáma. Egy új versenyzőnél ezeket a P_i-nél kisebb pontszámokat összegezzük, majd a saját pontszámát hozzáadjuk a tömbhöz. Az időigény O(N*M), ami N≤100000 és M≤1000 mellett is belefér az időlimitbe.
*/
/*
Hint 1: || Egy versenyző akkor előzi meg a korábbit, ha annak pontszáma kisebb az övénél. Tehát minden versenyzőhöz a nála korábban lőttek közül a kisebb pontszámúak számát kell megadni. ||
Hint 2: || Mivel a pontszám legfeljebb 1000, tartsd nyilván tömbben, hány korábbi versenyzőnek volt az egyes pontszámokból, és minden lépésben a saját pontszámodnál kisebb értékeket összegezd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // db[p]: hány korábbi versenyzőnek lett p a pontszáma
    vector<int> db(m + 1, 0);
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;

        int kisebb = 0;
        for (int x = 1; x < p; x++) {
            kisebb += db[x];
        }
        cout << kisebb << (i + 1 < n ? " " : "\n");

        db[p]++;
    }
    return 0;
}
