/*
Megoldás lényege:
Egy K hosszú ablak akkor nem tartalmazza az adott bázist, ha az ablak egy olyan összefüggő szakaszba esik, amelyben az a bázis nincs benne. Minden bázisra ezért megkeressük a leghosszabb ilyen szakaszt: ez a bázis két egymás utáni előfordulása közötti távolság (illetve a szöveg elejéig vagy végéig tartó rész). Ha K ennél a legnagyobb hosszúságnál nagyobb, akkor minden K hosszú ablak tartalmazza a bázist. Így a válasz a négy bázisra kapott maximumok maximuma plusz egy. Ha valamelyik bázis nem fordul elő, a feltétel sosem teljesülhet, ezért a válasz a szöveg hossza. Az időigény O(N), mert minden bázisra egyszer végigmegyünk a szövegen.
*/
/*
Hint 1: || Fordítsd meg a kérdést: keresd meg minden bázisra a leghosszabb olyan összefüggő részt, amelyben az a bázis nincs benne, mert a K-nak ennél nagyobbnak kell lennie. ||
Hint 2: || Egy bázis kihagyott részei két egymás utáni előfordulása között vannak, valamint a szöveg elejétől az első és az utolsótól a szöveg végéig. Ezek hosszát egy bejárással megkaphatod; ha valamelyik bázis egyáltalán nincs a szövegben, a válasz a szöveg hossza. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    string s;
    cin >> s;
    int n = s.size();

    const string bazisok = "ACGT";
    for (char x : bazisok) {
        if (s.find(x) == string::npos) {
            cout << n << '\n';
            return 0;
        }
    }

    int leghosszabbKihagyott = 0;
    for (char x : bazisok) {
        int utolso = -1;  // az előző előfordulás helye (-1: a szöveg eleje előtt)
        for (int i = 0; i < n; ++i) {
            if (s[i] == x) {
                leghosszabbKihagyott = max(leghosszabbKihagyott, i - utolso - 1);
                utolso = i;
            }
        }
        leghosszabbKihagyott = max(leghosszabbKihagyott, n - utolso - 1);
    }

    cout << leghosszabbKihagyott + 1 << '\n';

    return 0;
}
