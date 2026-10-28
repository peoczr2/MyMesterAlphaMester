/*
Megoldás lényege:
A bemenet szövegében egyetlen bejárással megszámoljuk az 'A' (Ádám) és az 'E' (Éva) karakterek számát.
A két számlálót összehasonlítjuk: a többször győző nevét írjuk ki, egyenlőség esetén a DONTETLEN szót.
Az időigény O(N), ahol N a játékok száma, ami legfeljebb 100, így a megoldás gyors.
*/
/*
Hint 1: || Elég két számlálót vezetni: az egyik az Ádám, a másik az Éva győzelmeit számolja. ||
Hint 2: || A szöveg minden karakterét egyszer kell megnézni, a végén a két számláló értékét kell összevetni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    string s;
    cin >> s;

    int adam = 0; // Ádám győzelmeinek száma
    int eva = 0;  // Éva győzelmeinek száma
    for (char c : s) {
        if (c == 'A') {
            ++adam;
        } else if (c == 'E') {
            ++eva;
        }
    }

    if (adam > eva) {
        cout << "ADAM\n";
    } else if (eva > adam) {
        cout << "EVA\n";
    } else {
        cout << "DONTETLEN\n";
    }
    return 0;
}
