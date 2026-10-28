/*
Megoldás lényege:
Minden évben ugyanannyi napot figyelünk meg, ezért az éves átlagok sorrendje megegyezik az éves összegek
sorrendjével, így az osztás elhagyható. Az A) részben az összegek első maximumát keressük. A B) részben az E
évtől visszafelé lépkedünk, amíg az előző év összege kisebb, így megkapjuk a folyamatos növekedés kezdetét.
A napokat oszloponként vizsgáljuk: minden napon megkeressük a legmelegebb értéket és azt az évet, amelyben
először fordult elő. Az „egyik másik évben sem volt melegebb” megfogalmazás szerint az egyenlő értékek is
megfelelnek, ezért a C) részben az utolsó év azon napjait számoljuk, ahol az utolsó év értéke eléri a napi
maximumot, a D) részben pedig a napi maximumok legkorábbi évei közül a legkisebbet adjuk. Az időigény és a
memóriaigény O(N·M).
*/
/*
Hint 1: || Mivel minden évben ugyanannyi nap van, nem kell átlagot számolni: az éves összegek sorrendje ugyanaz. Az A) részhez ezért elég szélsőérték-keresés az összegekben, egyenlőség esetén a legelső évet kell választani. ||
Hint 2: || B): az E. évtől visszafelé haladva addig lépj egyet, amíg az előző év összege kisebb. C) és D): a napokat oszloponként nézd végig, és minden napra jegyezd fel a legnagyobb hőmérsékletet és azt, hogy melyik évben jelent meg először. ||
Hint 3: || C): ha egy napon több év is eléri a maximumot, az utolsó év az adott napon még megfelel, mert a feltétel szerint egyik másik évben sem volt melegebb. D): minden napra vedd a maximumot elérő legkorábbi évet, és ezek közül a legkisebb sorszámút add vissza. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> t(n + 1, vector<int>(m + 1));
    vector<long long> evosszeg(n + 1);

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> t[i][j];
            evosszeg[i] += t[i][j];
        }
    }

    int legjobb_ev = 1;
    for (int i = 2; i <= n; ++i) {
        if (evosszeg[i] > evosszeg[legjobb_ev]) {
            legjobb_ev = i;
        }
    }

    int kezdo_ev = legjobb_ev;
    while (kezdo_ev > 1 && evosszeg[kezdo_ev - 1] < evosszeg[kezdo_ev]) {
        --kezdo_ev;
    }

    int melegebb_idei_napok = 0;
    int legregibb_ev = n + 1;
    for (int j = 1; j <= m; ++j) {
        int legnagyobb = t[1][j], ev = 1;
        for (int i = 2; i <= n; ++i) {
            if (t[i][j] > legnagyobb) {
                legnagyobb = t[i][j];
                ev = i;
            }
        }
        if (t[n][j] == legnagyobb) {
            ++melegebb_idei_napok;
        }
        legregibb_ev = min(legregibb_ev, ev);
    }

    cout << legjobb_ev << '\n';
    if (kezdo_ev < legjobb_ev) cout << kezdo_ev << '\n';
    else cout << '\n';
    cout << melegebb_idei_napok << '\n';
    cout << legregibb_ev << '\n';
    return 0;
}
