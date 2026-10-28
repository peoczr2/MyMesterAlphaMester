/*
Megoldás lényege:
Az első elemet (i) rögzítjük, a maradék tartományon két mutatóval (l = i+1, r = n−1) keressük a megfelelő párt. Ha a három szám összege kisebb X-nél, az l mutatót léptetjük, mert az aktuális l elem a megmaradt r-ekkel már nem adhat X-et; ha nagyobb, az r mutatót csökkentjük, és ugyanez áll az r elemre. Az első találatnál az indexek növekvők, így a három szám is növekvő sorrendben kerül kiírásra; ha nincs találat, a -1 a válasz. Az időigény O(N²), ami N ≤ 1000 esetén (kb. 5·10^5 lépés) bőven belefér az időkorlátba.
*/
/*
Hint 1: || Rendezett sorozatnál a háromelemű összeghez érdemes egy elemet rögzíteni, és a maradék kettőt két mutatóval keresni. ||
Hint 2: || Ha a három szám összege túl kicsi, növeld a bal mutatót, ha túl nagy, csökkentsd a jobb mutatót. ||
Hint 3: || Minden rögzített első elemhez egy teljes kétmutatós pásztázás adja meg az összes érvényes hármast, duplázás nélkül. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int x;
    cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) {
        int l = i + 1, r = n - 1;
        while (l < r) {
            int s = a[i] + a[l] + a[r];
            if (s == x) {
                cout << a[i] << ' ' << a[l] << ' ' << a[r] << '\n';
                return 0;
            }
            if (s < x) ++l; else --r;
        }
    }
    cout << -1 << '\n';
    return 0;
}
