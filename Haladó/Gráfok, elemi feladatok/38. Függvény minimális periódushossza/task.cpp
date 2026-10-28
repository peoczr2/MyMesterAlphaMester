/*
Megoldás lényege:
Minden x-ből indulva az x, F(x), F(F(x)), ... sorozat előbb-utóbb egy ciklusba jut, a periódus pedig ennek a ciklusnak a hossza. Így a feladat: megtalálni a függvénygráf ciklusai közül a legrövidebbet.
Minden még be nem járt kezdőcsúcsból bejárjuk az utat, és feljegyezzük, melyik bejárás járta be az egyes csúcsokat. Ha a bejárás olyan csúcshoz ér, amelyet ugyanebben a bejárásban már láttunk, ciklust találtunk; hossza a két előfordulás pozíciójának különbsége.
A minimális hosszú ciklust megtartjuk, és a ciklus elemeit a belépési csúcstól kezdve, az F-et követve írjuk ki. Az időigény O(N), mert minden csúcsot pontosan egyszer járunk be.
*/
/*
Hint 1: || Egy F függvénynél minden csúcsnak pontosan egy kimenő éle van, ezért minden út ciklusba fut. Elég a függvénygráf ciklusai közül a legrövidebbet megtalálni. ||
Hint 2: || Egy csúcsot akkor kezdj el bejárni, ha még sosem jártad be. Jegyezd fel, melyik kezdőpont bejárásában láttad, és a pozíciókat; ha a bejárás a saját korábbi csúcsához ér, ott van a ciklus, hossza a pozíciók különbsége. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> f(n + 1);
    for (int i = 1; i <= n; ++i) cin >> f[i];

    vector<int> walkOf(n + 1, 0);  // melyik kezdőpont bejárása látta a csúcsot (0: még nem)
    vector<int> pos(n + 1, 0);     // a csúcs sorszáma abban a bejárásban
    int bestLen = INT_MAX, bestStart = -1;

    for (int s = 1; s <= n; ++s) {
        if (walkOf[s]) continue;
        int x = s, step = 0;
        while (!walkOf[x]) {
            walkOf[x] = s;
            pos[x] = step++;
            x = f[x];
        }
        if (walkOf[x] == s) {  // a saját bejárásunkban értünk vissza: ez egy ciklus
            int len = step - pos[x];
            if (len < bestLen) {
                bestLen = len;
                bestStart = x;
            }
        }
    }

    cout << bestLen << '\n';
    int x = bestStart;
    for (int i = 0; i < bestLen; ++i) {
        cout << x << (i + 1 < bestLen ? ' ' : '\n');
        x = f[x];
    }
    return 0;
}
