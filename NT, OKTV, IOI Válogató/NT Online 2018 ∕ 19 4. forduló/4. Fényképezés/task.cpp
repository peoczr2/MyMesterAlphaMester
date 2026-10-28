/*
Megoldás lényege:
A fényképész akkor és csak akkor tud egy embert lefényképezni az [t, t+P-1]
intervallum alatt, ha ez a két zárt intervallum metszi egymást. Egy résztvevő
`[Érki, Távi]` időintervalluma ezért pontosan a `t` kezdőidőkre hat, amelyekre
`Érki-P+1 <= t <= Távi`.

Mivel az időpontok legfeljebb 10000-ig terjednek, minden résztvevő egy egyszerű
intervallumfrissítést ad a lehetséges kezdőidőkre. A prefixösszegből megkapjuk,
hány embert tud lefényképezni az adott kezdéssel. A fényképész csak a legkorábbi
érkezés és a legkésőbbi távozás között lehet, így a kezdőidők tartománya
[legkorábbi érkezés, legkésőbbi távozás - P + 1]; ezen belül a legnagyobb értékhez
a legkésőbbi kezdőidőt választjuk.
*/
/*
Hint 1: || Egy ember [Érki, Távi] időintervalluma akkor metszi a fényképész [t, t+P-1] intervallumát, ha Érki-P+1 <= t <= Távi. Így minden emberhez egy t-intervallum tartozik, amelyen belül a lefényképezhetők száma eggyel nő. ||
Hint 2: || Az időpontok legfeljebb 10000-ig terjednek, ezért a növekmények egy különbségi tömbbe írhatók, és a prefixösszegből minden t-re megkapható a lefényképezhetők száma. ||
Hint 3: || A fényképész csak a legkorábbi érkezés és a legkésőbbi távozás között lehet, vagyis t >= min(Érki) és t+P-1 <= max(Távi). Ezen a tartományon kell a maximumot keresni, egyenlőség esetén a legkésőbbi t-t választva. ||
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
    int legkorabbi = MAXT;
    int legkesobbi = 1;

    for (int i = 0; i < n; ++i) {
        int a, b;
        cin >> a >> b;
        legkorabbi = min(legkorabbi, a);
        legkesobbi = max(legkesobbi, b);
        int l = max(1, a - p + 1);
        int r = min(MAXT, b);
        if (l <= r) {
            ++diff[l];
            --diff[r + 1];
        }
    }

    // A fényképész nem érkezhet a legelső érkezés előtt és nem távozhat a legutolsó távozás után.
    int lo = legkorabbi;
    int hi = max(lo, legkesobbi - p + 1);

    int bestTime = lo;
    int bestCount = -1;
    int cur = 0;
    for (int t = 1; t <= hi; ++t) {
        cur += diff[t];
        if (t >= lo && cur >= bestCount) {
            bestCount = cur;
            bestTime = t;
        }
    }

    cout << bestTime << '\n' << bestCount << '\n';
    return 0;
}
