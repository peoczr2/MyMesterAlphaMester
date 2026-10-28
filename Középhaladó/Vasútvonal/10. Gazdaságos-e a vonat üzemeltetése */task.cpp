/*
Megoldás lényege:
A vonaton lévő utasok száma a szakaszokon ugyanúgy léptethető, mint az 1. feladatban: az (i+1). állomás után a létszám előző értéke + felszállók - leszállók.
Az utolsó állomás után nincs szakasz, így az összes bevétel U-szor a szakaszokon utazó utasok összege az első N-1 szakaszra, a kiadás pedig (N-1) * V.
A vonal akkor gazdaságos, ha a bevétel szigorúan nagyobb a kiadásnál, ekkor a kiírt szám 1, különben 0.
Egy bejárással O(N) időben megoldható, a memóriaigény O(N). Az összegek nagyok lehetnek, ezért long long.
*/
/*
Hint 1: || Nem kell a vonat teljes menetét szimulálni: elég megszámolni, hány szakaszt tesz meg a vonat, és hány utas-szakasz (utas x szakasz) fordul elő összesen. ||
Hint 2: || A szakaszon lévő utasok száma az előző állomás utáni létszám, plusz a felszállók, mínusz a leszállók. Az utolsó állomás után már nincs szakasz, ezért annak létszámát nem kell a bevételhez adni. ||
Hint 3: || Hasonlítsd össze a két összeget szigorúan (bevétel > kiadás), és ügyelj arra, hogy a szorzatok és az összegek 64 bites egészek legyenek. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    long long u, v;
    cin >> n >> u >> v;

    vector<long long> le(n), fel(n);
    for (int i = 0; i < n; i++) cin >> le[i] >> fel[i];

    long long cur = 0;      // a vonaton lévő utasok száma
    long long revenue = 0;  // összes bevétel
    for (int i = 0; i < n; i++) {
        cur += fel[i] - le[i];
        if (i < n - 1) revenue += u * cur;  // az (i+1). szakaszon utazók fizetnek
    }
    long long cost = v * (n - 1);

    cout << (revenue > cost ? 1 : 0) << "\n";
    return 0;
}
