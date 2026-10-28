/*
Megoldás lényege:
A karavánok útját ugyanúgy szimuláljuk, mint a Karavánok találkozása feladatban: az első oázisból a megadott napon indulnak, minden úton a szakasz hosszának megfelelő ideig haladnak, és minden köztes oázisban egy napot maradnak.
Egy köztes érkezés napja és az azt követő nap két éjszakát foglal le, így egy d éjszakán az adott oázisban azok a karavánok alszanak, akiknek érkezési napja d-1 vagy d.
Oázisonként az érkezéseket napjuk szerint rendezzük, és minden lehetséges éjszakára (az érkezések napja és az azt követő nap) megszámoljuk a különböző karavánokat, akik ott egyszerre szálláson vannak.
Az oázisonkénti maximum adja a választ. Egy oázisban legfeljebb K érkezés van, így az idő O(N·K²·log K).
*/
/*
Hint 1: || Először ugyanúgy szimuláld az utakat, mint az előző feladatban: minden köztes oázisban kiszámolod az érkezési napot, és onnan a következő út a rákövetkező napon indul. ||
Hint 2: || Egy d éjszakát az a karaván tölt az oázisban, amelyiknek érkezési napja d-1 vagy d. Elég minden érkezési nap és a rákövetkező nap mint lehetséges éjszaka megnézni. ||
Hint 3: || Oázisonként rendezd az érkezéseket napjuk szerint, és egy adott éjszakához tartozó tartományban számold meg a különböző karavánokat, mert egy karaván ugyanazon éjszakán csak egyszer számít. ||
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

    // at[v]: (érkezési nap, karaván sorszáma) a köztes oázisokban
    vector<vector<pair<long long, int>>> at(n + 1);
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
                at[s[j]].push_back({t, i});
                t += 1;
            }
        }
    }

    for (int v = 1; v <= n; v++) {
        auto &L = at[v];
        sort(L.begin(), L.end());
        int best = 0;
        for (const auto &e : L) {
            // az e.first érkezés az e.first és e.first+1 éjszakát foglalja
            for (long long d : {e.first, e.first + 1}) {
                // azok az érkezések fedik a d éjszakát, amelyek napja d-1 vagy d
                auto lo = lower_bound(L.begin(), L.end(), make_pair(d - 1, -1));
                auto hi = upper_bound(L.begin(), L.end(), make_pair(d, INT_MAX));
                vector<int> ids;
                for (auto it = lo; it != hi; ++it) ids.push_back(it->second);
                sort(ids.begin(), ids.end());
                ids.erase(unique(ids.begin(), ids.end()), ids.end());
                best = max(best, (int)ids.size());
            }
        }
        cout << best << '\n';
    }
    return 0;
}
