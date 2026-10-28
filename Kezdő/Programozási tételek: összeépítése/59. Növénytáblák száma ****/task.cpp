/*
Megoldás lényege:
Egy növénytábla olyan téglalap, amelyben csupa azonos növény áll, és amelyet egyik irányban sem lehet ugyanazzal a növénnyel tovább bővíteni.
A táblák átfedhetik egymást, a feladat az összes ilyen maximális téglalap számát kéri.
Minden téglalapot a bal felső sarka határoz meg, ezért minden mezőből indulva a magasságot fokozatosan növeljük, és közben nyilvántartjuk, meddig terjedhet az egyneműség vízszintesen.
Egy (magasság, szélesség) pár akkor ad táblát, ha a téglalap egyneműen kitöltött, és sem fel, sem le, sem balra, sem jobbra nem bővíthető.
A jobbra és lefelé mért azonos növényű futamhosszakat előre kiszámoljuk, így minden ellenőrzés O(1), az összes művelet a négy dimenzió szorzatával arányos, ami 50×50 méretnél bőven belefér.
*/
/*
Hint 1: || Egy növénytábla olyan téglalap, amelyben csak egyféle növény áll, és amelyet egy sorral vagy oszloppal sem lehet tovább bővíteni; a táblák átfedhetik egymást, ezért az ilyen téglalapok számát kell megszámolni. ||
Hint 2: || Minden téglalapot a bal felső sarka határoz meg: előre számold ki minden mezőre, hogy jobbra és lefelé hány egymás utáni azonos növényű mező van, így az egyneműség ellenőrzése O(1) lesz. ||
Hint 3: || Egy kezdőpontból a magasságot növelve a szélesség felső korlátja a sorok futamhosszainak minimuma; minden (magasság, szélesség) párnál nézd meg, hogy a négy irány közül van-e olyan, amerre még lehet bővíteni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<vector<string>> g(n, vector<string>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            cin >> g[i][j];

    // jobbra[i][j]: azonos növényű mezők száma (i,j)-től jobbra; lefele[i][j]: ugyanez lefelé
    vector<vector<int>> jobbra(n, vector<int>(m, 1)), lefele(n, vector<int>(m, 1));
    for (int i = 0; i < n; i++)
        for (int j = m - 2; j >= 0; j--)
            if (g[i][j + 1] == g[i][j]) jobbra[i][j] = 1 + jobbra[i][j + 1];
    for (int j = 0; j < m; j++)
        for (int i = n - 2; i >= 0; i--)
            if (g[i + 1][j] == g[i][j]) lefele[i][j] = 1 + lefele[i + 1][j];

    long long tables = 0;
    for (int r1 = 0; r1 < n; r1++) {
        for (int c1 = 0; c1 < m; c1++) {
            const string &p = g[r1][c1];
            int szeleseg = INT_MAX;  // ennyi széles lehet a téglalap az aktuális magasságnál

            for (int h = 1; r1 + h - 1 < n; h++) {
                int r = r1 + h - 1;
                if (g[r][c1] != p) break;
                szeleseg = min(szeleseg, jobbra[r][c1]);

                // balra bővíthető-e: a bal oszlop az egész magasságban azonos növény
                bool balra = c1 > 0 && g[r1][c1 - 1] == p && lefele[r1][c1 - 1] >= h;
                if (balra) continue;

                for (int w = 1; w <= szeleseg; w++) {
                    bool fel = r1 > 0 && g[r1 - 1][c1] == p && jobbra[r1 - 1][c1] >= w;
                    bool le = r1 + h < n && g[r1 + h][c1] == p && jobbra[r1 + h][c1] >= w;
                    bool jobb = c1 + w < m && g[r1][c1 + w] == p && lefele[r1][c1 + w] >= h;
                    if (!fel && !le && !jobb) tables++;
                }
            }
        }
    }

    cout << tables << "\n";
    return 0;
}
