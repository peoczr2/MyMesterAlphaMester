/*
Megoldás lényege:
A bemenet N sorából minden sor egy versenyzőt jelent, a sor 5 száma pedig a versenyzőnek az öt kvalifikációs versenyen elért helyezése. Egy versenyző akkor indult az adott versenyen, ha a helyezése nem 0.
Ezért versenyenként külön számlálót tartunk, és a bemenet beolvasása közben minden nem nulla helyezésnél a megfelelő számlálót növeljük.
Az öt számlálót a végén egy sorba írjuk ki. A K érték a számlálásban nem szerepel.
Az időigény O(N), a tárigény O(1), mert mindig csak öt számlálót tárolunk.
*/
/*
Hint 1: || Egy sor egy versenyzőt ír le, az 5 szám az öt versenyen elért helyezése. Egy versenyző akkor indult egy versenyen, ha ott a helyezése nem 0. ||
Hint 2: || Tarts öt számlálót, egyet-egyet minden versenyhez. Minden versenyzőnél menj végig az öt helyezésen, és a nem nulla helyezéseknél növeld a hozzájuk tartozó számlálót. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    int indulok[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int helyezes;
            cin >> helyezes;
            if (helyezes != 0) {
                indulok[j]++;
            }
        }
    }
    for (int j = 0; j < 5; j++) {
        cout << indulok[j] << (j < 4 ? " " : "\n");
    }
    return 0;
}
