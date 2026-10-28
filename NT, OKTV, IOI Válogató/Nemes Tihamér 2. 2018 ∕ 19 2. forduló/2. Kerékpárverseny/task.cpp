/*
Megoldás lényege:
A lépések csak jobbra vagy lefelé mutatnak, ezért a rács körmentes (DAG), és a dinamikát a jobb alsó sarokból visszafelé számoljuk.
Minden kereszteződés dp értéke az onnan induló leghosszabb megengedett út hossza, és eltároljuk a hozzá vezető lépést is.
Egy lépés csak akkor megengedett, ha a két szomszédos kereszteződés magasságkülönbsége legfeljebb K.
A legnagyobb dp értékű kezdőmezőből a tárolt lépések alapján visszaépítjük az útvonalat.
Az időigény és a tárolási igény is O(N·M), ami a korlátok mellett bőven elfér.
*/
/*
Hint 1: || Mivel a lépések csak jobbra vagy lefelé mutatnak, a mezők legjobb útját a jobb alsó sarokból kiindulva, visszafelé érdemes kiszámolni. ||
Hint 2: || Legyen dp[i][j] az (i,j) mezőből induló leghosszabb út hossza. Ez a jobbra és a lefelé szomszéd dp értékénél 1-gyel nagyobb érték közül a nagyobbik, de csak ha a lépés megengedett; ha egyik sem az, az érték 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) cin >> a[i][j];
    }

    vector<vector<int>> dp(n + 2, vector<int>(m + 2, 0));
    vector<vector<char>> nxt(n + 2, vector<char>(m + 2, 0));

    int bestLen = 0, sr = 1, sc = 1;
    for (int i = n; i >= 1; --i) {
        for (int j = m; j >= 1; --j) {
            int best = 0;
            char step = 0;
            if (j < m && abs(a[i][j] - a[i][j + 1]) <= k) {
                int cand = 1 + dp[i][j + 1];
                if (cand > best) {
                    best = cand;
                    step = 'J';
                }
            }
            if (i < n && abs(a[i][j] - a[i + 1][j]) <= k) {
                int cand = 1 + dp[i + 1][j];
                if (cand > best) {
                    best = cand;
                    step = 'L';
                }
            }
            dp[i][j] = best;
            nxt[i][j] = step;
            if (best > bestLen) {
                bestLen = best;
                sr = i;
                sc = j;
            }
        }
    }

    string path;
    int r = sr, c = sc;
    while (nxt[r][c]) {
        char step = nxt[r][c];
        path.push_back(step);
        if (step == 'J') ++c;
        else ++r;
    }

    cout << bestLen << '\n' << sr << ' ' << sc << '\n' << path << '\n';
    return 0;
}