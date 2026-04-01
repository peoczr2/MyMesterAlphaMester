/*
A legkevesebb lépésű eljutás keresés, ezért a sakklépések gráfján szélességi bejárást kell futtatni. A BFS szintjei közvetlenül megadják, hány ugrás kell az induló mezőtől a célig.
*/
/*
Hint 1: || A lépések számát a sakkló nyolc lehetséges ugrása alapján, BFS-sel érdemes keresni. ||
Hint 2: || A legkisebb távolságot szintenként terjedő bejárással kapod meg. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int x, y, n;
    cin >> x >> y >> n;
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
            cout << (dist[i][j] != -1 && dist[i][j] <= n ? '*' : '.');
        }
        cout << '\n';
    }
    return 0;
}