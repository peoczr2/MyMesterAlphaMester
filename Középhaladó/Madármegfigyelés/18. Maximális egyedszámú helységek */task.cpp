/*
Megoldás lényege:
Minden madárfajhoz (táblázat oszlopához) külön keressük azt a helységet, ahol a legtöbb egyedet figyelték meg. Egy oszlopon végigmegyünk a helységeken, és csak szigorúan nagyobb értéknél frissítjük az eddigi legjobb helységet, így egyenlő maximum esetén a legkisebb sorszám marad, ahogy a példa is mutatja. A táblázatot egyszer beolvassuk, a keresés összesen O(M·N) időt igényel, ami a korlátok mellett gyors.
*/
/*
Hint 1: || Minden madárfaj (oszlop) külön kérdés: az adott oszlopban melyik sornál van a maximum. ||
Hint 2: || Tárold az M×N táblázatot, és fajonként egy bejárással tartsd nyilván az eddigi legnagyobb értéket és annak helységét. Egyenlőségnél ne cserélj. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> e(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> e[i][j];

    for (int j = 0; j < n; j++) {
        int best = 0;  // a legjobb helység indexe (0-tól számolva)
        for (int i = 1; i < m; i++)
            if (e[i][j] > e[best][j]) best = i;  // szigorú >: egyenlőségnél a kisebb sorszám marad
        cout << best + 1 << (j + 1 < n ? ' ' : '\n');
    }
    return 0;
}
