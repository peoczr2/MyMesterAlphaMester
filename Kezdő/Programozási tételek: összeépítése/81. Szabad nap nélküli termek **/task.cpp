/*
Megoldás lényege:
Termenként gyűjtjük a foglalásokat, és kezdő nap szerint rendezzük őket. Két foglalás között akkor nincs szabad nap, ha a következő foglalás első napja pontosan eggyel az előző foglalás utolsó napja után van. Mivel a foglalások nem fedik egymást, elég a rendezett sorban a szomszédos párokat ellenőrizni: ha két foglalás között nincs szabad nap, a köztük lévő napokat lefedő foglalások között is van egymás utáni pár. Ha egy teremben van ilyen pár, a terem sorszámát felvesszük a listába. Az időigény O(K log K), a rendezés miatt, ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Termenként külön vizsgáld a foglalásokat: rendezd őket a kezdő nap szerint. Két egymás utáni foglalás között akkor nincs szabad nap, ha a következő foglalás első napja pontosan eggyel nagyobb az előző foglalás utolsó napjánál. ||
Hint 2: || Minden terem foglalásait gyűjtsd külön vektorba, és a végén a teremszámokat növekvő sorrendben írd ki. Ha egyik teremben sincs ilyen szomszédos pár, a második sor üres marad, de a kimenetnek akkor is két sorból kell állnia. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m, k;
    cin >> n >> m >> k;

    vector<vector<pair<int, int>>> foglalas(n + 1);
    for (int i = 0; i < k; ++i) {
        int t, e, u;
        cin >> t >> e >> u;
        foglalas[t].push_back({e, u});
    }

    vector<int> talalt;
    for (int t = 1; t <= n; ++t) {
        sort(foglalas[t].begin(), foglalas[t].end());
        bool van = false;
        for (size_t i = 1; i < foglalas[t].size(); ++i) {
            if (foglalas[t][i].first == foglalas[t][i - 1].second + 1) {
                van = true;
                break;
            }
        }
        if (van) talalt.push_back(t);
    }

    cout << talalt.size() << '\n';
    for (size_t i = 0; i < talalt.size(); ++i) {
        if (i) cout << ' ';
        cout << talalt[i];
    }
    cout << '\n';
    return 0;
}
