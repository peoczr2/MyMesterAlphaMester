/*
Megoldás lényege:
A telefonszámot karakterláncként olvassuk be, így a visszafelé olvasás a karakterek fordított sorrendjét jelenti.
Egy szám akkor tükörtelefonszám, ha önmaga visszafelé olvasva ugyanaz (palindrom), vagy vidéki szám (első jegye nem 1, mert Budapest körzetszáma az 1-es),
és a körzetszám két jegye egyenlő, vagy a körzetszám utáni hat jegy palindrom.
A budapesti számokra a körzetes feltételek nem vonatkoznak: a 11811886 nem tükör, pedig a körzetszáma (11) tükör.
Minden számot egy konstans méretű vizsgálattal dolgozunk fel, így az időigény O(N), ami N ≤ 10 000 esetén bőven belefér a 0.1 mp-be.
*/
/*
Hint 1: || A teljes számra vonatkozó eset mellett vidéki számoknál két további eset van: a körzetszám két jegye, illetve a körzet utáni rész. Budapesti szám (első jegy 1) esetén csak a teljes számot kell megnézni. ||
Hint 2: || Tartsd a számot string-ként: a körzetszám az s[0] és s[1] karakter, a körzet utáni rész az s.substr(2), és egy string akkor palindrom, ha egyezik a fordítottjával (reverse). ||
*/
#include <bits/stdc++.h>
using namespace std;

// Visszafelé olvasva ugyanaz-e a karakterlánc.
bool palindrom(const string& s) {
    return string(s.rbegin(), s.rend()) == s;
}

int main() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;

        bool tukor = palindrom(s);
        // Vidéki szám: az első jegy nem 1 (Budapest körzetszáma)
        if (s[0] != '1' && (s[0] == s[1] || palindrom(s.substr(2)))) {
            tukor = true;
        }

        if (tukor) {
            cout << s << "\n";
        }
    }
    return 0;
}
