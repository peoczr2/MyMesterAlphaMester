/*
Megoldás lényege:
Rögzítünk egy x atomot, és minden más y atomra megkérdezzük a kozepen(x,y) értékét. Ez az x-hez
közelebbi felezőpont, vagyis x-től floor(d/2) távolságra van, ha d az x és y távolsága. Így minden
atomnak lesz egy "felezőpont-szülője", és ezek egy bináris fát alkotnak: a d távolságú atom
szülőjének távolsága floor(d/2). Egy szülő két gyermeke a 2t és 2t+1 távolságú atom; melyik
melyik, azt egy további kérdéssel döntjük el: kozepen(s,x) a szülőt adja vissza, ha s a 2t
távolságú. Így minden atom x-től mért távolsága és oldala ismert, ezekből a helyek kiszámolhatók.
A kérdések száma kb. N + N/2, és minden atomra pontosan egyszer hívjuk a holvan műveletet.
*/
/*
Hint 1: || Rögzíts egy x atomot, és minden más y atomra kérdezd meg a kozepen(x,y) értékét. Ez az x és y közötti út felezőpontja, így minden atomnak megkapod a "felezőpont-szülőjét". ||
Hint 2: || Ha egy c atom x-től t távolságra van, a gyermekei a 2t és 2t+1 távolságú atomok. A kettő közül a 2t-st az dönti el, hogy kozepen(s,x) éppen c-t adja-e vissza. ||
Hint 3: || Az x két oldalán külön lánc van: a távolságokból és oldalakból a pozíciók kiszámolhatók, x-et a két oldal közé kell tenni. ||
*/
#include "meter.h"
#include <bits/stdc++.h>
using namespace std;

int main() {
    long n = meret();
    long x = 1;

    // ch[c]: azok az y atomok, amelyekre kozepen(x,y) = c
    vector<vector<long>> ch(n + 1);
    for (long y = 1; y <= n; y++) {
        if (y == x) continue;
        long c = kozepen(x, y);
        ch[c].push_back(y);
    }

    vector<long> tav(n + 1, 0), oldal(n + 1, 0);   // tav: x-től mért távolság, oldal: -1 vagy +1
    queue<long> q;
    long sz = 1;
    for (long e : ch[x]) {                          // x szomszédai: távolság 1, két külön oldal
        tav[e] = 1; oldal[e] = sz; sz = -1;
        q.push(e);
    }
    while (!q.empty()) {
        long c = q.front(); q.pop();
        vector<long> gy = ch[c];
        if (gy.size() == 1) {
            tav[gy[0]] = 2 * tav[c];
            oldal[gy[0]] = oldal[c];
            q.push(gy[0]);
        } else if (gy.size() == 2) {
            long s1 = gy[0], s2 = gy[1];
            if (kozepen(s1, x) != c) swap(s1, s2);  // s1 a 2t távolságú
            tav[s1] = 2 * tav[c];     oldal[s1] = oldal[c]; q.push(s1);
            tav[s2] = 2 * tav[c] + 1; oldal[s2] = oldal[c]; q.push(s2);
        }
    }

    // A bal oldal hossza L; x a L+1 helyen, a bal oldal 1..L, a jobb oldal L+2..n.
    long L = 0;
    for (long y = 1; y <= n; y++) if (y != x && oldal[y] == -1) L = max(L, tav[y]);
    for (long y = 1; y <= n; y++) {
        long hely = (y == x) ? L + 1 : (oldal[y] == -1 ? L + 1 - tav[y] : L + 1 + tav[y]);
        holvan(y, hely);
    }
    return 0;
}
