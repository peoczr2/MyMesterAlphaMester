/*
Megoldás lényege:
Minden napra kiszámoljuk a maximum és a minimum különbségét, amely nemnegatív, mert min ≤ max. A napokon egy menetben haladunk, és az eddigi legnagyobb különbséget és a hozzá tartozó nap sorszámát tartjuk nyilván. Csak szigorúan nagyobb különbségnél cserélünk, így holtverseny esetén a legkisebb sorszámú nap marad. Az időigény O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy napot egyetlen szám jellemez: a napi maximum és minimum különbsége. ||
Hint 2: || Menet közben tartsd nyilván az eddigi legnagyobb különbséget és a nap sorszámát, és csak szigorúan nagyobb értéknél frissíts. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestDay = 0;
    int bestDiff = INT_MIN;
    for (int i = 1; i <= n; i++) {
        int mn, mx;
        cin >> mn >> mx;
        int diff = mx - mn;
        if (diff > bestDiff) {
            bestDiff = diff;
            bestDay = i;
        }
    }

    cout << bestDay << "\n";
    return 0;
}
