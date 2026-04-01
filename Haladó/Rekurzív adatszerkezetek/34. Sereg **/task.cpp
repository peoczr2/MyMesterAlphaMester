/*
Megoldási ötlet:
Az évek során csak új katonák lépnek be, a parancsnoki viszonyok pedig rögzítettek. Ezért minden kért
adat karbantartható egyetlen balról jobbra bejárással, mert a bemenet a belépés éve szerint rendezett.

Ha egy új katona a `p` felettese alá kerül, akkor:
- a mélysége `depth[p]+1`;
- a teljes zsold `10 + depth[u]` értékkel nő, mert az új katonának 10 arany jár, és minden őse
  kap még +1-et miatta, összesen `depth[u]` darabot;
- a levelek száma eggyel nő, de ha `p` eddig levél volt, akkor ő ezt elveszti, így ilyenkor nettó nem változik;
- `p` közvetlen beosztottjainak száma eggyel nő, ebből frissíthető a maximum;
- a zsoldosztás utolsó napja a maximális mélység + 1.

Az első év elején csak az 1-es katona van a seregben, ebből indulunk, majd évenként hozzáadjuk az adott évben
belépő katonákat, és kiírjuk az aktuális négy statisztikát.
*/
/*
Hint 1: || Az összes „nem csak közvetlen beosztott” összege ugyanaz, mint a katonák mélységének összege. ||
Hint 2: || Egy új katona pontosan akkor nem növeli a levélszámot, ha a felettese addig levél volt. ||
Hint 3: || A zsoldosztás annyi napig tart, ahány szintje van az aktuális fának, tehát a legnagyobb mélységhez csak 1-et kell hozzáadni. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, h;
    cin >> n >> h;

    vector<int> entryYear(n + 1, h + 1);
    vector<int> boss(n + 1, 0);
    for (int soldier = 2; soldier <= n; ++soldier) {
        cin >> entryYear[soldier] >> boss[soldier];
    }

    vector<int> depth(n + 1, 0);
    vector<int> directChildren(n + 1, 0);
    vector<char> isLeaf(n + 1, false);

    int activeSoldiers = 1;
    long long totalPay = 10;
    int leafCount = 1;
    int bestCommander = 1;
    int maxDepth = 0;
    isLeaf[1] = true;

    int nextSoldier = 2;
    for (int year = 1; year <= h; ++year) {
        while (nextSoldier <= n && entryYear[nextSoldier] == year) {
            int parent = boss[nextSoldier];
            depth[nextSoldier] = depth[parent] + 1;
            ++activeSoldiers;
            totalPay += 10 + depth[nextSoldier];

            ++leafCount;
            if (isLeaf[parent]) {
                isLeaf[parent] = false;
                --leafCount;
            }
            isLeaf[nextSoldier] = true;

            ++directChildren[parent];
            if (directChildren[parent] > directChildren[bestCommander] ||
                (directChildren[parent] == directChildren[bestCommander] && parent < bestCommander)) {
                bestCommander = parent;
            }

            if (depth[nextSoldier] > maxDepth) {
                maxDepth = depth[nextSoldier];
            }

            ++nextSoldier;
        }

        cout << totalPay << ' ' << leafCount << ' ' << bestCommander << ' ' << (maxDepth + 1) << '\n';
    }

    return 0;
}