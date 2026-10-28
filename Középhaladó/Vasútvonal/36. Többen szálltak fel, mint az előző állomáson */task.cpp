/*
Megoldás lényege:
Egy bejárásban az előző állomás felszállóinak számát tároljuk. Az i. állomás akkor felel meg, ha van előző állomása (i > 1), mindkét állomáson volt felszálló (az előző és az aktuális száma is pozitív), és az aktuális felszállók száma nagyobb az előzőnél.
Az első ilyen állomás sorszámát jegyezzük meg, a többit már nem kell vizsgálni. Ha nincs ilyen, a válasz -1. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Csak két egymás utáni állomás felszállóit kell összehasonlítani, miközben végigmész az állomásokon. ||
Hint 2: || Tartsd nyilván az előző állomás felszállóinak számát. Az első olyan állomásnál állj meg, ahol a felszállók száma nagyobb az előzőnél, és az előző állomáson is volt felszálló. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    long long prevFel = 0;
    int ans = -1;
    for (int i = 1; i <= n; i++) {
        long long le, fel;
        cin >> le >> fel;
        if (ans == -1 && i > 1 && prevFel > 0 && fel > prevFel) ans = i;
        prevFel = fel;
    }

    cout << ans << "\n";
    return 0;
}
