/*
Megoldás lényege:
Minden hét egy sor a bemenetben, benne a hét 7 napjának csapadékmennyiségével.
Egy hét összes csapadéka ezeknek a számoknak az összege, ezért soronként egy belső ciklusban összegezzük a 7 értéket.
Az összeget minden hét után kiírjuk, így a kimenet N szám lesz; az időigény O(7·N).
*/
/*
Hint 1: || Egy hét csapadéka a hét 7 napjának összege. Hány szám tartozik egy hétre a bemenetben? ||
Hint 2: || Két egymásba ágyazott ciklust használj: a külső a heteken megy végig, a belső 7 számot olvas be és adja össze egy változóba. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    for (int het = 0; het < n; het++) {
        int osszeg = 0;
        for (int nap = 0; nap < 7; nap++) {
            int c;
            cin >> c;
            osszeg += c;
        }
        cout << osszeg << (het + 1 < n ? " " : "\n");
    }
    return 0;
}
