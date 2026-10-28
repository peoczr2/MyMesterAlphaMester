/*
Megoldás lényege:
A generáció itt nem számít, csak az számít, hogy gyártónként összesen hány konzol jelent meg. Ezért egy tömbben, amelynek indexe a gyártó sorszáma, minden feljegyzésnél az adott gyártó elemét növeljük a K értékkel. A végén a két kért gyártó összegét hasonlítjuk össze: a nagyobb összegű gyártó nevét írjuk ki, egyenlőség esetén az „EGYEZIK” szót. Mivel N legfeljebb 100 és M legfeljebb 50, az időigény és a memóriaigény is elhanyagolható.
*/
/*
Hint 1: || A generáció ebben a feladatban nem számít: elég gyártónként összeadni az összes kiadott konzolt. ||
Hint 2: || Tarts egy tömböt, amelynek indexe a gyártó sorszáma; minden feljegyzésnél az S indexű elemhez add hozzá a K számot, a végén pedig hasonlítsd össze a két kért gyártó összegét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<string> nev(n + 1);
    for (int i = 1; i <= n; i++) cin >> nev[i];
    int m;
    cin >> m;
    vector<int> ossz(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int s, g, k;
        cin >> s >> g >> k;
        ossz[s] += k;
    }
    int gy1, gy2;
    cin >> gy1 >> gy2;
    if (ossz[gy1] > ossz[gy2])
        cout << nev[gy1] << "\n";
    else if (ossz[gy2] > ossz[gy1])
        cout << nev[gy2] << "\n";
    else
        cout << "EGYEZIK\n";
    return 0;
}
