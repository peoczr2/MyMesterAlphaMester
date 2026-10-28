/*
Megoldás lényege:
Minden karaván útját időben követjük: az első oázisból a megadott napon indul, és minden úton a szakasz hosszának megfelelő ideig halad.
Az első és az utolsó oázisban nincs szállásigény, a köztes oázisokban viszont a karaván egy napot marad, így a következő indulás az érkezés napjánál eggyel később van.
Egy köztes érkezés napja és az azt követő nap két éjszakát foglal le, ezért két karaván pontosan akkor tölt együtt éjszakát ugyanabban az oázisban, ha érkezési napjaik különbsége legfeljebb 1.
A köztes érkezéseket oázisonként gyűjtjük, majd minden oázison páronként összevetjük őket, és a találkozó karavánpárokat logikai mátrixban jelöljük.
A válasz soronként a találkozó karavánok száma. Az idő O(N·K²), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Szimuláld minden karaván útját időben: az első oázisból a megadott napon indulsz, és minden út az adott hosszúságú szakasznak megfelelő ideig tart. Az első és az utolsó oázisban nincs szállásigény. ||
Hint 2: || Köztes oázisban az érkezés után a karaván egy napot marad, így a következő út a rákövetkező napon indul. Az érkezési naphoz tartozó két éjszaka az érkezési nap és az azt követő nap. ||
Hint 3: || Oázisonként gyűjtsd össze a köztes érkezéseket (karaván, nap) párokként. Két karaván akkor találkozik, ha ugyanabban az oázisban az érkezési napjaik legfeljebb 1-gyel térnek el, és ezt logikai mátrixban rögzítsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    const long long INF = 1000000000000000LL;
    vector<vector<long long>> w(n + 1, vector<long long>(n + 1, INF));
    for (int i = 0; i < m; i++) {
        int a, b;
        long long h;
        cin >> a >> b >> h;
        w[a][b] = min(w[a][b], h);
        w[b][a] = min(w[b][a], h);
    }

    // at[v]: (karaván sorszáma, érkezési nap) a köztes oázisokban
    vector<vector<pair<int, long long>>> at(n + 1);
    for (int i = 0; i < k; i++) {
        long long nap;
        int o;
        cin >> nap >> o;
        vector<int> s(o);
        for (int &x : s) cin >> x;

        long long t = nap;
        for (int j = 1; j < o; j++) {
            t += w[s[j - 1]][s[j]];          // megérkezés az s[j] oázisba
            if (j < o - 1) {                 // köztes oázis: szállás, és egy nap ott
                at[s[j]].push_back({i, t});
                t += 1;
            }
        }
    }

    vector<vector<char>> meet(k, vector<char>(k, 0));
    for (int v = 1; v <= n; v++) {
        const auto &L = at[v];
        for (size_t p = 0; p < L.size(); p++) {
            for (size_t q = p + 1; q < L.size(); q++) {
                if (L[p].first == L[q].first) continue;
                if (llabs(L[p].second - L[q].second) <= 1) {
                    meet[L[p].first][L[q].first] = 1;
                    meet[L[q].first][L[p].first] = 1;
                }
            }
        }
    }

    for (int i = 0; i < k; i++) {
        int cnt = 0;
        for (int j = 0; j < k; j++) cnt += meet[i][j];
        cout << cnt << '\n';
    }
    return 0;
}
