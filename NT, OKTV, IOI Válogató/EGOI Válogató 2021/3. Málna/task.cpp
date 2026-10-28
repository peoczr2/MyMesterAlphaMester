/*
Megoldas: prefix osszegek paritasa.
Egy reszsorozat osszege akkor paros, ha a ket vegpontot jelolo prefixek paritasa
megegyezik. Ezert eleg a paros es paratlan prefixek szamanak megszamlalasa.
Az idoigeny O(N).
*/
/*
Hint 1: || Egy szakasz összege pontosan akkor páros, ha a szakasz végéig tartó prefixösszeg és a szakasz előtti prefixösszeg paritása megegyezik. Vagyis elég a prefixek paritását nézni. ||
Hint 2: || Haladj balról jobbra, és számold, hány korábbi prefix volt páros és hány páratlan (az üres prefixet, amelynek értéke 0, páros prefixnek számold). Minden új bokornál az aktuális prefix paritásával egyező korábbi prefixek számát add hozzá a válaszhoz, majd növeld ezt a számlálót. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    long long darab[2] = {1, 0};
    int paritas = 0;
    long long valasz = 0;
    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        paritas ^= (x & 1);
        valasz += darab[paritas];
        ++darab[paritas];
    }
    cout << valasz << '\n';
    return 0;
}