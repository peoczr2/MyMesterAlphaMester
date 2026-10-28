/*
Megoldás lényege:
Minden napra kiszámoljuk a különbséget (este − reggel), és egy menetes maximumkiválasztással keressük a legnagyobb növekedést. A kezdeti maximumot 0-nak vesszük: csak szigorúan pozitív növekedés számít, ezért ha egyik nap sem nőtt, a kimenet 0. Több azonos maximum esetén a szigorú összehasonlítás miatt az első nap marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Minden napra elég a különbséget (este − reggel) kiszámolni, nem kell a napi értékeket tárolni. ||
Hint 2: || Egy menetben keress maximumot, de a kezdőértéke 0 legyen: így a nem növekedő napok nem kerülnek be, és ha egyik nap sem nőtt, a kimenet 0 marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestDay = 0;
    int bestInc = 0;
    for (int i = 1; i <= n; i++) {
        int morning, evening;
        cin >> morning >> evening;
        int inc = evening - morning;
        if (inc > bestInc) {
            bestInc = inc;
            bestDay = i;
        }
    }

    cout << bestDay << "\n";
    return 0;
}
