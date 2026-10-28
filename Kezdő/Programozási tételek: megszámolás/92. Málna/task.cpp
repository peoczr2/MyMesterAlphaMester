/*
Megoldás lényege:
Legyen P[0] = 0 és P[i] az első i bokron lévő málnák összege. Az i-től j-ig tartó szakasz összege P[j] - P[i-1], ez pontosan akkor páros, ha P[j] és P[i-1] paritása megegyezik. Ezért elég a prefixösszegek paritását végigkövetni, és minden lépésben megszámolni, hány korábbi prefixösszeg volt ugyanolyan paritású. A futásidő O(N), a válasz legfeljebb kb. 5 * 10^9, ezért 64 bites egész kell.
*/
/*
Hint 1: || Egy szakasz összege P[j] - P[i-1] alakú, ezért akkor páros, ha a két prefixösszeg paritása megegyezik. Ez már összeszámolható az eddigi előfordulások alapján. ||
Hint 2: || Tarts két számlálót: hány páros és hány páratlan prefixösszeg volt eddig, kezdetben a P[0] = 0 páros. Minden új prefixösszegnél a megfelelő paritású eddigi darabszám adja az új jó szakaszok számát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    long long db[2] = {1, 0};
    int paritas = 0;
    long long ans = 0;
    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        paritas ^= (m & 1);
        ans += db[paritas];
        db[paritas]++;
    }
    cout << ans << "\n";
    return 0;
}
