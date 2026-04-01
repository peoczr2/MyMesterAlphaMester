/*
Megoldási ötlet:
Itt is a szerkesztési távolságot számoljuk, de most a műveletsort is ki kell írni. Ehhez suffix-DP-t használunk:
dp[i][j] a forrás szó i. pozíciójától és a cél szó j. pozíciójától kezdődő suffixek minimális átalakítási költsége.

Ezután előrefelé végigmegyünk a két szón. Mindig olyan lépést választunk, amelyik teljesíti a DP optimális
egyenletét. Így a kiírt pozíciók végig az eredeti szó indexei maradnak: törlés és csere az aktuális eredeti karakterre,
beszúrás pedig az aktuálisan már feldolgozott eredeti prefix mögé történik.
*/
/*
Hint 1: || A pozíciók miatt kényelmesebb suffixekre DP-zni, és utána balról jobbra generálni a műveleteket. ||
Hint 2: || Ha az aktuális két karakter azonos, optimális lépés nélkül továbbléphetsz. ||
Hint 3: || Beszúrásnál az index azt mondja meg, hány eredeti karakter mögé szúrsz be, ezért ez az aktuális i érték lesz. ||
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string source, target;
    cin >> source >> target;

    int n = static_cast<int>(source.size());
    int m = static_cast<int>(target.size());
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = n; i >= 0; --i) dp[i][m] = n - i;
    for (int j = m; j >= 0; --j) dp[n][j] = m - j;

    for (int i = n - 1; i >= 0; --i) {
        for (int j = m - 1; j >= 0; --j) {
            if (source[i] == target[j]) {
                dp[i][j] = dp[i + 1][j + 1];
            } else {
                dp[i][j] = min({dp[i + 1][j] + 1, dp[i][j + 1] + 1, dp[i + 1][j + 1] + 1});
            }
        }
    }

    vector<tuple<char, int, char>> operations;
    int i = 0;
    int j = 0;
    while (i < n || j < m) {
        if (i < n && j < m && source[i] == target[j] && dp[i][j] == dp[i + 1][j + 1]) {
            ++i;
            ++j;
            continue;
        }
        if (j < m && dp[i][j] == dp[i][j + 1] + 1) {
            operations.push_back({'B', i, target[j]});
            ++j;
            continue;
        }
        if (i < n && dp[i][j] == dp[i + 1][j] + 1) {
            operations.push_back({'T', i + 1, 0});
            ++i;
            continue;
        }
        operations.push_back({'C', i + 1, target[j]});
        ++i;
        ++j;
    }

    cout << operations.size() << '\n';
    for (const auto& [type, pos, ch] : operations) {
        cout << type << ' ' << pos;
        if (type != 'T') cout << ' ' << ch;
        cout << '\n';
    }
    return 0;
}