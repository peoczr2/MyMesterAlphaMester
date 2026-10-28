/*
Megoldás lényege:
Minden naphoz kiszámoljuk, hány határőr van ügyeletben: egy [E, U] intervallum elejéhez +1-et, a U+1. napnál -1-et írunk egy különbségi tömbbe, majd prefixösszeggel megkapjuk a napi darabszámokat. A legalább egy határőrös napok folytonos szakaszai a darabszámok balról jobbra való bejárásával azonosíthatók; a leghosszabb szakaszt tartjuk meg (egyenlőségnél a korábbit). Ezen belül a maximális darabszámú napot keressük, egyenlőség esetén a legkisebb sorszámút. Az időigény O(N+M).
*/
/*
Hint 1: || Számold ki minden napra, hány határőr van szolgálatban. Egy intervallum kezdőnapjához adj +1-et, a vége utáni napnál vonj le 1-et egy különbségi tömbben, majd a prefixösszeggel minden nap darabszámát megkapod. ||
Hint 2: || A darabszámok alapján a „legalább egy határőr van” napok folytonos szakaszait kell megkeresni. Balról jobbra haladva követheted, meddig tart az aktuális szakasz, és megtartod a leghosszabbat (egyenlőség esetén a korábbit). ||
Hint 3: || A kiválasztott szakaszon belül keresd meg a legnagyobb darabszámot, és a vele egyező darabszámú napok közül az elsőt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> diff(m + 2, 0);
    for (int i = 0; i < n; i++) {
        int e, u;
        cin >> e >> u;
        diff[e]++;
        diff[u + 1]--;
    }

    vector<int> cover(m + 1, 0);
    int run = 0;
    for (int d = 1; d <= m; d++) {
        run += diff[d];
        cover[d] = run;
    }

    int bestLen = 0, bestL = 0, bestR = 0;
    int d = 1;
    while (d <= m) {
        if (cover[d] == 0) {
            d++;
            continue;
        }
        int l = d;
        while (d <= m && cover[d] > 0) d++;
        int r = d - 1;
        if (r - l + 1 > bestLen) {
            bestLen = r - l + 1;
            bestL = l;
            bestR = r;
        }
    }

    int bestDay = bestL;
    for (int x = bestL; x <= bestR; x++) {
        if (cover[x] > cover[bestDay]) bestDay = x;
    }

    cout << bestLen << "\n" << bestDay << "\n";
    return 0;
}
