/*
Megoldás lényege:
Két egymás utáni A-előfordulás közötti szakaszban meg kell számolni, hány elem kisebb B-nél. Ezt a szakasz darabszám-tömbjének előtagösszegeivel kapjuk meg: az 1..B-1 értékű elemek darabszámának összege. Minden (A, B) párra a szakaszok közül a legnagyobb ilyen összeget tartjuk meg. Egy A-értékre elég egyszer végigmenni a sorozaton, a szakaszok hossza összesen legfeljebb N, és minden szakaszban az M darab értéket egyszerre kezeljük. Mivel M legfeljebb 100, az eredmények egy M×M-es táblázatba férnek, így a K kérdés már csak kiolvasás. Az idő O(N·M).
Ha egy A-értéknek nincs két egymás utáni előfordulása, a hozzá tartozó válasz 0.
*/
/*
Hint 1: || Két egymás utáni A közötti elemeket kell vizsgálni, és minden szakaszban azt kell megszámolni, hány elem kisebb B-nél. ||
Hint 2: || A B-nél kisebb elemek száma a szakasz darabszám-tömbjének előtagösszege: az 1..B-1 értékek darabszámainak összege. ||
Hint 3: || Ha az A-értékekre egyenként végigmész a sorozaton, és az összes B-re egyszerre számolsz, a K kérdés már csak kiolvasás a kész táblázatból. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> s(n);
    for (int &x : s) cin >> x;

    // pos[a]: az a értékű elemek indexei növekvő sorrendben
    vector<vector<int>> pos(m + 1);
    for (int i = 0; i < n; i++) pos[s[i]].push_back(i);

    // best[a][b]: a legnagyobb számú B-nél kisebb elem két egymás utáni a között
    vector<vector<int>> best(m + 1, vector<int>(m + 1, 0));
    vector<int> cnt(m + 1);

    for (int a = 1; a <= m; a++) {
        const vector<int> &p = pos[a];
        for (size_t j = 0; j + 1 < p.size(); j++) {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = p[j] + 1; i < p[j + 1]; i++) cnt[s[i]]++;
            int less = 0;  // az 1..b-1 értékű elemek száma a szakaszban
            for (int b = 1; b <= m; b++) {
                best[a][b] = max(best[a][b], less);
                less += cnt[b];
            }
        }
    }

    for (int q = 0; q < k; q++) {
        int a, b;
        cin >> a >> b;
        cout << best[a][b] << "\n";
    }
    return 0;
}
