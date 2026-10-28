/*
Gyöngy csapdával, jobbra és lefelé lépve
Feladat: a bal felső sarokból a jobb alsóba kell eljutni csak jobbra és lefelé lépve, csapdára (-1)
nem léphetünk. Ki kell írni a maximális gyöngyszámot és egy ilyen lépéssort (J/L).
Ötlet: klasszikus rács-DP. dp[i][j] = a legtöbb gyöngy, amivel (i,j)-be eljuthatunk; egy mezőbe csak
felülről vagy balról érkezhetünk, így dp[i][j] = a[i][j] + max(dp[i-1][j], dp[i][j-1]). A csapda és a
nem elérhető mező értéke -∞. Minden mezőre eltároljuk, honnan jöttünk (L vagy J), ebből a célból
visszafelé haladva felírható az út.
A kimenet a mintafájlok szerint két sor (pontszám, lépéssor); a feladatszöveg „két mező koordinátái”
sora a 26. feladatból maradt benne tévesen. A cél nem feltétlenül érhető el (a csapdák elzárhatják):
ilyenkor -1-et írunk ki, mint a testvérfeladatban (88. Táblás játék csapdákkal és gyöngyökkel).
Idő: O(N·M), memória: O(N·M).
*/
/*
Hint 1: || Egy mezőbe legfeljebb két irányból lehet beérkezni: felülről vagy balról. ||
Hint 2: || dp[i][j] = a legtöbb gyöngy, amivel (i,j)-be eljuthatsz: a[i][j] + max(dp[i−1][j], dp[i][j−1]). A csapdát és az elérhetetlen mezőt jelöld −∞-nel. ||
Hint 3: || Tárold minden mezőre, felülről (L) vagy balról (J) jöttél-e, és a célból visszafelé lépkedve írd fel az utat, majd fordítsd meg. Ha a cél értéke −∞, a válasz -1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // beolvasás: n sor, m oszlop, -1 = csapda
    int n, m;
    cin >> n >> m;
    vector<vector<int>> a(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) cin >> a[i][j];

    // dp[i][j]: a legtöbb gyöngy (i,j)-ig; NINCS = -∞ (csapda vagy elérhetetlen).
    // A 0. sor és oszlop őrszem (NINCS), így a széleket nem kell külön kezelni.
    const long long NINCS = LLONG_MIN / 4;
    vector<vector<long long>> dp(n + 1, vector<long long>(m + 1, NINCS));
    vector<vector<char>> honnan(n + 1, vector<char>(m + 1, '?'));
    dp[1][1] = a[1][1];

    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= m; j++) {
            if ((i == 1 && j == 1) || a[i][j] == -1) continue;
            // egyenlőségnél a felülről érkezést (L) tartjuk meg
            if (dp[i - 1][j] != NINCS && dp[i - 1][j] >= dp[i][j - 1]) {
                dp[i][j] = dp[i - 1][j] + a[i][j];
                honnan[i][j] = 'L';
            } else if (dp[i][j - 1] != NINCS) {
                dp[i][j] = dp[i][j - 1] + a[i][j];
                honnan[i][j] = 'J';
            }
        }

    // a cél nem érhető el: -1
    if (dp[n][m] == NINCS) {
        cout << -1 << '\n';
        return 0;
    }

    // visszafejtés a célból a kezdőmezőig, majd megfordítás
    string ut;
    int i = n, j = m;
    while (i != 1 || j != 1) {
        ut += honnan[i][j];
        if (honnan[i][j] == 'L') i--;
        else j--;
    }
    reverse(ut.begin(), ut.end());

    cout << dp[n][m] << '\n' << ut << '\n';
    return 0;
}
