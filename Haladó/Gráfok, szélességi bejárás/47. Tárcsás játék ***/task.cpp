/*
Megoldás lényege:
Minden lépés után az összes tárcsa 90 fokot fordul, ezért egy mezőn lévő tárcsa állása a megtett lépések számától függ,
de csak a lépésszám 4-es maradékától, mert négy forgatás után minden tárcsa visszaér az eredeti állásába. Ezért a
szélességi bejárás állapota nem csak a mező, hanem a lépésszám mod 4 is. Egy állapotban a mező tárcsáját a
lépésszám mod 4 szerint forgatva kapjuk az aktuális nyilakat, és minden nyíl irányába léphetünk. Mivel a bejárás
távolság szerint halad, az első olyan állapot, amely a jobb alsó sarokba ér, adja a minimális lépésszámot. Ha nem
érhető el, a -1 választ írjuk ki. Az időigény O(M * N * 4), ami 100 x 100-as táblán bőven belefér.
*/
/*
Hint 1: || Minden lépés után az összes tárcsa elfordul, így a mezőn lévő tárcsa állása a megtett lépések számától függ. A bejárásban tehát a mező mellé a lépésszám mod 4 is állapotnak számít, mert négy forgatás után minden tárcsa visszaér az eredeti állásába. ||
Hint 2: || A tárcsa négy bitje a négy irányt jelöli. Egy forgatás minden irányt a következőbe visz: fel -> jobbra -> le -> balra -> fel. Az (sor, oszlop, lépésszám mod 4) állapotokon szélességi bejárást futtatva a jobb alsó sarokba érkezés lépésszáma lesz a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Iránok sorrendje: 0 = fel, 1 = jobbra, 2 = le, 3 = balra (a tárcsa bitjei ebben a sorrendben)
// Egy 90 fokos forgatás órajárás szerint: fel -> jobbra -> le -> balra -> fel, vagyis a bitek egyet balra lépnek.
int rotateOnce(int mask) {
    return ((mask << 1) | (mask >> 3)) & 15;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<vector<int>> disc(m, vector<int>(n));
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++) cin >> disc[i][j];

    const int di[4] = {-1, 0, 1, 0};
    const int dj[4] = {0, 1, 0, -1};

    // Állapot: (sor, oszlop, lépésszám mod 4)
    auto id = [&](int i, int j, int t) { return (i * n + j) * 4 + t; };
    vector<int> dist(m * n * 4, -1);
    queue<int> q;
    dist[id(0, 0, 0)] = 0;
    q.push(id(0, 0, 0));

    int answer = -1;
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int t = cur % 4;
        int cell = cur / 4;
        int i = cell / n, j = cell % n;
        if (i == m - 1 && j == n - 1) {
            answer = dist[cur];
            break;
        }
        // A tárcsa állása t forgatás után
        int mask = disc[i][j];
        for (int k = 0; k < t; k++) mask = rotateOnce(mask);
        for (int d = 0; d < 4; d++) {
            if (!((mask >> d) & 1)) continue;
            int ni = i + di[d], nj = j + dj[d];
            if (ni < 0 || nj < 0 || ni >= m || nj >= n) continue;
            int nxt = id(ni, nj, (t + 1) % 4);
            if (dist[nxt] == -1) {
                dist[nxt] = dist[cur] + 1;
                q.push(nxt);
            }
        }
    }
    cout << answer << '\n';
    return 0;
}
