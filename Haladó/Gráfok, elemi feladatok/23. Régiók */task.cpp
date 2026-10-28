/*
Megoldás lényege:
Két település pontosan akkor kerül azonos régióba, ha a Manhattan-távolság szerint legfeljebb T távolságú élekből álló gráfban összefüggő a kapcsolatuk, így a régiók a komponensek.
A gráfot nem építjük fel explicit módon: szélességi bejárással haladunk, és minden felfedezett településhez a még nem látogatott települések közül kiválogatjuk a T-n belül lévőket.
A bejárás mindig a legkisebb, még nem látogatott sorszámú településből indul, így a régiók a legkisebb tagjuk szerint növekvő sorrendben keletkeznek.
A régiók tagjait kiírás előtt rendezzük; mivel N legfeljebb 7000, az O(N^2) időigény a korláton belül marad.
*/
/*
Hint 1: || Két település akkor kerül egy régióba, ha lépésekkel eljuthatsz közöttük úgy, hogy a szomszédos települések távolsága legfeljebb T; ez egy összefüggő komponens keresése. ||
Hint 2: || Nem kell élek listáját felépítened: szélességi bejárásnál a sorban álló település és a még nem látogatott települések távolságát egyszerűen kiszámolod, és a közelieket sorba állítod. ||
Hint 3: || Ha a komponenseket mindig a legkisebb nem látogatott sorszámtól keresed, a régiók sorrendje adódik; a régión belüli sorrendhez a tagokat még rendezd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, t;
    cin >> n >> t;
    vector<int> x(n), y(n);
    for (int i = 0; i < n; i++) cin >> x[i] >> y[i];

    // rem: a még nem látogatott települések, növekvő sorrendben
    vector<int> rem(n);
    iota(rem.begin(), rem.end(), 0);

    vector<vector<int>> regions;
    while (!rem.empty()) {
        vector<int> comp;
        comp.push_back(rem.front());
        rem.erase(rem.begin());

        for (size_t head = 0; head < comp.size(); head++) {
            int u = comp[head];
            size_t keep = 0;
            for (size_t i = 0; i < rem.size(); i++) {
                int v = rem[i];
                if (abs(x[u] - x[v]) + abs(y[u] - y[v]) <= t) {
                    comp.push_back(v);
                } else {
                    rem[keep++] = v;
                }
            }
            rem.resize(keep);
        }

        sort(comp.begin(), comp.end());
        regions.push_back(comp);
    }

    cout << regions.size() << '\n';
    for (const auto& r : regions) {
        for (size_t i = 0; i < r.size(); i++) {
            if (i) cout << ' ';
            cout << r[i] + 1;
        }
        cout << '\n';
    }
    return 0;
}
