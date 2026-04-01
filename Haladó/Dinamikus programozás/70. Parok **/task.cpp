/*
A keresztezes nelkuli parok pontosan olyan parositast alkotnak, amelyben a 11.-es oldalon es a
12.-es oldalon is novekvo a kivalsztott sorszamok sorrendje. Ez ugyanaz a dinamika, mint az LCS-nel:
dp[i][j] legyen a maximum parszam az elso i bal oldali es elso j jobb oldali tanuloval. Ha i es j
baratok, akkor a ket uj diak parba allithato, igy dp[i][j] legalabb dp[i-1][j-1]+1. Emellett mindig
kihagyhato az egyik oldal aktualis diakja, tehat a ket szomszedos allapot maximumat is venni kell.
A szulo-informaciobol a konkret, novekvo sorrendu parlista visszaepitheto.
*/
/*
Hint 1: || A nem keresztezodo feltetel azt jelenti, hogy a kivalsztott parok mindket oldalon novekvo sorrendben jonnek. ||
Hint 2: || Ezert egy ketdimenzios DP ugyanugy mukodik, mint a leghosszabb kozos reszsorozatnal. ||
Hint 3: || Ha (i,j) valaszthato par, akkor erdemes megnezni a dp[i-1][j-1]+1 lehetoseget is. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> knows(n + 1, vector<char>(n + 1, false));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        knows[a][b] = true;
    }

    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
    vector<vector<char>> parent(n + 1, vector<char>(n + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = dp[i - 1][j];
            parent[i][j] = 1;
            if (dp[i][j - 1] > dp[i][j]) {
                dp[i][j] = dp[i][j - 1];
                parent[i][j] = 2;
            }
            if (knows[i][j] && dp[i - 1][j - 1] + 1 > dp[i][j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                parent[i][j] = 3;
            }
        }
    }

    vector<pair<int, int>> answer;
    int i = n;
    int j = n;
    while (i > 0 && j > 0) {
        if (parent[i][j] == 3) {
            answer.push_back({i, j});
            --i;
            --j;
        } else if (parent[i][j] == 2) {
            --j;
        } else {
            --i;
        }
    }
    reverse(answer.begin(), answer.end());

    cout << answer.size() << '\n';
    for (const auto& [left, right] : answer) {
        cout << left << ' ' << right << '\n';
    }
    return 0;
}