/*
Megoldás lényege: az esős napokat +1-nek, a szárazakat -1-nek vesszük, így egy intervallumban az esős napok száma pontosan akkor legalább a fele, ha az összeg nem negatív.
Az összeg prefixösszegek különbsége, ezért a feltétel O(1)-ben ellenőrizhető; az intervallum két szélén is esőnek kell lennie.
Minden esős l kezdőnapra hátulról keressük a legnagyobb megfelelő r végpontot, és a leghosszabb intervallumot tartjuk meg; döntetlennél a korábbi (kisebb l) marad.
Időigény: O(N^2) legrosszabb esetben, N <= 10 000 mellett bőven belül van, a rövidítés miatt gyakran sokkal gyorsabb.
*/
/*
Hint 1: || Az esős napokat +1-nek, a szárazakat -1-nek véve egy intervallumban akkor esik legalább a napok fele, ha az összeg nem negatív. Az intervallum két szélén is esőnek kell lennie. ||
Hint 2: || Prefixösszegekkel egy [l, r] intervallum összege két érték különbségeként írható fel, így bármely párt O(1)-ben ellenőrizhetsz. ||
Hint 3: || Rögzített bal végpontnál a jobb végpontot a sorozat végétől visszafelé keresd: az első megfelelő esős r adja az ehhez l-hez tartozó legjobb intervallumot. Csak a szigorúan hosszabb intervallum írja felül az eredményt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> esett(n + 1, 0);     // esett[i] = 1, ha az i. napon esett az eső
    vector<int> elotag(n + 1, 0);    // elotag[i] = esős - száraz napok száma az 1..i napokon
    for (int i = 1; i <= n; i++) {
        int m;
        cin >> m;
        esett[i] = (m > 0);
        elotag[i] = elotag[i - 1] + (esett[i] ? 1 : -1);
    }

    int legHosszabb = 0, bal = 0, jobb = 0;
    for (int l = 1; l <= n; l++) {
        if (!esett[l]) continue;
        // a legnagyobb r, amely megfelel; csak akkor érdemes keresni, ha hosszabb lehet a jelenlegi legjobbnál
        for (int r = n; r >= l && r - l + 1 > legHosszabb; r--) {
            if (esett[r] && elotag[r] >= elotag[l - 1]) {
                legHosszabb = r - l + 1;
                bal = l;
                jobb = r;
                break;
            }
        }
    }

    cout << bal << " " << jobb << "\n";
    return 0;
}
