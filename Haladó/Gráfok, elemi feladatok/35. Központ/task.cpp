/*
Megoldás lényege:
Egy útvonal sebessége a rajta lévő legkisebb élsebesség, két csúcs közötti legjobb sebesség pedig a lehetséges utak sebességeinek maximuma.
Ezt a legszélesebb utak feladatot Floyd-Warshall-szerűen oldjuk meg: a min(w[i][m], w[m][j]) értéket vesszük, és a maximumot tartjuk meg.
Minden v csúcsra megnézzük, hogy a többi csúcs közül melyik érhető el a leglassabban (a legkisebb w[v][u]), és azt a csúcsot választjuk, amelynek ez az érték a legnagyobb; egyenlőségnél a kisebb sorszámút.
Az időigény O(N^3), ami N <= 100 mellett bőven belefér.
*/
/*
Hint 1: || Egy útvonal sebessége a legkisebb él sebessége rajta, így két csúcs közötti legjobb sebességet úgy kapod, hogy a lehetséges utak sebességei közül a legnagyobbat választod. Ezt Floyd-Warshall-szerűen minden csúcspárra kiszámolhatod. ||
Hint 2: || Egy v csúcs "gyorsasága" a többi csúcsnak számított legjobb sebességek minimuma, vagyis a leglassabban elérhető csúcs sebessége. A központ az a v, ahol ez az érték a legnagyobb; egyenlőség esetén a kisebb sorszám nyer. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    const int INF = INT_MAX;
    vector<vector<int>> w(n + 1, vector<int>(n + 1, 0));
    for (int i = 0; i < k; ++i) {
        int a, b, s;
        cin >> a >> b >> s;
        w[a][b] = max(w[a][b], s);
    }
    for (int i = 1; i <= n; ++i) w[i][i] = INF;

    for (int m = 1; m <= n; ++m)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                w[i][j] = max(w[i][j], min(w[i][m], w[m][j]));

    int bestV = 1, bestSpeed = -1;
    for (int v = 1; v <= n; ++v) {
        int slowest = INF;
        for (int u = 1; u <= n; ++u)
            if (u != v) slowest = min(slowest, w[v][u]);
        if (slowest > bestSpeed) {
            bestSpeed = slowest;
            bestV = v;
        }
    }
    cout << bestV << '\n';
    return 0;
}
