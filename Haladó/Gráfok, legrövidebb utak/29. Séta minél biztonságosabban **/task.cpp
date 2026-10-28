/*
Megoldás lényege:
Minden lámpa körül egy H×H-s négyzet világos, a többi mező sötét. A világos mezőket egyesével bejelöljük, ez legfeljebb K·H^2 <= 10^7 lépés. Az úton a sötét mezőbe lépés 1, a világos mezőbe 0 költséggel jár, így a feladat a bal felső sarokból a jobb alsó sarokba vezető legolcsóbb út keresése 0-1 súlyokkal. Erre a 0-1 BFS a megfelelő módszer: a 0 súlyú szomszédot a sor elejére, az 1 súlyút a végére tesszük. Az időigény O(N·M). A kezdő mező költsége is beleszámít, mert a kezdő mezőn is áthaladunk, és a végső mező költsége is része az útnak.
*/
/*
Hint 1: || Melyik mezők világosak? Egy lámpa körül a (H-1)/2 távolságon belüli négyzet világos, a többi mező sötét. Ezt egy logikai tömbben egyszerűen be lehet jelölni. ||
Hint 2: || A költség a bejárt sötét mezők száma, vagyis a mezőbe lépés költsége 0 vagy 1. Így a sima BFS helyett 0-1 BFS-t (kétvégű sort) érdemes használni: a 0 súlyú szomszédot a sor elejére, az 1 súlyút a végére tedd. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k, h;
    cin >> n >> m >> k >> h;

    vector<vector<char>> lit(n + 1, vector<char>(m + 1, 0));
    int r = (h - 1) / 2;
    for (int i = 0; i < k; i++) {
        int x, y;
        cin >> x >> y;
        for (int a = max(1, x - r); a <= min(n, x + r); a++)
            for (int b = max(1, y - r); b <= min(m, y + r); b++)
                lit[a][b] = 1;
    }

    const int INF = 1000000000;
    vector<vector<int>> dist(n + 1, vector<int>(m + 1, INF));
    deque<pair<int, int>> dq;
    dist[1][1] = lit[1][1] ? 0 : 1;
    dq.push_back({1, 1});

    const int dx[4] = {1, -1, 0, 0};
    const int dy[4] = {0, 0, 1, -1};
    while (!dq.empty()) {
        auto [x, y] = dq.front();
        dq.pop_front();
        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d], ny = y + dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            int w = lit[nx][ny] ? 0 : 1;
            if (dist[x][y] + w < dist[nx][ny]) {
                dist[nx][ny] = dist[x][y] + w;
                if (w == 0) dq.push_front({nx, ny});
                else dq.push_back({nx, ny});
            }
        }
    }

    cout << dist[n][m] << '\n';
    return 0;
}
