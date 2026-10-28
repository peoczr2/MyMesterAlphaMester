/*
Megoldás lényege:
Minden hétre összeadjuk a 7 napi csapadékmennyiséget, és egy menetben keressük a legnagyobb összeget. A csere csak szigorúan nagyobb összegnél történik, így egyenlőség esetén a korábbi, kisebb sorszámú hét marad, ahogy a feladat kéri. Nem kell a teljes táblázatot tárolni, elég a legjobb összeg és a hozzá tartozó sorszám. Az időigény O(7·N), vagyis O(N), a memóriaigény O(1).
*/
/*
Hint 1: || Egy hét csapadéka a 7 napi mennyiség összege: minden hétre ezt az összeget kell kiszámolnod, és ehhez képest kell a maximumot keresni. ||
Hint 2: || Egy menetben tartsd nyilván az eddigi legnagyobb összeget és a hét sorszámát, és csak szigorúan nagyobb összegnél cserélj, így a legkisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int bestIndex = 1;
    int bestSum = -1;
    for (int i = 1; i <= n; i++) {
        int sum = 0;
        for (int j = 0; j < 7; j++) {
            int c;
            cin >> c;
            sum += c;
        }
        if (sum > bestSum) {
            bestSum = sum;
            bestIndex = i;
        }
    }

    cout << bestIndex << "\n";
    return 0;
}
