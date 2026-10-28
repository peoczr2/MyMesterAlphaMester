/*
Megoldás lényege:
A ponthatárokat 60-tól indulva fokozatosan emeljük. Adott ponthatárok mellett minden jelentkező az első olyan szakra kerül, amelynek ponthatára nem nagyobb a pontszámánál, így a felvételek egyértelműen kiszámolhatók. Ha egy szakra a feltételek szerint túl sokan kerülnek be, a szak ponthatárát a következő, magasabb felvett pontszámra emeljük, így a legalacsonyabb pontszámú csoport kiesik, és a jelentkezői a következő választásukba kerülnek. Ezután a kiosztást újra kell számolni, mert a kiesettek másik szakokat is terhelhetnek. A ponthatárok csak nőnek és legfeljebb 121-ig mehetnek, ezért az eljárás véges: amikor egyik szak sem sérti a feltételeket, kész a megoldás. Egy kiosztás O(M·6) munka, a körök száma szakonként legfeljebb 61 emelés, így a futás belefér az időlimitbe.
*/
/*
Hint 1: || Minden szak ponthatárát 60-ról indítsd, és csak emeld. Egy jelentkező mindig az első olyan szakot kapja, ahol a ponthatár nem nagyobb a pontszámánál. ||
Hint 2: || Egy szakra a felvettek száma legyen c, és e az ezen a szakon a ponthatárt pontosan elérő pontszámú felvettek száma. A szak akkor megfelelő, ha c ≤ K, vagy ha c − e < K és egyszerre c ≤ ⌊1,1·K⌋ is teljesül. ||
Hint 3: || Ha egy szak nem felel meg, a ponthatárát emeld a legkisebb olyan felvett pontszámra, amely az eddigi ponthatárnál nagyobb. Ha ilyen nincs, a ponthatár legyen 121, azaz senkit ne vegyen fel. ||
Hint 4: || Ismételd a kiosztást és az emeléseket, amíg egyik szak sem változtat ponthatárt. A kimenetbe szakonként a felvettek legkisebb pontszáma kerül, ha nincs felvett, akkor 60. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> quota(n);
    for (int &x : quota) cin >> x;

    vector<int> score(m);
    vector<vector<int>> pref(m);
    string line;
    getline(cin, line);  // a keretszámokat tartalmazó sor vége
    for (int j = 0; j < m; j++) {
        do {
            if (!getline(cin, line)) break;
        } while (line.find_first_not_of(" \t\r") == string::npos);
        istringstream is(line);
        is >> score[j];
        int s;
        while (is >> s) pref[j].push_back(s - 1);
    }

    vector<int> thr(n, 60);  // aktuális ponthatár szakonként
    vector<int> assign(m, -1);
    while (true) {
        vector<int> cnt(n, 0), eq(n, 0), nxt(n, 121);
        for (int j = 0; j < m; j++) {
            assign[j] = -1;
            for (int s : pref[j]) {
                if (thr[s] <= score[j]) {
                    assign[j] = s;
                    break;
                }
            }
            if (assign[j] >= 0) {
                int s = assign[j];
                cnt[s]++;
                if (score[j] == thr[s])
                    eq[s]++;
                else
                    nxt[s] = min(nxt[s], score[j]);  // a következő magasabb felvett pontszám
            }
        }

        bool changed = false;
        for (int i = 0; i < n; i++) {
            int c = cnt[i];
            if (c == 0) continue;
            bool ok = c <= quota[i] || (c - eq[i] < quota[i] && c <= 110 * quota[i] / 100);
            if (!ok) {
                thr[i] = nxt[i];
                changed = true;
            }
        }
        if (!changed) break;
    }

    vector<int> best(n, INT_MAX);
    for (int j = 0; j < m; j++)
        if (assign[j] >= 0) best[assign[j]] = min(best[assign[j]], score[j]);
    for (int i = 0; i < n; i++)
        cout << (best[i] == INT_MAX ? 60 : best[i]) << (i + 1 < n ? ' ' : '\n');
    for (int j = 0; j < m; j++)
        cout << assign[j] + 1 << (j + 1 < m ? ' ' : '\n');
    return 0;
}
