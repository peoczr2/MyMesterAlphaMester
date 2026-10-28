/*
Megoldás lényege:
A futó mozgása szélességi bejárással számolható, mert minden lépés egységnyi költségű, a csúcsok pedig a tábla mezői. Egy mezőből minden átlós irányban addig lehet továbblépni, amíg a tábla szélét vagy az első bábut el nem érjük; az ezeken a mezőkön álló lépések egy lépéssel elérhetők. Az A részfeladatban a bábu mezőjére nem lehet lépni, a B részfeladatban viszont az első bábu leüthető: a lépés a bábu mezőjén ér véget, és az adott irányban nem megy tovább. Az időigény O(N^3) legfeljebb, ami N ≤ 200 esetén bőven elég.
*/
/*
Hint 1: || Egy lépés egy átló menti csúszás: az első bábuig vagy a tábla széléig minden mező egy lépésből elérhető. ||
Hint 2: || A két részfeladat ugyanazzal a bejárással oldható meg; B-nél csak az a változás, hogy az első bábu mezőjére is lehet lépni, de a csúszás ott véget ér. ||
Hint 3: || Ha a célmezőt a bejárás nem éri el, a kiírandó érték -1; a kezdő- és célmező egyezése esetén a válasz 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

static int N;

// Szélességi bejárás a futó mezői között.
// allowCapture = false: az átlón csak az első bábuig lehet menni, a bábu mezőjére nem lehet lépni.
// allowCapture = true: az első bábu leüthető, a lépés a bábu mezőjén ér véget.
static int bishopBfs(const vector<vector<char>>& occ, int sx, int sy, int tx, int ty, bool allowCapture) {
    if (sx == tx && sy == ty) return 0;

    vector<vector<int>> dist(N + 1, vector<int>(N + 1, -1));
    queue<pair<int, int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});

    const int dx[4] = {1, 1, -1, -1};
    const int dy[4] = {1, -1, 1, -1};
    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        for (int d = 0; d < 4; ++d) {
            int nx = x + dx[d], ny = y + dy[d];
            while (nx >= 1 && nx <= N && ny >= 1 && ny <= N) {
                if (occ[nx][ny]) {
                    if (allowCapture && dist[nx][ny] == -1) {
                        dist[nx][ny] = dist[x][y] + 1;
                        q.push({nx, ny});
                    }
                    break;
                }
                if (dist[nx][ny] == -1) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                }
                nx += dx[d];
                ny += dy[d];
            }
        }
    }
    return dist[tx][ty];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> N >> k;

    int kx, ky, vx, vy;
    cin >> kx >> ky >> vx >> vy;

    vector<vector<char>> occ(N + 1, vector<char>(N + 1, 0));
    for (int i = 0; i < k; ++i) {
        int x, y;
        cin >> x >> y;
        occ[x][y] = 1;
    }

    cout << bishopBfs(occ, kx, ky, vx, vy, false) << '\n';
    cout << bishopBfs(occ, kx, ky, vx, vy, true) << '\n';
    return 0;
}
