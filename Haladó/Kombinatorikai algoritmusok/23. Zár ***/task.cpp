/*
Megoldás lényege:
Mindhárom tárcsát az 1-es állásba kell hozni. Egy tárcsa növekvő irányban d_+
lépéssel, csökkenő irányban d_- lépéssel jut az 1-es állásba, ahol d_+ + d_- = N,
ha a tárcsa nincs 1-en; ha már ott áll, mindkettő 0.
Egy lépésben tetszőleges nem üres részhalmaz forgatható ugyanabba az irányba.
Ezért a pozitív irányú lépésekből annyi kell, ahány a pozitív irányba forgatott
tárcsák d_+ értékeinek maximuma: a t-edik pozitív lépésbe azok a tárcsák kerülnek,
amelyeknek legalább t pozitív lépés kell. A negatív irányúak ugyanígy működnek.
Egy irányválasztás költsége tehát a két maximum összege, a válasz a 2^3 = 8
irányválasztás közül a legkisebb.
Időigény O(8·3), konstans.
*/
/*
Hint 1: || Egy lépés egy nem üres részhalmaz tárcsáit forgatja ugyanabba az irányba. Egy tárcsánál tehát két irány közül lehet választani, és mindkét irányban meg kell nézni, hány lépés kell az 1-es állásba. ||
Hint 2: || Ha már rögzítettük, melyik tárcsa melyik irányba forog, akkor a növekvő irányú tárcsák közül a legnagyobb szükséges lépésszám adja a növekvő irányú lépések számát, és ugyanígy a csökkenő irányúaké. Egy lépésbe mindig azok a tárcsák kerülhetnek, amelyeknek még van hátra lépésük. ||
Hint 3: || Mivel csak három tárcsa van, a 2^3 = 8 irányválasztás bitmaszkkal végigpróbálható. Egy maszkra a válasz a két maximum összege, a végeredmény a 8 eset minimuma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;

    int a[3];
    for (int i = 0; i < 3; ++i) cin >> a[i];

    int ans = INT_MAX;
    for (int mask = 0; mask < 8; ++mask) {
        int pos = 0, neg = 0;
        for (int i = 0; i < 3; ++i) {
            int cw = (1 - a[i] + n) % n;
            int ccw = (a[i] - 1 + n) % n;
            if (mask & (1 << i)) pos = max(pos, cw);
            else neg = max(neg, ccw);
        }
        ans = min(ans, pos + neg);
    }

    cout << ans << '\n';
    return 0;
}