/*
Megoldás lényege:
A hatszögeket (i,j,k) indexekkel azonosítjuk, ahol i+j+k=0, így elég az (i,j) párt tárolni, a k mindig -i-j. A bemenet 2N-1 sora felülről lefelé az i = -(N-1) ... (N-1) értékeknek felel meg, és egy sorban j balról jobbra nő; a sor hossza 2N-1-|i|. A (p,q,r) pontból szélességi bejárást végzünk, de csak olyan szomszédra lépünk, amely a térképen belül van, és magassága megegyezik a kiindulási pontéval. Ha az (x,y,z) pont elérhető, a bejárás távolsága a válasz, különben -1. Legfeljebb (2N-1)^2 mező van, így az időigény O(N^2), ami N ≤ 80 esetén bőven elég.
*/
/*
Hint 1: || Elég két indexet tárolni, mert a harmadik mindig a két másik összegének ellentettje: k = -i-j. Így a térkép egy (i,j) koordinátájú négyzetes tömbbel ábrázolható. ||
Hint 2: || Az i-edik sorban j a sor elejétől a végéig egyesével nő; a sor elején j = max(-(N-1), -i-(N-1)), a végén j = min(N-1, N-1-i). Ezekkel a határokkal olvasd be a magasságokat. ||
Hint 3: || Szélességi bejárásnál a hat szomszéd (i-1,j), (i-1,j+1), (i,j-1), (i,j+1), (i+1,j-1), (i+1,j). Csak olyan szomszédra lépj, amely a térképen belül van, és ugyanolyan magas, mint a kiindulási pont. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int size = 2 * n - 1;
    int off = n - 1;  // az (i,j) indexek eltolása nemnegatív tömbindexekre

    vector<vector<int>> height(size, vector<int>(size, 0));
    vector<vector<char>> inside(size, vector<char>(size, 0));

    // Sorok: i = -(N-1) ... (N-1), felülről lefelé; egy sorban j balról jobbra nő.
    for (int row = 0; row < size; row++) {
        int i = row - off;
        int jFirst = max(-off, -i - off);
        int jLast = min(off, off - i);
        for (int j = jFirst; j <= jLast; j++) {
            cin >> height[i + off][j + off];
            inside[i + off][j + off] = 1;
        }
    }

    int p, q, r, x, y, z;
    cin >> p >> q >> r >> x >> y >> z;

    // Szomszédok (i,j) szerinti eltolása; a harmadik index k = -i-j mindig adódik.
    const int di[6] = {-1, -1, 0, 0, 1, 1};
    const int dj[6] = {0, 1, -1, 1, -1, 0};

    int si = p + off, sj = q + off;
    int ti = x + off, tj = y + off;
    int startHeight = height[si][sj];

    vector<vector<int>> dist(size, vector<int>(size, -1));
    queue<pair<int, int>> que;
    dist[si][sj] = 0;
    que.push({si, sj});
    while (!que.empty()) {
        auto [ci, cj] = que.front();
        que.pop();
        for (int d = 0; d < 6; d++) {
            int ni = ci + di[d], nj = cj + dj[d];
            if (ni < 0 || nj < 0 || ni >= size || nj >= size) continue;
            if (!inside[ni][nj] || dist[ni][nj] != -1) continue;
            if (height[ni][nj] != startHeight) continue;
            dist[ni][nj] = dist[ci][cj] + 1;
            que.push({ni, nj});
        }
    }

    cout << dist[ti][tj] << "\n";
    return 0;
}
