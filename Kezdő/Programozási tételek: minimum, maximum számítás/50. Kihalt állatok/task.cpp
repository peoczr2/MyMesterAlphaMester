/*
Megoldás lényege:
Minden fajhoz tartozik egy [U, E] intervallum: a faj az U és az E évvel ezelőtt közötti években élt. A két kort kisebb-nagyobb sorrendbe rendezzük, mert a bemenetben a sorrend nem garantált. Az intervallumok határait egy különbségi tömbbe írjuk (U helyén +1, E+1 helyén -1), majd a prefixösszegekkel minden k korra megkapjuk, hány faj élt akkor. Az egyenlőség esetén a nagyobb k-t tartjuk meg, mert a legrégebbi kort kell kiírni. Az időigény O(N + M), a memóriaigény O(M).
*/
/*
Hint 1: || Minden faj egy intervallum: nem kell év-évenként végigszámolni, elég az intervallum két végpontját feljegyezni. ||
Hint 2: || Használj különbségi tömböt: az U indexén növeld, az E+1 indexén csökkentsd eggyel az értéket, majd a prefixösszeggel minden évre megkapod az akkor élő fajok számát. Ügyelj arra, hogy egyenlőség esetén a nagyobb kort válaszd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    vector<int> kulonbseg(m + 2, 0);
    for (int i = 0; i < n; i++) {
        int u, e;
        cin >> u >> e;
        if (u > e) {
            swap(u, e);
        }
        kulonbseg[u]++;
        kulonbseg[e + 1]--;
    }

    int elo = 0;
    int legtobb = 0;
    int legregebbi = 0;
    for (int k = 1; k <= m; k++) {
        elo += kulonbseg[k];
        if (elo >= legtobb) {
            legtobb = elo;
            legregebbi = k;
        }
    }

    cout << legtobb << "\n" << legregebbi << "\n";
    return 0;
}
