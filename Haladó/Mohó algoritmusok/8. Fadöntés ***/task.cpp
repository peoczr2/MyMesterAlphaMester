/*
Megoldás lényege:
Egy kidőlő fa a jobb oldalán a [x_i, x_i + h_i] szakaszt érinti, és minden ebbe eső (a szakasz végpontjára eső is) fa szintén kidől, így az i-edik fa láncreakciójának jobb végpontja (reach) egy balról jobbra haladó bejárással kiszámítható. A legtöbb fát kidöntő fa az, amelynek [x_i, reach_i] szakaszába a legtöbb fa esik. A minimális kivágásszám balról jobbra haladó mohó intervallumfedés: az első még álló fát kivágjuk, a kidőlt szakasz végét a láncreakciók alapján frissítjük, és az első nem kidőlt fánál folytatjuk. Az időigény O(N^2), ami N <= 1000 mellett bőven belefér az időlimitbe.
*/
/*
Hint 1: || Egy fa kidőlése a jobb oldali fák láncán keresztül tovább terjedhet. ||
Hint 2: || Egy fa kidőlési végpontja x+h-val kezdődik, és minden olyan jobb oldali fával bővül, amelyik ebbe a szakaszba esik. ||
Hint 3: || Balról haladva mindig az első még álló fát vágd ki, majd ugorj a kidőlt szakasz végéig; a lépések száma adja a minimális kivágásszámot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> x(n + 1), h(n + 1), reach(n + 1);
    for (int i = 1; i <= n; ++i) cin >> x[i] >> h[i];

    for (int i = 1; i <= n; ++i) {
        long long cur = x[i] + h[i];
        int j = i + 1;
        while (j <= n && x[j] <= cur) {
            cur = max(cur, x[j] + h[j]);
            ++j;
        }
        reach[i] = cur;
    }

    int bestIdx = 1;
    long long bestFall = 1;
    for (int i = 1; i <= n; ++i) {
        long long cnt = upper_bound(x.begin() + 1, x.end(), reach[i]) - (x.begin() + i);
        if (cnt > bestFall) {
            bestFall = cnt;
            bestIdx = i;
        }
    }

    int cuts = 0;
    int i = 1;
    while (i <= n) {
        ++cuts;
        long long far = reach[i];
        int j = i + 1;
        while (j <= n && x[j] <= far) {
            far = max(far, reach[j]);
            ++j;
        }
        i = j;
    }

    cout << cuts << '\n' << bestIdx << '\n';
    return 0;
}