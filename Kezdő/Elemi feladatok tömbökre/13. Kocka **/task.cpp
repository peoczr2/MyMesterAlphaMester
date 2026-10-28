/*
Megoldás lényege:
A kocka 12 élét egy 9×9-es logikai táblázatban (adjacencia-mátrix) rögzítjük az 1–8 csúcsokra indexelve,
mindkét irányban. A bejárási sorrend minden egymást követő párjára megnézzük, van-e köztük él. Ha nincs,
a párt a bemeneti sorrendben kiírjuk, ha minden pár él, az „IGEN” szót írjuk ki. A sorrend 8 elemű,
így az időigény állandó.
*/
/*
Hint 1: || Az élek a számozásból adódnak: az alsó lapon a szomszédos számok (1-2, 2-3, 3-4, 4-1), a felső lapon a szomszédos számok (5-6, 6-7, 7-8, 8-5), a függőleges élek pedig az 1-8, 2-7, 3-6, 4-5 párok. ||
Hint 2: || Tárold az éleket egy logikai táblázatban, a bejárás minden egymást követő párjára pedig nézd meg a táblázat megfelelő elemét. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    // adj[a][b] igaz, ha az a és b csúcs között van él
    bool adj[9][9] = {};
    int edges[12][2] = {
        {1, 2}, {2, 3}, {3, 4}, {4, 1},
        {5, 6}, {6, 7}, {7, 8}, {8, 5},
        {1, 8}, {2, 7}, {3, 6}, {4, 5}
    };
    for (auto &e : edges) {
        adj[e[0]][e[1]] = adj[e[1]][e[0]] = true;
    }

    int p[8];
    for (int i = 0; i < 8; i++) cin >> p[i];

    vector<pair<int, int>> bad;
    for (int i = 0; i + 1 < 8; i++) {
        if (!adj[p[i]][p[i + 1]]) bad.push_back({p[i], p[i + 1]});
    }

    if (bad.empty()) {
        cout << "IGEN\n";
    } else {
        for (size_t i = 0; i < bad.size(); i++) {
            if (i) cout << ' ';
            cout << bad[i].first << '-' << bad[i].second;
        }
        cout << '\n';
    }
    return 0;
}
