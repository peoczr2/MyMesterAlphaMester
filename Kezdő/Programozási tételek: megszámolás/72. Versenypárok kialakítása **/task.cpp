/*
Megoldás lényege:
Csak a két csapat ellenfelei párosíthatók, és csak akkor, ha a pólójuk színe különbözik.
Így két egymástól független párosítási típus van: az első csapat zöldjei a második csapat
pirosaival, illetve az első csapat pirosai a második csapat zöldjeivel. Egyik típusban sem
használ senki olyat, aki a másikban szerepelne, ezért a két szám egyszerűen összeadható.
Mindkét típusban a párok száma a két színcsoport kisebb létszámától függ, így a válasz
min(z1, p2) + min(p1, z2). Az idő O(N+M).
*/
/*
Hint 1: || Csak az ellenfelek párosíthatók, és csak akkor, ha a színük különbözik. A piros-zöld és a zöld-piros párok egymástól függetlenül számolhatók. ||
Hint 2: || Számold meg mindkét csapatban a piros (p) és a zöld (z) pólósokat. Az első csapat zöldjeit a második csapat pirosaival, az első csapat pirosait a második csapat zöldjeivel kell párosítani; mindkét esetben a kisebb létszám a korlát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    string a, b;
    cin >> n >> a >> m >> b;

    int z1 = 0, p1 = 0, z2 = 0, p2 = 0;
    for (char c : a) {
        if (c == 'z') z1++;
        else p1++;
    }
    for (char c : b) {
        if (c == 'z') z2++;
        else p2++;
    }

    int ans = min(z1, p2) + min(p1, z2);
    cout << ans << "\n";
    return 0;
}
