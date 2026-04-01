/*
Megoldási ötlet:
Ha a városokban levő rendőröket egyenként felsoroljuk, akkor a legtöbb lefedhető város száma pontosan a rendőrök száma. Ezután már
csak azt kell eldönteni, mely városokba kerüljön ez a P darab rendőr úgy, hogy minden kiválasztott városba pontosan egy jusson, és az
összes mozgatási költség minimális legyen.

Az optimális párosítás rendezett: a balról jobbra vett rendőröket a balról jobbra vett célvárosokhoz kell illeszteni. Legyen dp[i][j]
az első i rendőrt az első j város közül kiválasztott i városba helyezésének minimális költsége. A város j vagy bekerül, vagy kimarad.
Visszafejtéssel megkapjuk a végső 0/1 városlistát.
*/
/*
Hint 1: || Először bontsd fel az induló állapotot egy rendezett rendőrpozíció-listára. ||
Hint 2: || Ha a célvárosokat növekvő sorrendben választod, akkor az i-edik rendőrt az i-edik kiválasztott városhoz kell rendelni. ||
Hint 3: || Ezután már csak egy „várost választunk vagy kihagyunk” típusú DP marad. ||
*/

#include <bits/stdc++.h>
using namespace std;

static const long long INF = (1LL << 60);

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> cnt(n + 1);
    vector<int> pos;
    for (int i = 1; i <= n; ++i) {
        cin >> cnt[i];
        for (int j = 0; j < cnt[i]; ++j) pos.push_back(i);
    }

    int p = static_cast<int>(pos.size());
    if (p == 0) {
        cout << 0 << '\n';
        for (int i = 1; i <= n; ++i) {
            if (i > 1) cout << ' ';
            cout << 0;
        }
        cout << '\n';
        return 0;
    }

    pos.insert(pos.begin(), 0);
    vector<vector<long long>> dp(p + 1, vector<long long>(n + 1, INF));
    vector<vector<char>> take(p + 1, vector<char>(n + 1, 0));

    for (int j = 0; j <= n; ++j) dp[0][j] = 0;
    for (int i = 1; i <= p; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = dp[i][j - 1];
            if (dp[i - 1][j - 1] != INF) {
                long long cand = dp[i - 1][j - 1] + llabs(pos[i] - j);
                if (cand < dp[i][j]) {
                    dp[i][j] = cand;
                    take[i][j] = 1;
                }
            }
        }
    }

    vector<int> used(n + 1, 0);
    int i = p, j = n;
    while (i > 0 && j > 0) {
        if (take[i][j]) {
            used[j] = 1;
            --i;
            --j;
        } else {
            --j;
        }
    }

    cout << dp[p][n] << '\n';
    for (int city = 1; city <= n; ++city) {
        if (city > 1) cout << ' ';
        cout << used[city];
    }
    cout << '\n';
    return 0;
}