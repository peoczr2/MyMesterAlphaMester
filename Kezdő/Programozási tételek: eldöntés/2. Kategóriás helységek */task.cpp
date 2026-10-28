/*
Megoldás lényege:
A kategória csak a helységek lélekszámától függ, a résztvevők száma a válaszban nem szerepel. Három logikai változóval nyilvántartjuk, előfordult-e V., VI. és VII. kategóriás helység. Minden helységet egyszer megnézünk, és a lélekszáma alapján állítjuk be a megfelelő változót. A végén a három változó alapján írjuk ki a három szót. A nevet sorként olvassuk, mert egy sor egy adat, így a többszavas nevek is jól kezelhetők. Az időigény N-nel arányos.
*/
/*
Hint 1: || A kategória csak a lélekszámtól (H) függ, a résztvevők száma (R) a válaszban nem szerepel. Elég három igaz/hamis jelzőt tartani: volt-e V., VI. vagy VII. kategóriás helység. ||
Hint 2: || Minden beolvasott helységnél nézd meg a lélekszámát: 8000 és 24999 között V., 25000 és 69999 között VI., 70000 felett VII. kategória. A megfelelő jelzőt állítsd igazra, a végén pedig három szót írj ki egy sorba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    bool v = false, vi = false, vii = false;
    for (int i = 0; i < n; i++) {
        string nev;
        int lelekszam, reszvevo;
        getline(cin >> ws, nev);
        cin >> lelekszam >> reszvevo;

        if (lelekszam >= 8000 && lelekszam <= 24999) {
            v = true;
        } else if (lelekszam >= 25000 && lelekszam <= 69999) {
            vi = true;
        } else if (lelekszam >= 70000) {
            vii = true;
        }
    }

    cout << (v ? "VAN" : "NINCS") << ' '
         << (vi ? "VAN" : "NINCS") << ' '
         << (vii ? "VAN" : "NINCS") << '\n';
    return 0;
}
