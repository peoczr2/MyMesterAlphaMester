/*
Megoldás lényege:
A fényképész akkor és csak akkor tud egy embert lefényképezni az [t, t+P-1]
intervallum alatt, ha ez a két zárt intervallum metszi egymást. Egy résztvevő
`[Érki, Távi]` időintervalluma ezért pontosan az `t` kezdőidőkre hat, amelyekre
`Érki-P+1 <= t <= Távi`.

Mivel az időpontok legfeljebb 10000-ig terjednek, minden résztvevő egy egyszerű
intervallumfrissítést ad a lehetséges kezdőidőkre. A prefixösszegből megkapjuk,
hány embert tud lefényképezni az adott kezdéssel, majd a legnagyobb értékhez a
legkésőbbi kezdőidőt választjuk.
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, p;
    cin >> n >> p;

    const int MAXT = 10000;
    vector<int> diff(MAXT + 3, 0);

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        int l = max(1, a - p + 1);
        int r = min(MAXT, b);
        if (l <= r) {
            ++diff[l];
            --diff[r + 1];
        }
    }

    int bestTime = 1;
    int bestCount = -1;
    int cur = 0;
    for (int t = 1; t <= MAXT; ++t) {
        cur += diff[t];
        if (cur > bestCount || (cur == bestCount && t > bestTime)) {
            bestCount = cur;
            bestTime = t;
        }
    }

    cout << bestTime << '\n' << bestCount << '\n';
    return 0;
}
