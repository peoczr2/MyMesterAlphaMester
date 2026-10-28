/*
Megoldás lényege:
Egy útvonal sebessége a rajta lévő legkisebb átviteli sebesség, ezért két gép legjobb sebessége a legszélesebb út (maximin) értéke.
Ezt Floyd–Warshall-szerű táblázattal számoljuk: a köztes csúcsot végigpróbálva a best[i][j] értéket max(best[i][j], min(best[i][k], best[k][j])) szerint frissítjük.
Minden i jelöltre azt a legkisebb sebességet nézzük, amellyel bármely más gép elérhető; a legnagyobb ilyen értékű gépet választjuk, egyenlőség esetén a kisebb sorszámút.
Az időigény O(N³), ami N ≤ 100 esetén bőven elég.
*/
/*
Hint 1: || Egy útvonal sebessége a szakaszsebességek minimuma, ezért két gép legjobb sebessége a legszélesebb út feladat: a Floyd–Warshall-hoz hasonló táblázat mindent megad. ||
Hint 2: || Minden i géphez számold ki a többi géphez vezető legjobb sebességek minimumát. Az a jó központ, ahol ez a minimum a legnagyobb; ha több ilyen van, a legkisebb sorszámút válaszold. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    const int INF = 1e9 + 7;
    vector<vector<int>> best(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; ++i) best[i][i] = INF;
    for (int i = 0; i < k; ++i) {
        int a, b, s;
        cin >> a >> b >> s;
        best[a][b] = max(best[a][b], s);
    }

    for (int mid = 1; mid <= n; ++mid) {
        for (int i = 1; i <= n; ++i) {
            if (best[i][mid] == 0) continue;
            for (int j = 1; j <= n; ++j) {
                if (best[mid][j] == 0) continue;
                best[i][j] = max(best[i][j], min(best[i][mid], best[mid][j]));
            }
        }
    }

    int ans = 1;
    int score = -1;
    for (int i = 1; i <= n; ++i) {
        int cur = INF;
        for (int j = 1; j <= n; ++j) {
            if (i == j) continue;
            cur = min(cur, best[i][j]);
        }
        if (cur > score) {
            score = cur;
            ans = i;
        }
    }

    cout << ans << '\n';
    return 0;
}