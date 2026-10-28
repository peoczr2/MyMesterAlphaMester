/*
Megoldás lényege:
Egy megálló távolsága az előzőtől a sor első száma, ezért a feladat kérdése erre a számra vonatkozik. A megállókat sorrendben olvassuk, és az első olyan megállónál, ahol a távolság nagyobb K-nál, kiírjuk a sorszámát és a távolságot, majd kilépünk. Ha egyik megálló távolsága sem nagyobb K-nál, a válasz -1. Az érkezési és indulási időket nem kell tárolni. Az időigény O(N), ami N ≤ 100 mellett elhanyagolható.
*/
/*
Hint 1: || Egy megálló távolsága az előzőtől minden sorban az első szám. Az érkezési és indulási idők most nem befolyásolják a választ. ||
Hint 2: || Haladj a megállók sorrendjében, és az első olyan megállónál, ahol a távolság szigorúan nagyobb K-nál, írd ki a sorszámát és a távolságát, majd fejezd be. Ha a végéig nem találsz ilyet, írj ki -1-et. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        int dist, arr, dep;
        cin >> dist >> arr >> dep;
        if (dist > k) {
            cout << i << ' ' << dist << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
