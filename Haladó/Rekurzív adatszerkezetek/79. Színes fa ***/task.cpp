/*
Megoldás lényege:
Minden levél és a gyökér közötti út tartalmazza az összes színt, ezért a színek száma legfeljebb a legrövidebb gyökér-levél út csúcsszáma, vagyis a legkisebb levélmélység (m).
Ez el is érhető: a csúcsokat a mélységük szerint színezzük, a d mélységű csúcs színe m+1-min(d,m) legyen.
Minden levél mélysége legalább m, ezért egy csúcs ősei és a hozzá tartozó lefelé vezető úton minden mélység megjelenik, így minden szín előfordul.
Az időigény O(N), mert a mélységeket BFS-sel számoljuk ki.
*/
/*
Hint 1: || Vegyél egy levelet és a gyökérbe vezető utat: ezen az úton az összes színnek szerepelnie kell. Mit mond ez a színek számáról? ||
Hint 2: || Számold ki minden csúcs mélységét a gyökértől (a gyökér mélysége 1). A színek száma a levelek mélységének minimuma lesz. ||
Hint 3: || A színeket a mélység szerint oszthatod ki: a legmélyebb részen a csúcsok közös színt kaphatnak, a sekélyebbek mélységük szerint külön színt. Ellenőrizd, hogy minden csúcs őseinek és leszármazottainak együtt minden szín megjelenjen. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> par(n + 1, 0);
    vector<vector<int>> ch(n + 1);
    for (int i = 2; i <= n; ++i) {
        cin >> par[i];
        ch[par[i]].push_back(i);
    }

    // mélységek BFS-sel: a gyökér mélysége 1, a szülő sorszáma nem feltétlenül kisebb
    vector<int> depth(n + 1, 0), q{1};
    depth[1] = 1;
    for (size_t h = 0; h < q.size(); ++h) {
        int v = q[h];
        for (int c : ch[v]) {
            depth[c] = depth[v] + 1;
            q.push_back(c);
        }
    }

    int k = INT_MAX;
    for (int v = 1; v <= n; ++v)
        if (ch[v].empty()) k = min(k, depth[v]);

    cout << k << "\n";
    for (int v = 1; v <= n; ++v) {
        int col = k + 1 - min(depth[v], k);
        cout << col << (v == n ? '\n' : ' ');
    }
    return 0;
}
