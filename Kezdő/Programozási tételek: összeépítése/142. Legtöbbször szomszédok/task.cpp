/*
Megoldás lényege:
A pontszámok legfeljebb 10 000-esek, ezért a már pontot kapott versenyzők pontszámait rendezett halmazban (set) tartjuk. Minden t >= M ugrás után Őrült Ló S pontszámánál nagyobb pontszámok közül a legkisebb értékűek állnak közvetlenül előtte, a S-nél kisebbek közül a legnagyobb értékűek pedig közvetlenül utána; ezeket a pontszámokhoz tartozó számlálóval egyet növelünk. Egy versenyző végeredménye a pontszáma végső számlálójából adódik, amelyből levonjuk a saját ugrásakor mért értéket, mert addig még nem volt a rangsorban. Így minden versenyző O(1) alatt kiértékelhető, az időigény O(N log P), ahol P a pontszámok legnagyobb értéke.
*/
/*
Hint 1: || A pontszámok legfeljebb 10 000-ig terjednek, így a jelenleg előforduló pontszámokat rendezett halmazban tarthatod, és az ugrás utáni "legközelebbi nagyobb" és "legközelebbi kisebb" pontszám gyorsan megtalálható. ||
Hint 2: || Minden t >= M ugrás után elég Őrült Ló pontszámánál (S) nagyobb pontszámok közül a legkisebb értéket megnézni: az ezt a pontszámot kapó versenyzők állnak közvetlenül előtte. A "közvetlenül utána" oldalra ugyanez a gondolat a S-nél kisebb legnagyobb értékkel. ||
Hint 3: || A pontszámonkénti számlálók végső értékéből vond ki azt az értéket, ami a versenyző saját ugrásakor volt a pontszámához. Így csak a versenyző ugrása utáni időpontok számítanak, és a legtöbbször előforduló, egyenlőség esetén legkisebb rajtszámú versenyzőt kell kiválasztani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> p(n + 1);
    for (int i = 1; i <= n; i++) cin >> p[i];

    const int MAXP = 10000;
    vector<long long> cntBefore(MAXP + 1, 0), cntAfter(MAXP + 1, 0);
    vector<long long> baseBefore(n + 1, 0), baseAfter(n + 1, 0);
    vector<char> present(MAXP + 1, 0);
    set<int> scores;
    int sm = p[m];

    for (int t = 1; t <= n; t++) {
        baseBefore[t] = cntBefore[p[t]];
        baseAfter[t] = cntAfter[p[t]];
        if (!present[p[t]]) {
            present[p[t]] = 1;
            scores.insert(p[t]);
        }
        if (t >= m) {
            auto up = scores.upper_bound(sm);
            if (up != scores.end()) cntBefore[*up]++;
            auto down = scores.lower_bound(sm);
            if (down != scores.begin()) cntAfter[*prev(down)]++;
        }
    }

    long long bestB = 0, bestA = 0;
    int idB = -1, idA = -1;
    for (int j = 1; j <= n; j++) {
        long long cb = cntBefore[p[j]] - baseBefore[j];
        if (cb > bestB) {
            bestB = cb;
            idB = j;
        }
        long long ca = cntAfter[p[j]] - baseAfter[j];
        if (ca > bestA) {
            bestA = ca;
            idA = j;
        }
    }

    if (idB == -1) cout << -1 << "\n";
    else cout << idB << " " << bestB << "\n";
    if (idA == -1) cout << -1 << "\n";
    else cout << idA << " " << bestA << "\n";
    return 0;
}
