/*
Megoldás lényege:
Minden ládához pontosan egy üvegfajtát rendelünk, és a fajták különbözőek. Egy
üveg akkor marad a helyén, ha a fajtája megegyezik a láda kiválasztott fajtájával,
különben át kell rakni. A minimális átrakásszám ezért az összes üveg és a helyben
maradók számának különbsége, vagyis a helyben maradók összegét kell maximalizálni.
Mivel N legfeljebb 8, az összes permutációt (legfeljebb 8! = 40320) végigpróbáljuk,
és mindegyiknél N összeadást végzünk. Azonos összegnél a lexikografikusan első
permutációt írjuk ki.
Időigény O(N!·N), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Tegyük fel, hogy minden ládába egy fajta üvegeit gyűjtjük, és a fajták mind különbözőek. Egy láda üvegei közül csak a kiválasztott fajtához tartozók maradnak a helyükön, a többit át kell rakni. Így a feladat a ládák és a fajták párosítása. ||
Hint 2: || Mivel N legfeljebb 8, a fajták sorrendjének minden lehetősége végigpróbálható. Ha perm[i] az i. láda fajtája, a helyben maradó üvegek száma a[i][perm[i]-1] értékek összege; a legnagyobb összeget adó permutációból adódik a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    vector<vector<int>> a(n, vector<int>(n));
    long long total = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
            total += a[i][j];
        }
    }

    vector<int> perm(n);
    iota(perm.begin(), perm.end(), 1);

    long long bestKeep = -1;
    vector<int> bestPerm;
    do {
        long long keep = 0;
        for (int i = 0; i < n; ++i) keep += a[i][perm[i] - 1];
        if (keep > bestKeep) {
            bestKeep = keep;
            bestPerm = perm;
        }
    } while (next_permutation(perm.begin(), perm.end()));

    cout << total - bestKeep << '\n';
    for (int i = 0; i < n; ++i) {
        if (i) cout << ' ';
        cout << bestPerm[i];
    }
    cout << '\n';
    return 0;
}