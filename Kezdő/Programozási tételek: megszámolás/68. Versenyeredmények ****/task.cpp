/*
Megoldás lényege:
Egy Ai érték két szomszédos előfordulása közötti rés elemeire vonatkozik a kérdés, ezért csak ezeket a réseket kell figyelembe venni.
Prefixösszegekkel egy résben a Bi-nél nem nagyobb elemek száma O(1) alatt megkapható: pre[i][b] az első i elem között a b-nél nem nagyobb értékek számát tárolja.
Ezért minden résre (összesen legfeljebb N-1 darab) végigmegyünk az összes b értéken (M darab), és az ans[a][b] táblázatban tároljuk a résekben kapott maximumot.
A táblázat felépítése így O(N·M), minden lekérdezés pedig már csak egy olvasás, így az összidő O(N·M + K), ami N ≤ 10 000 és M ≤ 100 mellett kb. 10^6 művelet.
*/
/*
Hint 1: || Egy Ai értékre csak a két egymás utáni előfordulása közötti elemek számítanak, mert a kérdés ezekre a réseken belüli elemekre vonatkozik. Nem kell minden lekérdezésnél újra az egész sorozatot bejárni. ||
Hint 2: || Készíts prefixösszeg-tömböt: pre[i][b] legyen az első i elem között a b-nél nem nagyobb értékek száma. Egy p és q közötti résben (p < q) a keresett szám pre[q-1][b] - pre[p][b]. ||
Hint 3: || Minden értékhez járd végig az előfordulásai közötti réseket, és minden b-re tartsd nyilván a résekben kapott legnagyobb értéket az ans[a][b] táblázatban. Ha egy a értéknek kevesebb mint két előfordulása van, az ans[a][b] marad -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<int> v(n + 1);
    for (int i = 1; i <= n; i++) cin >> v[i];

    // pre[i][b] = az 1..i elemek közül hány darab nem nagyobb, mint b
    vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; i++) {
        for (int b = 0; b <= m; b++) {
            pre[i][b] = pre[i - 1][b] + (v[i] <= b ? 1 : 0);
        }
    }

    // pos[a] = az a érték előfordulásainak helyei
    vector<vector<int>> pos(m + 1);
    for (int i = 1; i <= n; i++) pos[v[i]].push_back(i);

    // ans[a][b] = az a két egymás utáni előfordulása közötti résekben a b-nél nem nagyobb elemek maximális száma
    vector<vector<int>> ans(m + 1, vector<int>(m + 1, -1));
    for (int a = 0; a <= m; a++) {
        for (size_t j = 1; j < pos[a].size(); j++) {
            int p = pos[a][j - 1];
            int q = pos[a][j];
            for (int b = 0; b <= m; b++) {
                ans[a][b] = max(ans[a][b], pre[q - 1][b] - pre[p][b]);
            }
        }
    }

    while (k--) {
        int a, b;
        cin >> a >> b;
        cout << ans[a][b] << "\n";
    }
    return 0;
}
