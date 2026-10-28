/*
Megoldás lényege:
Egy mező 100 m x 100 m, azaz 1 hektár, ezért a gazdaság területe hektárban a mezők száma, a legelők aránya pedig az L mezők száma osztva az összes mezővel. A legelők téglalapok, és nem érintkeznek egymással, ezért az oldalszomszédos L mezők összefüggő komponensei pontosan a legelők: ezeket BFS bejárással azonosítjuk, és komponensenként megjegyezzük a területet és a legkisebb-legnagyobb oszlopindexet. A legelő szélessége a két oszlopindex különbségéből (plusz egy) adódik, méterben pedig szorozva 100-zal. Az északi legelő távolsága a legkisebb sorindexű L mező sorindexéből (0-tól számolva) adódik, szintén 100 méterrel szorozva. Az időigény a mezők számával arányos, vagyis legfeljebb 10000 lépés.
*/
/*
Hint 1: || Egy mező 1 hektár, így a területek egyszerűen mezőszámok. A legelők téglalapok, és nem érintkeznek, ezért az oldalszomszédos L mezők egy BFS vagy DFS bejárásával minden legelő külön komponensként adódik. ||
Hint 2: || Komponensenként számold a területet, és jegyezd fel a legkisebb és legnagyobb oszlopindexet; a szélesség (legnagyobb - legkisebb + 1) * 100 méter. Az északi távolság a legkisebb sorindexű L mező sorindexéből adódik (0-tól számolva): index * 100 méter. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (auto &s : g) cin >> s;

    // 1. részfeladat: a gazdaság területe hektárban
    long long total = (long long)n * m;

    // 2. és 3. részfeladathoz: legelők mezőszáma, legkisebb sorindex
    long long pasture = 0;
    int minRow = -1;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (g[i][j] == 'L') {
                pasture++;
                if (minRow < 0) minRow = i;
            }

    // Legelők (összefüggő komponensek) bejárása
    vector<vector<bool>> vis(n, vector<bool>(m, false));
    int dr[4] = {1, -1, 0, 0}, dc[4] = {0, 0, 1, -1};
    long long count = 0, maxWidth = 0, maxArea = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
            if (g[i][j] != 'L' || vis[i][j]) continue;
            count++;
            queue<pair<int, int>> q;
            q.push({i, j});
            vis[i][j] = true;
            int minC = j, maxC = j;
            long long area = 0;
            while (!q.empty()) {
                auto [r, c] = q.front();
                q.pop();
                area++;
                minC = min(minC, c);
                maxC = max(maxC, c);
                for (int d = 0; d < 4; d++) {
                    int nr = r + dr[d], nc = c + dc[d];
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m) continue;
                    if (g[nr][nc] != 'L' || vis[nr][nc]) continue;
                    vis[nr][nc] = true;
                    q.push({nr, nc});
                }
            }
            maxWidth = max(maxWidth, (long long)(maxC - minC + 1));
            maxArea = max(maxArea, area);
        }

    cout << "#\n" << total << '\n';
    cout << "#\n" << fixed << setprecision(2) << 100.0 * pasture / total << '\n';
    cout << "#\n" << (long long)minRow * 100 << '\n';
    cout << "#\n" << maxWidth * 100 << '\n';
    cout << "#\n" << count << '\n';
    cout << "#\n" << maxArea << '\n';
    return 0;
}
