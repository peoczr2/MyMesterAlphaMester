/*
Megoldás lényege:
A szigetek a zöld cellák olyan összefüggő részei, amelyekben a cellák a sarkokat is beleértve szomszédosak lehetnek, mert a feladat szerint két különböző sziget sarkon sem érintkezik. Ezért minden zöld komponenst a 8 irányú szomszédságon át kell bejárni. Egy még nem látogatott zöld cellából indított szélességi bejárás (BFS) egy teljes szigetet bejár, a látogatott tömb miatt minden cella legfeljebb egyszer kerül a sorba. A szigetek száma az indítások száma, az összes munka O(N·M), ami legfeljebb 10^6 cella.
*/
/*
Hint 1: || A sziget a zöld cellák olyan összefüggő halmaza, ahol a cellák oldalról vagy sarokról elérhetők egymásból. Keresd meg ezeket a részeket. ||
Hint 2: || Minden még nem látott zöld cellából indíts szélességi bejárást, amely a 8 szomszédos irányba lép. Minden indítás egy új szigetet jelent, így a számlálót ott növeld. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto &row : grid) cin >> row;

    vector<vector<char>> seen(n, vector<char>(m, 0));
    int islands = 0;
    queue<pair<int, int>> q;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != 'Z' || seen[i][j]) continue;
            ++islands;
            seen[i][j] = 1;
            q.push({i, j});
            while (!q.empty()) {
                auto [x, y] = q.front();
                q.pop();
                for (int dx = -1; dx <= 1; ++dx) {
                    for (int dy = -1; dy <= 1; ++dy) {
                        int a = x + dx, b = y + dy;
                        if (a < 0 || a >= n || b < 0 || b >= m) continue;
                        if (grid[a][b] != 'Z' || seen[a][b]) continue;
                        seen[a][b] = 1;
                        q.push({a, b});
                    }
                }
            }
        }
    }
    cout << islands << "\n";
    return 0;
}
