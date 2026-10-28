/*
Megoldás lényege:
Az ismeretségek kölcsönösek, ezért minden emberhez egy bitsetben tároljuk az ismerőseit (N ≤ 200).
B: egy pár (a, b) akkor kerül a listába, ha van közös ismerősük, vagyis az ismerőslistáik metszete nem üres. Ezt bitset-metszettel O(N/64) időben ellenőrizzük.
A: a pár minden ismerőse közös, ha a két listából kivéve a párt egymásra mutató bitet, a két lista megegyezik, és nem üres. Így a közvetlen ismeretség nem zavarja az egyezést.
A párokat a kisebb sorszámmal kezdve, két egymásba ágyazott ciklussal soroljuk fel, így a lexikografikus sorrend magától adódik.
Időigény: O(N^2 · N / 64), ami N ≤ 200 esetén bőven belefér.
*/
/*
Hint 1: || Két ember közös ismerőse a két ismerőslista metszetében van. Az ismerőslistákat érdemes bitsetben tárolni, így a metszet és az egyezés gyorsan ellenőrizhető. ||
Hint 2: || Az A feltételnél a két ember egymást is ismerheti. Ezt úgy kezeld, hogy a másik ember bitjét a listából kivéded, majd a két listát egyenlőségre vizsgálod, és ellenőrzöd, hogy nem üres-e. ||
Hint 3: || A párokat két egymásba ágyazott ciklussal, a kisebb sorszámút elsőnek véve, lexikografikus sorrendben kapod. A két listát külön gyűjtsd, és a darabszámot a párok előtt írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<bitset<256>> knows(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        knows[a][b] = 1;
        knows[b][a] = 1;
    }

    vector<pair<int, int>> same, common;
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            if ((knows[a] & knows[b]).any())
                common.push_back({a, b});

            bitset<256> ea = knows[a], eb = knows[b];
            ea[b] = 0;
            eb[a] = 0;
            if (ea == eb && ea.any())
                same.push_back({a, b});
        }
    }

    cout << same.size() << "\n";
    for (auto [a, b] : same)
        cout << a << " " << b << "\n";
    cout << common.size() << "\n";
    for (auto [a, b] : common)
        cout << a << " " << b << "\n";
    return 0;
}
