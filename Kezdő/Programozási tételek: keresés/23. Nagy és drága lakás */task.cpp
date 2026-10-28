/*
Megoldás lényege:
A lakásokat a felsorolás sorrendjében olvassuk be, és minden lakásnál megnézzük, hogy a területe nagyobb-e A-nál,
és az ára nagyobb-e B-nél. Az első ilyen lakás sorszámát azonnal kiírjuk, és befejezzük a programot.
Ha a végigolvasás után sincs ilyen lakás, a kimenet 0. A bemenetben az ár áll elöl, a terület utána.
Az időigény O(N).
*/
/*
Hint 1: || Egyetlen végigmenő ciklus elég. Az első találatnál állj meg, így a felsorolás sorrendje magától teljesül. ||
Hint 2: || A feltételben két szigorú összehasonlítás van: a terület nagyobb A-nál, az ár nagyobb B-nél. A bemenetben előbb az ár, utána a terület szerepel. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, a, b;
    cin >> n >> a >> b;
    for (int i = 1; i <= n; i++) {
        int ar, terulet;
        cin >> ar >> terulet;
        if (terulet > a && ar > b) {
            cout << i << "\n";
            return 0;
        }
    }
    cout << 0 << "\n";
    return 0;
}
