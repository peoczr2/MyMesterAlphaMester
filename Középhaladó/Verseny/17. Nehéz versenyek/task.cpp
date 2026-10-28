/*
Megoldás lényege:
Minden versenyen külön meg kell számolni, hányan maradtak a versenyhez tartozó minimális pontszám alatt. Egy verseny akkor nehéz, ha az indulók legalább fele nem érte el a minimumot, azaz ha a minimum alatt maradók száma k és az indulók száma i esetén 2·k ≥ i. Ezt az egész számokkal felírt feltételt használjuk, így nincs szükség törtekre vagy lebegőpontos osztásra. A bemenetet sorban olvassuk: előbb a minimumokat, majd versenyenként az indulókat és a pontszámaikat, és közben számoljuk a minimum alatt maradókat. A nehéz versenyek sorszámait növekvő sorrendben, a darabszámukat pedig az elején írjuk ki. Az időigény az összes bejegyzés számával arányos, ami a korlátok mellett rendkívül gyors.
*/
/*
Hint 1: || Versenyenként külön kell nézni az indulókat: számold meg, hányan maradtak a versenyhez tartozó minimum alatt. ||
Hint 2: || Ne törtekkel dolgozz: ha k a minimum alatt maradók száma, i pedig az indulók száma, akkor a verseny nehéz, ha 2·k ≥ i. Ez egész számokkal pontosan ellenőrizhető. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> minimum(m);
    for (int i = 0; i < m; i++) {
        cin >> minimum[i];
    }

    vector<int> hard;
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        int below = 0;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p < minimum[i]) {
                below++;
            }
        }
        // legalább fele nem érte el a minimumot: 2 * below >= ind
        if (2 * below >= ind) {
            hard.push_back(i + 1);
        }
    }

    cout << hard.size();
    for (int x : hard) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
