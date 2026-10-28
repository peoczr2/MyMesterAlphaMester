/*
    A páciensek érkezési sorrendben kerülnek ellátásra, így minden beteg kezdési
    ideje az előző kezelés végének és a saját érkezésének maximuma. A várakozási
    idő a kezdési idő és az érkezés különbsége. A várakozók száma az
    [érkezés, kezdés) félig nyílt intervallumok átfedése: sweep line-nal számoljuk,
    az érkezéseket +1, a kezdéseket -1 eseménynek véve. Azonos időpontban előbb a
    -1 eseményeket dolgozzuk fel, mert a kezdett kezelés már nem várakozás.
    Időigény: O(N log N).
*/
/*
Hint 1: || Egy beteg kezdési ideje az érkezése és az előző beteg kezelésének vége közül a későbbi. A várakozása ebből a saját érkezési idejének levonásával adódik. ||
Hint 2: || A várakozás egy [érkezés, kezdés) időintervallum. Rendezd az eseményeket időpont szerint: az érkezés +1, a kezdés -1, és azonos időpontban a -1 kerüljön előre. Az összegzett érték maximuma adja a B kérdés válaszát. ||
Hint 3: || Akinek a várakozása 0, azt nem kell az eseménysorba tenni, mert üres az intervallum. Az A kérdésnél elég egy bejárás a maximális várakozás keresésére, egyenlőség esetén a kisebb sorszám marad. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> er(n + 1), kez(n + 1);
    for (int i = 1; i <= n; ++i) cin >> er[i] >> kez[i];

    vector<int> start(n + 1), vege(n + 1), var(n + 1);
    int cur = 0;
    for (int i = 1; i <= n; ++i) {
        start[i] = max(cur, er[i]);
        var[i] = start[i] - er[i];
        cur = start[i] + kez[i];
    }

    int bestId = 0, bestWait = 0;
    for (int i = 1; i <= n; ++i) {
        if (var[i] > bestWait) {
            bestWait = var[i];
            bestId = i;
        }
    }

    vector<pair<int, int>> es;
    for (int i = 1; i <= n; ++i) {
        if (var[i] > 0) {
            es.push_back({er[i], 1});
            es.push_back({start[i], -1});
        }
    }
    sort(es.begin(), es.end(), [](auto& a, auto& b) {
        if (a.first != b.first) return a.first < b.first;
        return a.second < b.second; // -1 előbb, mint +1
    });
    int akt = 0, maxWaiters = 0;
    for (auto [t, d] : es) {
        akt += d;
        maxWaiters = max(maxWaiters, akt);
    }

    cout << bestId << '\n' << maxWaiters << '\n';
    return 0;
}