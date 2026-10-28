/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Egy szigetnek egy bal és egy jobb partja van: a bal part a szakasz első, a jobb part az utolsó mérése. Mivel a szomszédos tengerszint 0, a part meredeksége maga a part magassága. Egy bejárással szakaszonként összehasonlítjuk a két partot, és két számlálóban nyilvántartjuk, hányszor meredekebb a bal, illetve a jobb part. A kimenet 1, ha a bal oldali számláló szigorúan nagyobb, egyébként 0. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy szigetnek pontosan egy bal és egy jobb partja van: a szigetet határoló első és utolsó pozitív mérés. A part meredeksége a part magassága, mert a szomszédos tengerszint 0. A kontinenshez érő szakaszok nem szigetek. ||
Hint 2: || Egy bejárásban keresd meg a pozitív szakaszokat, és minden szigeten hasonlítsd össze az első és az utolsó mérést. Két számlálóban gyűjtsd, hányszor nagyobb a bal, illetve a jobb part; az egyenlőt egyik sem számolja. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    int bal_meredekebb = 0;   // hány szigeten meredekebb a bal oldali part
    int jobb_meredekebb = 0;  // hány szigeten meredekebb a jobb oldali part

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a sziget [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        // a bal part meredeksége m[l] - 0, a jobb parté m[r] - 0
        if (m[l] > m[r]) bal_meredekebb++;
        else if (m[r] > m[l]) jobb_meredekebb++;
    }

    cout << (bal_meredekebb > jobb_meredekebb ? 1 : 0) << "\n";
    return 0;
}
