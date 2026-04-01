/*
Itt nem egyetlen útvonalat, hanem minden mező minimális huszárlépésszámát kell meghatározni. Ez természetesen egy forrásból indított BFS-es távolságszámítás, ahol minden elért mezőre eltároljuk a legkisebb lépésszámot.
*/
/*
Hint 1: || Itt nem az útvonal kell, hanem csak az, hogy hány huszárlépés után érhető el egy mező. ||
Hint 2: || A válasz minden mezőre egyetlen hullámban terjedő BFS-ből kiolvasható. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y;
    cin >> x >> y;
    --x; --y;
    vector<vector<int>> dist(8, vector<int>(8, -1));
    queue<pair<int,int>> q;
    dist[x][y] = 0;
    q.push({x, y});
    const int dx[8] = {-2,-2,-1,-1,1,1,2,2};
    const int dy[8] = {-1,1,-2,2,-2,2,-1,1};
    while (!q.empty()) {
        auto [i, j] = q.front(); q.pop();
        for (int k = 0; k < 8; ++k) {
            int ni = i + dx[k], nj = j + dy[k];
            if (0 <= ni && ni < 8 && 0 <= nj && nj < 8 && dist[ni][nj] == -1) {
                dist[ni][nj] = dist[i][j] + 1;
                q.push({ni, nj});
            }
        }
    }
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (j) cout << ' ';
            cout << dist[i][j];
        }
        cout << '\n';
    }
    return 0;
}