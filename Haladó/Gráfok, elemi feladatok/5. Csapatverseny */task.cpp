/*
Megoldás lényege:
A csapatokat irányított gráf csúcsainak tekintjük: i -> j él, ha az i. csapat legyőzte a j.-ediket.
A. Két csapat, amely már legyőzte egymást: ha i -> j és j -> i is van, akkor ez egy 2 hosszú kör. Ezek közül a
lexikografikusan legkisebb párt (kisebb sorszám előre) írjuk ki: O(N^2) mátrixszal könnyen megvan.
B. Azok a csapatok, amelyek játszottak (van mérkőzésük), de senki sem győzte le őket: a bejövő élek száma 0.
Ezeket növekvő sorrendben írjuk ki.
C. Olyan csapat, amely „közvetve” legyőzte magát: a csapat legalább 3 hosszú körön van (A legyőzte B-t, B legyőzte
C-t, C legyőzte A-t, ...). Egy v csapatra ilyen kör akkor van, ha van v-ből kimenő w és v-be bejövő u csapat, w != u,
és van w-ből u-ba út, amely nem megy át v-n. Ezt minden v-re egy bejárással ellenőrizzük: a v kimenő szomszédaiból
egyszerre indulunk, és minden csúcsnál legfeljebb két különböző kezdőpontot jegyzünk meg. Egy bejövő u szomszédra
akkor van kör, ha u-t a kezdőpontok közül legalább egy, u-tól különböző kezdőpont eléri. A teljes munka O(N*(N+M)).
Az első ilyen v-t írjuk ki.
Ha egyik kérdésre sincs megfelelő csapat, az adott sor üres marad.
*/
/*
Hint 1: || Irányított gráfként gondolj a csapatokra: a kölcsönös győzelem 2 hosszú kör, a keresett csapat pedig legalább 3 hosszú körön van. ||
Hint 2: || Egy v csapatra akkor van ilyen kör, ha van belőle kimenő w és bejövő u, w != u, és w-ből u-ba út vezet v megkerülésével; ezt minden v-re egy bejárással ellenőrizheted, ha minden csúcsnál legfeljebb két különböző kezdőpontot jegyzel meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<char>> beat(n + 1, vector<char>(n + 1, 0));
    vector<vector<int>> out(n + 1);
    vector<char> played(n + 1, 0), lost(n + 1, 0);
    for (int k = 0; k < m; ++k) {
        int i, j;
        cin >> i >> j;
        if (!beat[i][j]) {
            beat[i][j] = 1;
            out[i].push_back(j);
        }
        played[i] = played[j] = 1;
        lost[j] = 1;
    }

    // A: legkisebb (i, j) pár, i < j, amely kölcsönösen legyőzte egymást
    int pa = -1, pb = -1;
    for (int i = 1; i <= n; ++i) {
        for (int j = i + 1; j <= n; ++j) {
            if (beat[i][j] && beat[j][i]) {
                pa = i;
                pb = j;
                break;
            }
        }
        if (pa != -1) break;
    }

    // B: játszottak, de senki nem győzte le őket
    vector<int> bList;
    for (int v = 1; v <= n; ++v) {
        if (played[v] && !lost[v]) {
            bList.push_back(v);
        }
    }

    // C: legkisebb csúcs, amely 3 vagy hosszabb körön van
    int cAns = -1;
    vector<int> L1(n + 1), L2(n + 1);
    vector<pair<int, int>> q;
    q.reserve(2 * n + 2);
    for (int v = 1; v <= n && cAns == -1; ++v) {
        vector<int> sources = out[v];
        if (sources.empty()) continue;
        bool hasIn = false;
        for (int u = 1; u <= n; ++u) {
            if (beat[u][v]) {
                hasIn = true;
                break;
            }
        }
        if (!hasIn) continue;

        fill(L1.begin(), L1.end(), -1);
        fill(L2.begin(), L2.end(), -1);
        q.clear();
        for (int w : sources) {
            L1[w] = w;
            q.push_back({w, w});
        }
        for (size_t h = 0; h < q.size(); ++h) {
            auto [x, s] = q[h];
            for (int y : out[x]) {
                if (y == v) continue;
                if (L1[y] == -1) {
                    L1[y] = s;
                    q.push_back({y, s});
                } else if (L1[y] != s && L2[y] == -1) {
                    L2[y] = s;
                    q.push_back({y, s});
                }
            }
        }

        for (int u = 1; u <= n; ++u) {
            if (!beat[u][v]) continue;
            bool isSource = beat[v][u];
            bool ok = isSource ? (L2[u] != -1) : (L1[u] != -1);
            if (ok) {
                cAns = v;
                break;
            }
        }
    }

    if (pa != -1) {
        cout << pa << ' ' << pb << '\n';
    } else {
        cout << '\n';
    }
    for (size_t i = 0; i < bList.size(); ++i) {
        cout << bList[i] << (i + 1 == bList.size() ? '\n' : ' ');
    }
    if (bList.empty()) cout << '\n';
    if (cAns != -1) {
        cout << cAns << '\n';
    } else {
        cout << '\n';
    }
    return 0;
}
