/*
Hungarian megoldás: a szókeresést DFS-sel végezzük a rácson, négy irányban
mozogva, minden mezőt legfeljebb egyszer használva.

Hint 1: || Ha a szó első betűje megvan, onnan folytatható a keresés. ||
Hint 2: || A találat útvonala a lépések irányából közvetlenül kiírható. ||
*/

#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> t;
string s;
vector<vector<char>> vis;
string path;
bool found = false;
int dr[4] = {-1, 0, 1, 0};
int dc[4] = {0, -1, 0, 1};
char ch[4] = {'F', 'B', 'L', 'J'};

bool dfs(int r, int c, int idx) {
    if (idx + 1 == (int)s.size()) return true;
    vis[r][c] = 1;
    for (int d = 0; d < 4; ++d) {
        int nr = r + dr[d], nc = c + dc[d];
        if (nr < 0 || nr >= n || nc < 0 || nc >= n || vis[nr][nc] || t[nr][nc] != s[idx + 1]) continue;
        path.push_back(ch[d]);
        if (dfs(nr, nc, idx + 1)) return true;
        path.pop_back();
    }
    vis[r][c] = 0;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    t.resize(n);
    for (int i = 0; i < n; ++i) cin >> t[i];
    cin >> s;
    vis.assign(n, vector<char>(n, 0));
    for (int i = 0; i < n && !found; ++i) for (int j = 0; j < n && !found; ++j) if (t[i][j] == s[0]) {
        path.clear();
        if (dfs(i, j, 0)) {
            cout << i + 1 << ' ' << j + 1 << '\n' << path << '\n';
            found = true;
        }
    }
    if (!found) cout << "0 0\n";
    return 0;
}