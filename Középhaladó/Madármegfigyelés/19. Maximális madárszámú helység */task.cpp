/*
Megoldás lényege:
Egy helység megfigyelt madarainak száma a helység sorában lévő értékek összege, ezért soronként összegezzük az E_ij számokat. Csak egy változó kell az eddigi legnagyobb összegnek és egy a hozzá tartozó helység sorszámának; a táblázatot nem kell eltárolni. Szigorúan nagyobb összegnél cserélünk, így egyenlőség esetén a kisebb sorszám marad. Az időigény O(M·N).
*/
/*
Hint 1: || Egy helység összes megfigyelt madarának száma a helység sorának elemeinek összege. ||
Hint 2: || Elég egy változó az eddigi legnagyobb összegnek és egy a hozzá tartozó sorszámnak; a sorokat nem kell egyszerre tárolni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int m, n;
    cin >> m >> n;
    long long bestSum = -1;  // a madárszámok nemnegatívak, így -1 biztosan kisebb
    int bestRow = 0;
    for (int i = 0; i < m; i++) {
        long long s = 0;
        for (int j = 0; j < n; j++) {
            int x;
            cin >> x;
            s += x;
        }
        if (s > bestSum) {
            bestSum = s;
            bestRow = i;
        }
    }
    cout << bestRow + 1 << "\n";
    return 0;
}
