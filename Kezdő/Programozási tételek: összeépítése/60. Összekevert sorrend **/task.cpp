/*
Megoldás lényege: mindkét szalag ugyanazt a permutációt tartalmazza, csak más helyeken lett elvágva. Egy darabon
belül két egymás utáni szám az eredeti sorrendben is szomszédos, és mivel nincs olyan hely, ahol mindkét szalagot
elvágták, minden szomszédos pár legalább az egyik szalag valamelyik darabjában szerepel. Így a darabokból
kiolvasott „utána következik” élek pontosan az eredeti sorrend láncát adják. Az élek alapján megkeressük az
egyetlen olyan számot, amelyhez nem fut be él (ez az első elem), és onnan N lépésben bejárjuk a láncot.
Időigény: O(N + a darabok összhossza).
*/
/*
Hint 1: || Egy darab két egymás utáni száma az eredeti sorrendben is egymás után áll. Gondold végig, hogy a két szalag
darabjaiból együtt melyik szomszédos párok ismerhetők meg. ||
Hint 2: || Mivel nincs olyan hely, ahol mindkét szalagot elvágták, az eredeti sorrend minden szomszédos párja legalább
az egyik szalagon egy darabon belül van. Tárold minden számhoz a rákövetkezőjét (nxt), és azt is, hogy van-e rá
bejövő él (van_elozo). ||
Hint 3: || Az a szám, amelyre nem fut be él, az eredeti sorrend első eleme. Innen az nxt tömbön végigmenve N elemet
kapsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;

    vector<int> nxt(n + 1, 0);
    vector<bool> hasPrev(n + 1, false);

    for (int strip = 0; strip < 2; strip++) {
        int pieces;
        cin >> pieces;
        for (int i = 0; i < pieces; i++) {
            int len;
            cin >> len;
            int prev = 0;
            for (int j = 0; j < len; j++) {
                int x;
                cin >> x;
                if (prev != 0) {
                    nxt[prev] = x;
                    hasPrev[x] = true;
                }
                prev = x;
            }
        }
    }

    int start = 1;
    for (int x = 1; x <= n; x++) {
        if (!hasPrev[x]) {
            start = x;
            break;
        }
    }

    int cur = start;
    for (int i = 0; i < n; i++) {
        cout << cur << (i + 1 < n ? ' ' : '\n');
        cur = nxt[cur];
    }
    return 0;
}
