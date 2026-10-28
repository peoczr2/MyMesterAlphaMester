/*
Megoldás lényege:
Minden mérkőzésnél a két betűt számmá alakítjuk: K = 0 (kő), P = 1 (papír), O = 2 (olló). A kő legyőzi az ollót, az olló a papírt, a papír a követ, ezért az első játékos akkor nyer, ha (első - második + 3) osztva 3-mal maradékot ad 1-et; egyenlő választásnál döntetlen. Az eredményt karakterek sorozataként fűzzük össze, és közben számoljuk a döntetlenek és a két játékos győzelmeinek számát. A táblázatot egy 3x3-as tömbben vezetjük: a sor a második, az oszlop az első játékos választását adja, így a kiírás a tömb sorainak sorrendjében történik. A mérkőzések száma a beolvasott párok száma. Az időigény O(M), ahol M a mérkőzések száma, a memóriaigény O(M).
*/
/*
Hint 1: || Egy mérkőzés két betűből áll, kötőjellel elválasztva. Az első betű az első játékos, az utolsó betű a második játékos választása. Alakítsd át a betűket 0, 1, 2 számokká, így a győzelem szabálya számtani alakban is felírható. ||
Hint 2: || Az első játékos akkor nyer, ha (első - második + 3) osztva 3-mal 1 maradékot ad. Döntetlen, ha a két szám egyenlő. A második játékos győzelmét az előző szabály szerepcserével kapod meg, vagyis a maradék a másik irányban számít. ||
Hint 3: || Egy 3x3-as tömbbe számold a párokat: a sor a második, az oszlop az első játékos számának indexe. A főátló adja a döntetlenek számát, a többi cella az egyik vagy a másik játékos győzelmét, így az utolsó részfeladat három száma ebből összegezhető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // Kő = 0, Papír = 1, Olló = 2
    auto sorszam = [](char c) {
        if (c == 'K') return 0;
        if (c == 'P') return 1;
        return 2;
    };

    int tabla[3][3] = {}; // tabla[második][első]
    string kimenetelek;
    long long meccsek = 0, dontetlen = 0, elsoNyert = 0, masodikNyert = 0;

    string meccs;
    while (cin >> meccs) {
        int elso = sorszam(meccs[0]);
        int masodik = sorszam(meccs.back());
        meccsek++;
        tabla[masodik][elso]++;

        if (elso == masodik) {
            dontetlen++;
            kimenetelek += 'X';
        } else if ((elso - masodik + 3) % 3 == 1) {
            elsoNyert++;
            kimenetelek += '1';
        } else {
            masodikNyert++;
            kimenetelek += '2';
        }
    }

    // 1. részfeladat: a mérkőzések száma
    cout << "#\n" << meccsek << "\n";

    // 2. részfeladat: az egyes mérkőzések kimenetele
    cout << "#\n" << kimenetelek << "\n";

    // 3. részfeladat: a táblázat
    cout << "#\n";
    for (int r = 0; r < 3; r++) {
        cout << tabla[r][0] << " " << tabla[r][1] << " " << tabla[r][2] << "\n";
    }

    // 4. részfeladat: döntetlenek, első játékos győzelmei, második játékos győzelmei
    cout << "#\n" << dontetlen << " " << elsoNyert << " " << masodikNyert << "\n";

    return 0;
}
