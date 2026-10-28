/*
Megoldás lényege:
Minden számhoz nyilvántartjuk az utolsó kisorsolásának napját, így egy új kisorsolásnál azonnal megkapjuk a két egymást követő előfordulás távolságát.
Ez a távolság egy szakasz hossza, ezért a hossz szerinti darabszám-tömbben növeljük a megfelelő elemet.
Mivel a számok egy hosszú, N ≤ 100 000 elemű sorozatból állnak, minden nap O(1) munkát végzünk, és a végén a darabszám-tömb maximuma adja a választ.
Ha nem volt egyetlen ismétlődő szám sem, a tömb csupa nulla, és a válasz 0.
Az időigény O(N + M), ami az 0,1 mp-es limitbe bőven belefér.
*/
/*
Hint 1: || Tartsd nyilván minden számról, melyik napon volt utoljára kisorsolva. Egy új kisorsolásnál a két nap különbsége adja az előző kisorsolása óta eltelt szakasz hosszát. ||
Hint 2: || Készíts egy tömböt, amelynek i-edik eleme azt mondja meg, hányszor fordult elő i hosszúságú szakasz. A végén keresd ennek a tömbnek a maximumát. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> last(m + 1, 0);
    vector<int> cnt(n + 1, 0);

    for (int day = 1; day <= n; ++day) {
        int x;
        cin >> x;
        if (last[x] != 0) {
            ++cnt[day - last[x]];
        }
        last[x] = day;
    }

    int best = 0;
    for (int d = 1; d <= n; ++d) {
        best = max(best, cnt[d]);
    }
    cout << best << '\n';
    return 0;
}
