/*
Megoldás lényege:
Először ellenőrizzük a bemenetet: minden kocka alatti szám 0 és N között legyen, egy kocka nem állhat saját magán, egy kocka tetején legfeljebb egy kocka lehet, és nincs körforgás (az asztalról kiinduló láncok lefedik az összes kockát).
Ezután az 1., 2., …, N. kockát sorban a helyére építjük: ha az i. kocka már az (i-1). kocka tetején van, nem csinálunk semmit.
Egyébként az (i-1). kocka tetején és az i. kocka tetején lévő kockákat felülről lefelé az asztalra tesszük, majd az i. kockát az (i-1). kocka tetejére (az 1. kockát az asztalra) rakjuk.
Ez a sorrend minimális lépésszámot ad: egy kocka pontosan akkor mozog kétszer, ha közvetlenül egy nála kisebb sorszámú kocka tetején volt, egyébként egyszer; a bejárás O(N).
*/
/*
Hint 1: || A tornyot alulról felfelé építsd: az 1. kocka kerüljön az asztalra, majd minden következő kocka az őt megelőző kocka tetejére; a kérdés csak az, mit kell előbb levenni. ||
Hint 2: || Ha egy kocka tetején másik kocka van, azt előbb le kell venni, és a lekerült kockát később a helyére kell tenni, így a lekerülő kocka két lépést kap. ||
Hint 3: || Egy kocka tetején lévő kockák láncát tömb segítségével követheted (a tető-mutató minden kockához ismert), és a láncot felülről lefelé érdemes lebontani. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> below(n + 1, 0), above(n + 1, 0);
    bool ok = true;
    for (int i = 1; i <= n; i++) {
        cin >> below[i];
        if (below[i] < 0 || below[i] > n || below[i] == i) ok = false;
    }
    if (ok) {
        for (int i = 1; i <= n && ok; i++) {
            if (below[i] == 0) continue;
            if (above[below[i]] != 0) ok = false;
            above[below[i]] = i;
        }
    }
    if (ok) {
        int reached = 0;
        for (int i = 1; i <= n; i++) {
            if (below[i] != 0) continue;
            for (int x = i; x != 0; x = above[x]) reached++;
        }
        if (reached != n) ok = false;
    }
    if (!ok) {
        cout << "HIBAS\n";
        return 0;
    }

    vector<pair<int, int>> moves;
    auto moveCube = [&](int x, int y) {
        if (below[x]) above[below[x]] = 0;
        below[x] = y;
        if (y) above[y] = x;
        moves.push_back({x, y});
    };
    auto clearAbove = [&](int x) {
        vector<int> chain;
        for (int y = above[x]; y != 0; y = above[y]) chain.push_back(y);
        for (int k = (int)chain.size() - 1; k >= 0; k--) moveCube(chain[k], 0);
    };

    for (int i = 1; i <= n; i++) {
        if (below[i] == i - 1) continue;
        if (i - 1 >= 1) clearAbove(i - 1);
        clearAbove(i);
        moveCube(i, i - 1);
    }

    string out = "HELYES\n";
    for (auto& mv : moves) {
        out += to_string(mv.first) + " " + to_string(mv.second) + "\n";
    }
    cout << out;
    return 0;
}
