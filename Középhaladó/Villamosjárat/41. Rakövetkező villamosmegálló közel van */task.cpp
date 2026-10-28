/*
Megoldás lényege:
Minden megállóhoz beolvassuk az előzőtől mért távolságát. Az első olyan megállót keressük, amelynek ez a távolsága szigorúan kisebb K-nál, és ekkor kiírjuk a sorszámát és a távolságát. A mintából látszik, hogy a kiírt távolság az adott megálló és az előző megálló távolsága. Ha nincs ilyen megálló, -1-et írunk ki. Az időigény O(N).
*/
/*
Hint 1: || A feladathoz nincs szükség az útvonal teljes végigszámolására: minden megállónál csak az előzőtől mért távolságot kell összevetni K-val. ||
Hint 2: || Olvasd be a megállókat sorban, és az első olyan sorszámnál, ahol a távolság kisebb K-nál, írd ki a sorszámot és a távolságot, majd fejezd be a programot. Ha egyiknél sincs ilyen, írd ki a -1-et. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int t, erk, ind;
        cin >> t >> erk >> ind;
        if (t < k) {
            cout << i << ' ' << t << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
