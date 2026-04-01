/*
Megoldási ötlet:
Most a K darab összefüggő szakasz közül a legnagyobb szakaszösszeget akarjuk minimalizálni. Ha adott egy X felső korlát, akkor
greedyn a lehető leghosszabb, de még X-be beleférő szakaszokat vágva megkapjuk a szükséges kamionszám minimumát. Ha ez legfeljebb K,
akkor az X korlát megvalósítható.

Az optimális X-et binárisan keressük. A konkrét K szakaszhoz visszafelé építkezünk: jobbról balra haladva új kamiont indítunk, ha a
következő elem már nem férne bele az X korlátba, vagy ha különben nem maradna elég elem a még szükséges kamionokra.
*/
/*
Hint 1: || Az eldöntési változat itt az, hogy X-nél nagyobb összegű szakasz tilos. ||
Hint 2: || Egy fix X mellett a minimális kamionszámot a lehető leghosszabb greedyn szakaszok adják. ||
Hint 3: || A pontosan K kezdőindexhez jobbról balra kell vágni, hogy biztosan maradjon minden kamionra legalább egy konténer. ||
*/

#include <bits/stdc++.h>
using namespace std;

static bool feasible(const vector<int>& a, int k, long long lim) {
    long long sum = 0;
    int cnt = 1;
    for (int x : a) {
        if (x > lim) return false;
        if (sum + x > lim) {
            ++cnt;
            sum = x;
        } else {
            sum += x;
        }
    }
    return cnt <= k;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n + 1);
    long long lo = 0, hi = 0, ans = 0;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
        lo = max<long long>(lo, a[i]);
        hi += a[i];
    }

    vector<int> raw(a.begin() + 1, a.end());
    while (lo <= hi) {
        long long mid = (lo + hi) / 2;
        if (feasible(raw, k, mid)) {
            ans = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }

    vector<int> starts;
    long long sum = 0;
    int segmentsLeft = k;
    for (int i = n; i >= 1; --i) {
        if (sum + a[i] > ans || i < segmentsLeft) {
            starts.push_back(i + 1);
            --segmentsLeft;
            sum = a[i];
        } else {
            sum += a[i];
        }
    }
    starts.push_back(1);
    reverse(starts.begin(), starts.end());

    cout << ans << '\n';
    for (int i = 0; i < (int)starts.size(); ++i) {
        if (i) cout << ' ';
        cout << starts[i];
    }
    cout << '\n';
    return 0;
}