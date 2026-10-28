/*
Megoldás lényege:
Minden versenyző dobásait csökkenő sorrendbe rendezzük, így a "legnagyobb dobás, majd a második legnagyobb, ..." szempont közvetlenül a sorozatok összehasonlításává válik.
Két versenyző sorrendjét a rendezett dobássorozataik lexikografikus összehasonlításával döntjük el: az a jobb, akinek az első különböző helyen nagyobb dobása van.
A versenyzők sorszámait ezzel a feltétellel rendezzük, a stabil rendezés pedig az egyenlő sorozatoknál megtartja a listabeli sorrendet.
A rendezések együttes időigénye O(N log N · K), ami a korlátok mellett bőven belefér.
*/
/*
Hint 1: || Két versenyző összehasonlításánál nem a dobások eredeti sorrendje számít, hanem a legnagyobb dobásaik: rendezd minden versenyző dobásait csökkenő sorrendbe. ||
Hint 2: || A sorrendet úgy kapod meg, mint szótárban a szavak sorrendjét: a rendezett dobássorozatokat elemenként hasonlítsd össze, és az első különböző helyen nagyobb dobású kerüljön előrébb. Egyenlő sorozatoknál a sorszám szerinti sorrend maradjon. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k;
    cin >> n >> k;
    vector<vector<int>> d(n, vector<int>(k));
    for (auto &row : d) {
        for (int &x : row) cin >> x;
        sort(row.begin(), row.end(), greater<int>());
    }

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    // a vector lexikografikus összehasonlítása; stabil rendezés: egyenlőnél marad a listabeli sorrend
    stable_sort(order.begin(), order.end(), [&](int x, int y) {
        return d[x] > d[y];
    });

    for (int i = 0; i < n; i++) {
        if (i) cout << ' ';
        cout << order[i] + 1;
    }
    cout << '\n';
    return 0;
}
