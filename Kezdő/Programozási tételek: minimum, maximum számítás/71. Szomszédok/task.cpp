/*
Megoldás lényege:
Két egymás utáni A-előfordulás közötti szakaszban megszámoljuk, hány darab B érték van, és minden (A, B) párra a szakaszok közül a legnagyobb darabszámot tartjuk meg. Egy A-értékre elég egyszer végigmenni a sorozaton: a szakaszok hossza összesen legfeljebb N, és minden szakaszban az M darab értéket egyszerre kezeljük. Mivel M legfeljebb 100, az összes (A, B) pár eredménye egy M×M-es táblázatba fér, így a K kérdés már csak kiolvasás. Az idő O(N·M), ami legfeljebb néhány tízmillió művelet.
Ha egy A-értéknek nincs két egymás utáni előfordulása, a hozzá tartozó válasz 0.
*/
/*
Hint 1: || Csak az A értékű elemek számítanak: két egymás utáni A-előfordulás közötti szakasz a vizsgált terület. ||
Hint 2: || Egy szakaszban a B értékű elemek darabszámát egy darabszám-tömb (hisztogram) adja meg; minden B-re a szakaszok közül a legnagyobb darabszámot kell megtartani. ||
Hint 3: || Mivel K kérdés van, ne számold újra a sorozatot minden kérdésre: az A-értékek szerint dolgozz, és az eredményt táblázatban tárold. ||
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

    // best[a][b]: a legnagyobb számú b értékű elem két egymás utáni a között
    vector<vector<int>> best(m + 1, vector<int>(m + 1, 0));
    vector<int> cnt(m + 1);

    for (int a = 1; a <= m; a++) {
        const vector<int> &p = pos[a];
        for (size_t j = 0; j + 1 < p.size(); j++) {
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = p[j] + 1; i < p[j + 1]; i++) cnt[s[i]]++;
            for (int b = 1; b <= m; b++) best[a][b] = max(best[a][b], cnt[b]);
        }
    }

    for (int q = 0; q < k; q++) {
        int a, b;
        cin >> a >> b;
        cout << best[a][b] << "\n";
    }
    return 0;
}
