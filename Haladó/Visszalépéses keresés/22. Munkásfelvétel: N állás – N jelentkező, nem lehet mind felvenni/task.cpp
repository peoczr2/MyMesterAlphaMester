/*
Megoldás lényege: a feladat a munkások és az állások maximális méretű párosítása, a maximum számú párosítások közül pedig a legolcsóbbat keressük.
Ezt min-költségű folyammal oldjuk meg: a forrásból a munkásokba, onnan az ajánlott állásokba (az ajánlat költségével) és az állásokból a nyelőbe vezető élek kapacitása 1.
A successive shortest path módszer (Dijkstra potenciálokkal) minden lépésben a legolcsóbb augmentáló utat növeli, így a k-adik lépés után a folyam a k méretű legolcsóbb párosítás.
Ezért a folyam végén kapott érték a felvehető munkások maximális száma, a hozzá tartozó költség pedig ennek legkisebb ára.
A nem telíthető állások és munkások így természetesen kimaradnak, nem kell külön kezelni őket.
Időigény: N ≤ 35 esetén legfeljebb N augmentáló lépés, mindegyik O(E log V), ami bőven gyors.
*/
/*
Hint 1: || Először a lehető legtöbb munkást kell beosztani: a párosítás méretét kell maximalizálni, és csak utána az összköltséget. ||
Hint 2: || Ha a folyamot lépésenként növeljük, a legolcsóbb növelő úttal haladunk, és a kapott költség az adott méretű párosítás legkisebb ára. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<pair<int,int>>> ajanlatok(n);
    for (int i = 0; i < n; ++i) {
        int db;
        cin >> db;
        for (int j = 0; j < db; ++j) {
            int job, cost;
            cin >> job >> cost;
            ajanlatok[i].push_back({job - 1, cost});
        }
    }
    int S = 0, worker0 = 1, job0 = 1 + n, T = 1 + n + n;
    MinCostMaxFlow mcmf(T + 1);
    for (int i = 0; i < n; ++i) mcmf.addEdge(S, worker0 + i, 1, 0);
    for (int j = 0; j < n; ++j) mcmf.addEdge(job0 + j, T, 1, 0);
    for (int i = 0; i < n; ++i) for (auto [job, cost] : ajanlatok[i]) mcmf.addEdge(worker0 + i, job0 + job, 1, cost);
    auto [flow, cost] = mcmf.minCostMaxFlow(S, T, n);
    cout << flow << '\n' << cost << '\n';
    return 0;
}