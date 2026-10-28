/*
Megoldás lényege:
Minden versenyen megkeressük a legnagyobb elért pontszámot, és az ezt elérő tanulókat győztesnek tekintjük. Döntetlen esetén több győztes is van, és mindegyik győzelme beleszámít. A tanulónkénti győzelemszámokat összegezzük, majd a győztesek listáját a győzelemszám szerint csökkenő, azon belül a sorszám szerint növekvő sorrendbe rendezzük. A pontokat N×M-es táblázatban tároljuk (-1 jelöli, ha valaki nem indult), így az egész megoldás O(N·M) időben fut, ami a korlátok mellett bőven elég.
A minimális pontszámok az egyéni versenyek győzteseinek meghatározásához nem kellenek, ezért csak beolvassuk őket.
*/
/*
Hint 1: || Versenyenként keresd meg a legnagyobb elért pontszámot. A győztes az, aki ezt a pontot elérte, így döntetlennél több tanuló is nyer. ||
Hint 2: || Tanulónként számold a győzelmeket, majd a győztesekből készíts egy pair vektort: az első elem a negált győzelemszám, a második a sorszám. A sort() ezzel a kívánt sorrendet adja. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    // A minimumokat az egyéni versenyeknél nem használjuk, csak beolvassuk őket
    for (int j = 0; j < m; j++) {
        int minimum;
        cin >> minimum;
    }

    // pont[s][j]: az s. tanuló pontszáma a j. versenyen, -1, ha nem indult
    vector<vector<int>> pont(n + 1, vector<int>(m, -1));
    for (int j = 0; j < m; j++) {
        int indulok;
        cin >> indulok;
        for (int k = 0; k < indulok; k++) {
            int s, p;
            cin >> s >> p;
            pont[s][j] = p;
        }
    }

    // Versenyenként a legnagyobb pont, és az ezt elérők győzelmet kapnak
    vector<int> gyozelem(n + 1, 0);
    for (int j = 0; j < m; j++) {
        int legjobb = 0;
        for (int s = 1; s <= n; s++) {
            legjobb = max(legjobb, pont[s][j]);
        }
        for (int s = 1; s <= n; s++) {
            if (pont[s][j] == legjobb) {
                gyozelem[s]++;
            }
        }
    }

    // Rendezés: előbb a több győzelem, azonos esetén a kisebb sorszám
    vector<pair<int, int>> rangsor;
    for (int s = 1; s <= n; s++) {
        if (gyozelem[s] > 0) {
            rangsor.push_back({-gyozelem[s], s});
        }
    }
    sort(rangsor.begin(), rangsor.end());

    cout << rangsor.size();
    for (const auto &p : rangsor) {
        cout << ' ' << p.second;
    }
    cout << '\n';
    return 0;
}
