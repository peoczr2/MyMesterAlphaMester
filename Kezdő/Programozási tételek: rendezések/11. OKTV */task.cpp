/*
Megoldás lényege:
A fordulók addig futnak, amíg van holtverseny, és a holtversenyt mindig az újabb forduló pontszámai bontják. Ez pontosan úgy működik, mint egy többkulcsos rendezés: az első forduló pontszáma a fő szempont, a második fordulóé dönt az első holtversenyben, és így tovább. Ezért nem kell a fordulókat külön-külön szimulálni: a versenyzőket egyszer rendezzük a fordulók sorrendjében csökkenő pontszámok szerint. Mivel az utolsó forduló után nincs holtverseny, a rendezés egyértelmű helyezést ad. A rendezés O(N·log N·M), ami a korlátok mellett gyors.
*/
/*
Hint 1: || Nem kell a fordulókat külön szimulálni: a holtverseny feloldása pontosan azt jelenti, hogy a versenyzőket először az első forduló pontszáma, azonos pontszámnál a második, és így tovább szerint rendezzük. ||
Hint 2: || Egyetlen rendezést használj egyedi összehasonlító függvénnyel: a két versenyzőt a fordulók sorrendjében hasonlítsd össze, és az első eltérő pontszám döntsön, a nagyobb kerüljön előre. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    // p[j][i]: az i. versenyző pontszáma a j. fordulóban
    vector<vector<int>> p(m, vector<int>(n));
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++) cin >> p[j][i];

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int a, int b) {
        for (int j = 0; j < m; j++)
            if (p[j][a] != p[j][b]) return p[j][a] > p[j][b];
        return a < b;
    });

    for (int i = 0; i < n; i++) cout << order[i] + 1 << (i + 1 < n ? ' ' : '\n');
    return 0;
}
