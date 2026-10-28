/*
Megoldás lényege:
Az árakat sorban, egyszer olvassuk be, és csak a K forintnál drágább fákat vesszük figyelembe.
Az eddigi legolcsóbb ilyen fa árát és sorszámát tároljuk; minden újabb drágább fánál, ha az ára kisebb a tároltnál, lecseréljük a tárolt értékeket.
Csak szigorúan kisebb ár esetén cserélünk, így egyenlő ár esetén a korábbi, azaz kisebb sorszámú fa marad.
Ha nem volt K forintnál drágább fa, a kiírás -1.
Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Csak azokat a fákat kell figyelembe venni, amelyek ára nagyobb K-nál. A többit egyszerűen át lehet ugrani. ||
Hint 2: || Egy menetben tartsd nyilván az eddigi legolcsóbb, K-nál drágább fa árát és sorszámát. Csak szigorúan kisebb árnál frissíts, így egyenlőségnél a korábbi fa marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int legjobbSorszam = -1;
    int legjobbAr = INT_MAX;
    for (int i = 1; i <= n; i++) {
        int ar;
        cin >> ar;
        if (ar > k && ar < legjobbAr) {
            legjobbAr = ar;
            legjobbSorszam = i;
        }
    }

    if (legjobbSorszam == -1) {
        cout << -1 << endl;
    } else {
        cout << legjobbSorszam << " " << legjobbAr << endl;
    }
    return 0;
}
