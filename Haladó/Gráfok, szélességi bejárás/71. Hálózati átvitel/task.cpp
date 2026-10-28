/*
Megoldás lényege:
A gombok minden robotot ugyanúgy mozgatnak, ezért a robotok helyzete mindig városok egy halmaza, amelyet a gombok
függvényei egyre kisebbre szűkítenek. Ha bármely két várost össze lehet vonni valamilyen gombsorozattal, akkor a
teljes halmaz is egyetlen elemre szűkíthető: minden lépésben két különböző robot ugyanarra a helyre kerül, így a
halmaz mérete csökken. Ezért elég minden {x, y} várospárra megnézni, hogy összevonható-e. A párok gráfjában egy
lépés azt jelenti, hogy mindkét városra ugyanazt a gombot nyomjuk; a célállapotok az egyező (u, u) párok. Ezeket
visszafelé, a gombok fordított éleit követve szélességi bejárással járjuk be. A sorrend nem számít, ezért csak a
rendezett (a < b) párokat tároljuk. Ha minden különböző pár elérhető, IGEN, különben NEM. Az időigény tesztenként
O(N^2), N ≤ 500 mellett kb. 125 000 párral.
*/
/*
Hint 1: || Egy gomb minden robotot ugyanúgy mozgat, ezért a robotok helyzete városok halmaza, amelyet a gombok egyre kisebbre szűkítenek. A teljes halmaz pontosan akkor szűkíthető egyetlen elemre, ha bármely két várost össze lehet vonni. ||
Hint 2: || Egy (x, y) várospár akkor vonható össze, ha létezik olyan gombsorozat, amely után mindkettő ugyanott van. Ezt a párok gráfján kell keresni: egy lépés mindkét városra ugyanazt a gombot jelenti, a célok pedig az (u, u) párok. ||
Hint 3: || A párok gráfját visszafelé járd be: egy gomb fordított élei megmondják, mely városokból vezet a gomb u-ba. Az (u, v) párhoz tartozó előző párok ezekből a fordított élekből adódnak, mindkét tagra ugyanazzal a gombbal. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        // Visszafelé élek CSR formában: off[g][u] .. off[g][u+1] között lst[g]-ben azok a városok,
        // amelyek a g-edik gombbal u-ba jutnak (g = 0 zöld, 1 piros)
        vector<int> off[2], lst[2];
        for (int g = 0; g < 2; ++g) {
            vector<int> to(n);
            for (int i = 0; i < n; ++i) {
                cin >> to[i];
                --to[i];
            }
            off[g].assign(n + 1, 0);
            for (int i = 0; i < n; ++i) ++off[g][to[i] + 1];
            for (int u = 0; u < n; ++u) off[g][u + 1] += off[g][u];
            lst[g].assign(n, 0);
            vector<int> fill(off[g].begin(), off[g].end() - 1);
            for (int i = 0; i < n; ++i) lst[g][fill[to[i]]++] = i;
        }

        // ok[a * n + b]: az a és b városban lévő robotok valamilyen gombsorozattal összevonhatók (a < b)
        vector<unsigned char> ok((size_t)n * n, 0);
        const long long total = (long long)n * (n - 1) / 2;
        long long marked = 0;
        vector<pair<int, int>> qu;
        qu.reserve((size_t)n * (n + 1) / 2 + n);
        for (int i = 0; i < n; ++i) {
            ok[(size_t)i * n + i] = 1;
            qu.push_back({i, i});
        }
        for (size_t head = 0; head < qu.size() && marked < total; ++head) {
            auto [u, v] = qu[head];
            for (int g = 0; g < 2 && marked < total; ++g) {
                const int *xs = lst[g].data() + off[g][u], *xe = lst[g].data() + off[g][u + 1];
                const int *ys = lst[g].data() + off[g][v], *ye = lst[g].data() + off[g][v + 1];
                for (const int *px = xs; px != xe; ++px) {
                    int x = *px;
                    for (const int *py = ys; py != ye; ++py) {
                        int y = *py;
                        if (x == y) continue;
                        int a = x < y ? x : y, b = x ^ y ^ a;
                        size_t idx = (size_t)a * n + b;
                        if (!ok[idx]) {
                            ok[idx] = 1;
                            ++marked;
                            qu.push_back({a, b});
                        }
                    }
                }
            }
        }

        cout << (marked == total ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
