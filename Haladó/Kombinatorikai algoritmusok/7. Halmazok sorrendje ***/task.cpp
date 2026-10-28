/*
Megoldás lényege:
A rendezésben az a halmaz áll előrébb, amelyik tartalmazza a legnagyobb eltérő elemet, így a sorrend a
legnagyobb elem szerint épül fel: előbb azok a halmazok jönnek, amelyek tartalmazzák N-et (számuk C(N-1,K-1)),
utána a többiek. Az M-edik halmazt N-től lefelé haladva döntjük el: ha M legfeljebb C(x-1,K-1), akkor x benne
van a halmazban és K csökken, különben M-ből levonjuk C(x-1,K-1)-et, és x-et kihagyjuk. A binomiális
együtthatókat Pascal-háromszögben előre kiszámítjuk, N legfeljebb 30, így 64 biten belül maradnak.
Az időigény O(N), a táblázat 31 x 31 elem.
*/
/*
Hint 1: || Figyeld meg, hogy a rendezés a legnagyobb elem szerint csoportosít: az N-et tartalmazó halmazok állnak elől. Ez a döntés a többi elemre is ugyanígy ismételhető. ||
Hint 2: || Hány olyan K-elemű részhalmaza van a számok 1-től x-ig halmazának, amely tartalmazza x-et? Ez egy binomiális együttható, C(x-1,K-1), és N legfeljebb 30, így a Pascal-háromszög elég. ||
Hint 3: || Ha M legfeljebb ennyi, x benne van a halmazban, és K-t eggyel csökkented. Különben M-ből levonod ezt a számot, és x nélkül folytatod. A kiválasztott elemeket a végén növekvő sorrendben írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

using ull = unsigned long long;
static ull C[31][31];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int n = 0; n <= 30; ++n) {
        C[n][0] = C[n][n] = 1;
        for (int k = 1; k < n; ++k) C[n][k] = C[n - 1][k - 1] + C[n - 1][k];
    }

    int N, K;
    ull M;
    cin >> N >> K >> M;

    vector<int> ans;
    for (int x = N; x >= 1 && K > 0; --x) {
        ull cnt = C[x - 1][K - 1];
        if (M <= cnt) {
            ans.push_back(x);
            --K;
        } else {
            M -= cnt;
        }
    }

    reverse(ans.begin(), ans.end());
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}