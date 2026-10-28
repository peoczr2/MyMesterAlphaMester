/*
Megoldás lényege:
A hét 7 napjának hőmérsékletét egy tömbbe olvassuk, a napok neveit pedig egy másik tömbbe tesszük ugyanazzal az indexeléssel. Egyetlen végigmenéssel meghatározzuk a fagyos napokat, azaz azokat, ahol a hőmérséklet nulla alatti. Az első részfeladatnál ezek számát, a másodiknál a napok nevét írjuk ki szóközzel elválasztva, mindkettő elé egy "#" sort teszünk. Ha nem volt fagyos nap, a második részfeladat eredménye üres sor. Az időigény O(1), mert a hét mindig 7 napból áll.
*/
/*
Hint 1: || Mindkét részfeladathoz ugyanazt a végigmenést használhatod: a hét minden napján ellenőrizd, hogy a hőmérséklet kisebb-e nullánál. Az első részfeladatban a találatokat számolod, a másodikban kiírod a napok nevét. ||
Hint 2: || Tárold a napok neveit egy tömbben (hetfo, kedd, … vasarnap), és ugyanazzal az indexszel nézd a hőmérsékleti tömböt. A névlistánál figyelj arra, hogy a nevek közé kerüljön szóköz, a sor végére viszont ne. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    const vector<string> napok = {"hetfo", "kedd", "szerda", "csutortok", "pentek", "szombat", "vasarnap"};

    vector<int> homerseklet(7);
    for (int i = 0; i < 7; i++) {
        cin >> homerseklet[i];
    }

    int fagyosNapok = 0;
    for (int i = 0; i < 7; i++) {
        if (homerseklet[i] < 0) {
            fagyosNapok++;
        }
    }

    // 1. részfeladat: a fagyos napok száma
    cout << "#\n";
    cout << fagyosNapok << "\n";

    // 2. részfeladat: a fagyos napok neve, szóközzel elválasztva
    cout << "#\n";
    bool elso = true;
    for (int i = 0; i < 7; i++) {
        if (homerseklet[i] < 0) {
            if (!elso) {
                cout << " ";
            }
            cout << napok[i];
            elso = false;
        }
    }
    cout << "\n";

    return 0;
}
