/*
Megoldás lényege:
Az induló állomástól mért távolság egy megállóig az addig tartó szakaszok hosszának összege, vagyis folyamatos összegzéssel kapjuk. Mivel minden szakasz hossza pozitív, ez az érték a megállók sorszámával szigorúan nő. Ezért a K-nál távolabbi állomások közül a legközelebbit az a első megálló adja, amelynél az összeg már nagyobb K-nál. Ha nincs ilyen megálló, a kimenet -1. Az időigény O(N).
*/
/*
Hint 1: || Az induló állomástól mért távolságot úgy kapod, hogy az állomások között az előzőtől mért távolságokat egymás után összeadod. ||
Hint 2: || Mivel a távolságok szigorúan nőnek, az első olyan megálló lesz a legközelebbi K-nál távolabbi, amelynél az összeg először nagyobb K-nál. Egy ciklusban ezt az elsőt rögzítsd, és ha nincs ilyen, írj -1-et. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    int dist = 0;  // az induló állomástól mért távolság
    int ansIdx = -1, ansDist = -1;
    for (int i = 1; i <= n; i++) {
        int t, arr, dep;
        cin >> t >> arr >> dep;
        dist += t;
        if (ansIdx == -1 && dist > k) {
            ansIdx = i;
            ansDist = dist;
        }
    }

    if (ansIdx == -1) {
        cout << -1 << '\n';
    } else {
        cout << ansIdx << ' ' << ansDist << '\n';
    }
    return 0;
}
