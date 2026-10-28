/*
Megoldás lényege:
Ha minden pontnak 0 vagy 2 fia van, a belső pontok száma pontosan N-1, a szerkezetek száma pedig a
Catalan-szám: C(N-1). A Catalan-számok a C(k+1) = C(k) * 2(2k+1) / (k+2) rekurzióval számolhatók, és minden
lépésben egész számot kapunk. Az iteráció N-1 lépésből áll, a köztes szorzat 128 bites típusban biztosan nem
csordul túl. Az időigény O(N), ami bőven belefér a 0,1 mp-be.
*/
/*
Hint 1: || Egy fában csak a szerkezet számít. Ha minden pontnak 0 vagy 2 fia van, a belső pontok száma a levelek számánál eggyel kevesebb. ||
Hint 2: || Ezek a fák Catalan-számokkal számolhatók. Írhatsz rekurziót: a gyökér két részfájának levélszámai összege adja a teljes levélszámot, és a két részfa egymástól függetlenül épül fel. ||
Hint 3: || Az iteratív képlet: a következő Catalan-szám az előzőből a 2(2k+1)/(k+2) szorzóval kapható. Először szorozz, és csak utána oszts, így az osztás maradék nélkül megy. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    unsigned long long ans = 1;
    for (int i = 0; i < N - 1; ++i) {
        __int128 t = ans;
        t *= 2 * (2 * i + 1);
        t /= (i + 2);
        ans = (unsigned long long)t;
    }
    cout << ans << '\n';
    return 0;
}