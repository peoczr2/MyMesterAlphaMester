/*
Megoldás lényege:
Egy versenyen a K. helyezett 1, az őt megelőző 3, és így tovább, 2 pontos lépésekkel, tehát a h helyezés (1 ≤ h ≤ K) 2·(K − h) + 1 pontot ér.
A K-nál rosszabb helyezés és a nem indulás (0) nem ad pontot. A holtverseny-szabály csak a kijutásra vonatkozik, az összpontszámot nem változtatja.
Minden versenyző 5 helyezését egyesével beolvassuk, és a pontokat a versenyző összegéhez adjuk; az időigény O(5·N).
*/
/*
Hint 1: || Minden versenyen csak az első K helyezett kap pontot. A K. helyezett 1 pontot kap, az őt megelőző 3-at, és így tovább. Hogyan változik a pont a helyezés függvényében? ||
Hint 2: || Ha a helyezés h (1 ≤ h ≤ K), a pont 2·(K − h) + 1. Ez a képlet a 2 pontos lépésközt írja le: h = K esetén 1, h = K − 1 esetén 3 pont. ||
Hint 3: || Minden versenyző 5 helyezését egyenként olvasd be. A 0 (nem indult) és a K-nál rosszabb helyezés nem ad pontot, ezeket szűrd ki, mielőtt a pontot a versenyző összpontszámához adod. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<int> osszpont(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 5; j++) {
            int h;
            cin >> h;
            if (h >= 1 && h <= k) {
                osszpont[i] += 2 * (k - h) + 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << osszpont[i] << (i + 1 < n ? " " : "\n");
    }
    return 0;
}
