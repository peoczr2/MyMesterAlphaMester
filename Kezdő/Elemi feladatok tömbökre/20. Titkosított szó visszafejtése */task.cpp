/*
Megoldás lényege:
A titkosított szöveg betűi párokat alkotnak: a páros első betűje a táblázat sorát, a második betűje az oszlopát adja meg. A visszafejtéshez tehát a szöveget két-két karakterenként dolgozzuk fel, és minden párhoz kikeressük a táblázat megfelelő mezőjét. A táblázat c. sorának i. mezője szóköz, ezt is tárolni kell, mert a visszafejtett szövegben szóköz is előfordulhat. A megoldás a szöveg hosszával arányos, lineáris időben fut.
*/
/*
Hint 1: || A titkosított szöveg mindig két karakteres egységekből áll: az első karakter a sor (a, b, c), a második az oszlop (a–i) betűjét adja meg. ||
Hint 2: || Tárold a táblázat sorait stringek tömbjében, a sor- és oszlopindexet pedig a betű és az 'a' karakter különbségéből számold ki. A c. sor i. mezőjébe szóközt írj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // a táblázat sorai: a, b, c; az oszlopok a..i; a c. sor i. mezője szóköz
    const string tabla[3] = {
        "ioqhbfylw",
        "nragsktez",
        "dupxcjvm "
    };

    string s;
    cin >> s;

    string out;
    for (size_t i = 0; i + 1 < s.size(); i += 2) {
        int sor = s[i] - 'a';
        int oszlop = s[i + 1] - 'a';
        out += tabla[sor][oszlop];
    }
    cout << out << '\n';
    return 0;
}
