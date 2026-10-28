/*
Megoldás lényege: a három kedvezmény mindegyike a fizetendő jegyek arányát adja meg, a jegyár ismeretlen, de minden esetben közös szorzó, ezért elég ezeket az arányokat összehasonlítani. Csoportos kedvezménynél az arány 1 - p / 100, iskolainál (N - ingyenjegy) / N, diáknál 9 / 10. Az N legfeljebb 100, a kedvezmények lépcsős táblázatai egy-egy elágazással kiolvashatók. A törtek elkerülésére mindhármat a 100 * N közös nevezőre hozzuk: csoportos (100 - p) * N, iskolai (N - ingyenjegy) * 100, diák 90 * N, ezek már egész számok. Egyenlőség esetén a sorrend diák, iskolai, csoportos, ezért a legkisebb értékű variánsok közül ebben a sorrendben választunk. Az időigény állandó, O(1).
*/
/*
Hint 1: || A jegyár ismeretlen, de mindhárom esetben ugyanazzal szorzódik, ezért elég a három kedvezmény utáni fizetendő arányokat egymással összehasonlítani. ||
Hint 2: || Csoportosnál az arány (100 - p) / 100, iskolainál (N - ingyenjegy) / N, diáknál 90 / 100. Ezeket közös nevezőre (100 * N) hozva egész számokkal is összehasonlíthatod, így nem kell törtekkel vagy lebegőpontos számokkal dolgozni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Csoportos kedvezmény százaléka a csoport létszáma alapján
int csoportosSzazalek(int n) {
    if (n < 10) return 0;
    if (n <= 19) return 5;
    if (n <= 29) return 8;
    if (n <= 40) return 12;
    return 14;
}

// Iskolai kedvezményként járó ingyenjegyek száma a csoport létszáma alapján
int ingyenJegy(int n) {
    if (n < 5) return 0;
    if (n <= 11) return 1;
    if (n <= 19) return 2;
    if (n <= 28) return 3;
    if (n <= 40) return 4;
    return 5;
}

int main() {
    int n;
    cin >> n;

    // Mindhárom fizetendő arány a 100 * n közös nevezőre hozva, egész számként
    int csoportos = (100 - csoportosSzazalek(n)) * n;
    int iskolai = (n - ingyenJegy(n)) * 100;
    int diak = 90 * n;

    int legkisebb = min({csoportos, iskolai, diak});
    if (diak == legkisebb) {
        cout << "diak\n";
    } else if (iskolai == legkisebb) {
        cout << "iskolai\n";
    } else {
        cout << "csoportos\n";
    }
    return 0;
}
