/*
    A keresett szó legfeljebb 12 hosszú, a mátrix pedig 10x10-es lehet, ezért
    mélységi kereséssel végigpróbálhatjuk az összes kezdőhelyet és lépésirányt.
    Az aktuális utat a látogatott cellák jelölésével védjük, és zsákutcánál
    visszalépünk. Egy kezdőcellából legfeljebb 4·3^10 útvonalat járunk be,
    ez az összes kezdőcellára is belefér az időkorlátba.
*/
/*
Hint 1: || Próbálj minden cellát kezdőpontnak: ha az első betű egyezik, a szó következő betűjét kell keresni a szomszédos cellákban (fel, balra, le vagy jobbra), és közben nem léphetsz olyan cellára, amelyet az aktuális úton már használtál. ||

Hint 2: || A bejárt cellákat jelöld egy logikai tömbben, és a rekurzióból való visszatéréskor oldd fel a jelölést; a megtett lépések irányát egy karakterláncban (F, B, L, J) tárold, és visszalépéskor csökkentsd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int n;
vector<string> m;
string s;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, -1, 0, 1};
char ch[4] = {'F', 'B', 'L', 'J'};
bool vis[10][10];
string ut;

bool dfs(int x, int y, int idx) {
    if (idx == (int)s.size()) return true;
    vis[x][y] = true;
    for (int dir = 0; dir < 4; ++dir) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if (nx < 0 || nx >= n || ny < 0 || ny >= n) continue;
        if (vis[nx][ny] || m[nx][ny] != s[idx]) continue;
        ut.push_back(ch[dir]);
        if (dfs(nx, ny, idx + 1)) return true;
        ut.pop_back();
    }
    vis[x][y] = false;
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    m.resize(n);
    for (int i = 0; i < n; ++i) cin >> m[i];
    cin >> s;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (m[i][j] != s[0]) continue;
            memset(vis, 0, sizeof(vis));
            ut.clear();
            if (dfs(i, j, 1)) {
                cout << i + 1 << ' ' << j + 1 << '\n' << ut << '\n';
                return 0;
            }
        }
    }

    cout << "0 0\n";
    return 0;
}