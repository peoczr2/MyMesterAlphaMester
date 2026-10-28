/*
Megoldás lényege:
A ranglistát egy tömbben tároljuk, és verseny után csak azoknak a versenyzőknek a helyzete változik, akik az eddigi legjobb pontszámukat javították. Ezeket pontszám szerint csökkenő sorrendbe rendezzük, majd a régi lista és az új elemek összefésülésével kapjuk az új ranglistát. Egy régi versenyző akkor marad a javított versenyző előtt, ha a pontszáma nagyobb vagy egyenlő, ezért egyenlő pontszámnál a korábban elért eredmény marad előrébb. A helyezéseket az új lista egyetlen bejárásával számoljuk, és a versenyen indulókat azonosító szerint rendezve írjuk ki. Egy verseny O(N) időben fut, így az összes verseny O(M*N) időben, ahol M legfeljebb 100.
*/
/*
Hint 1: || A verseny után csak azok változhatnak meg, akik a saját legjobb pontszámukat javították. A többi versenyző egymáshoz viszonyított sorrendje nem módosul. ||
Hint 2: || Tartsd a ranglistát egy listában, és az új pontszámú versenyzőket összefésüléssel szúrd be a megfelelő helyre. Két egyenlő pontszám között a korábban elért eredmény áll előrébb. ||
Hint 3: || Az összefésülés után a lista sorszáma adja az új helyezést: egy bejárással minden versenyző helyét meg tudod határozni. Az indulókat azonosító szerint rendezve írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> pont(n + 1, 0);    // versenyző eddigi legjobb pontszáma
    vector<int> sorrend(n);        // az aktuális ranglista azonosítói, az előrébb álló elöl van
    for (int i = 0; i < n; i++) {
        int v, p;
        cin >> v >> p;
        sorrend[i] = v;
        pont[v] = p;
    }

    vector<char> valtozott(n + 1, 0);  // az adott versenyben javított legjobb pontszámot
    vector<int> hely(n + 1, 0);

    for (int j = 1; j <= m; j++) {
        int ind;
        cin >> ind;
        vector<pair<int, int>> indulo(ind);  // (azonosító, pontszám)
        for (auto& [id, s] : indulo) cin >> id >> s;

        vector<int> frissult;  // a legjobb pontszámukat javító versenyzők
        for (auto& [id, s] : indulo) {
            if (s > pont[id]) {
                pont[id] = s;
                valtozott[id] = 1;
                frissult.push_back(id);
            }
        }
        sort(frissult.begin(), frissult.end(), [&](int a, int b) { return pont[a] > pont[b]; });

        // összefésülés: a régi (nem változott) versenyzők sorrendje megmarad
        vector<int> uj;
        uj.reserve(n);
        size_t c = 0;
        for (int u : sorrend) {
            if (valtozott[u]) continue;
            while (c < frissult.size() && pont[frissult[c]] > pont[u]) uj.push_back(frissult[c++]);
            uj.push_back(u);
        }
        while (c < frissult.size()) uj.push_back(frissult[c++]);
        sorrend.swap(uj);

        for (int id : frissult) valtozott[id] = 0;

        for (int i = 0; i < n; i++) hely[sorrend[i]] = i + 1;

        sort(indulo.begin(), indulo.end());
        cout << ind << '\n';
        for (auto& [id, s] : indulo) cout << id << ' ' << hely[id] << '\n';
    }
    return 0;
}
