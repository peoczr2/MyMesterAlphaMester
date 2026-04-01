/*
Megoldási ötlet:
A robot minden lépésben szigorúan növeli a kezdőponttól mért Manhattan-távolságát, ezért az út a távolsággyűrűk szerint réteges DAG-ot
alkot. Egy mezőbe csak a négy szomszédja közül azokról érkezhetünk, amelyek egy gyűrűvel beljebb vannak.

Legyen dp[i][j] a (i,j) mezőig vezető út minimális sáros mezőszáma. A gyűrűket növekvő távolság szerint dolgozzuk fel, minden mezőhöz a
legjobb elődöt és az oda vezető irányt is eltároljuk. A végén a szélmezők közül választjuk a legjobbat, majd hozzáírjuk az utolsó, a
szigetről kilépő lépést.
*/
/*
Hint 1: || A Manhattan-távolság mindig pontosan eggyel nő egy szabályos lépésben. ||
Hint 2: || Emiatt a mezők rétegesen feldolgozhatók a középponttól kifelé. ||
Hint 3: || A válasz nem egy szélmezőn, hanem egy onnan kifelé tett utolsó lépéssel ér véget. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const int INF = 1e9;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> a(n + 1, vector<int>(n + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) cin >> a[i][j];
    }

    int sr = n / 2 + 1;
    int sc = n / 2 + 1;
    int maxDist = 0;
    vector<vector<pair<int, int>>> rings(2 * n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            int d = abs(i - sr) + abs(j - sc);
            maxDist = max(maxDist, d);
            rings[d].push_back({i, j});
        }
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, INF));
    vector<vector<char>> parent(n + 1, vector<char>(n + 1, 0));
    dp[sr][sc] = a[sr][sc];

    const int dx[4] = {-1, 1, 0, 0};
    const int dy[4] = {0, 0, -1, 1};
    const char moveChar[4] = {'D', 'N', 'E', 'K'};

    for (int d = 1; d <= maxDist; ++d) {
        for (auto [x, y] : rings[d]) {
            for (int dir = 0; dir < 4; ++dir) {
                int px = x + dx[dir];
                int py = y + dy[dir];
                if (px < 1 || px > n || py < 1 || py > n) continue;
                if (abs(px - sr) + abs(py - sc) != d - 1) continue;
                if (dp[px][py] + a[x][y] < dp[x][y]) {
                    dp[x][y] = dp[px][py] + a[x][y];
                    parent[x][y] = moveChar[dir];
                }
            }
        }
    }

    int best = INF;
    pair<int, int> finish = {sr, sc};
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i != 1 && i != n && j != 1 && j != n) continue;
            if (dp[i][j] < best) {
                best = dp[i][j];
                finish = {i, j};
            }
        }
    }

    string path;
    int x = finish.first, y = finish.second;
    while (!(x == sr && y == sc)) {
        char c = parent[x][y];
        path.push_back(c);
        if (c == 'D') --x;
        else if (c == 'N') ++x;
        else if (c == 'E') --y;
        else ++y;
    }
    reverse(path.begin(), path.end());

    char exitMove;
    if (finish.first == 1) exitMove = 'N';
    else if (finish.first == n) exitMove = 'D';
    else if (finish.second == 1) exitMove = 'K';
    else exitMove = 'E';
    path.push_back(exitMove);

    cout << best << '\n';
    cout << path << '\n';
    return 0;
}