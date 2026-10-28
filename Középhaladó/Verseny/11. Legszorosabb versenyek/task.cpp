/*
Megoldás lényege:
Egy versenyen csak azokat a pontokat vesszük figyelembe, amelyek elérték a verseny minimális pontszámát. Ha ilyenből legalább kettő van, a versenyen belüli pontszámkülönbség a legnagyobb és a legkisebb kiválasztott pont különbsége. Ezt a minimumot, maximumot és darabszámot egyetlen beolvasás közben követjük nyomon, így nem kell a pontokat tárolni. Az összes versenyen át keressük a legkisebb ilyen különbséget, és kiírjuk az ezt elérő versenyek sorszámait növekvő sorrendben. Ha egyetlen versenyben sincs legalább két érvényes pont, a 0 a válasz. Az időigény O(N·M).
*/
/*
Hint 1: || Egy versenyen csak a minimális pontszámot elérő résztvevők számítanak. Ha ezekből kevesebb mint kettő van, a verseny nem szerepelhet a rangsorban. ||
Hint 2: || Egy versenyen belüli legnagyobb különbség a kiválasztott pontok maximuma mínusz minimuma. Beolvasás közben tartsd nyilván a minimumot, a maximumot és a darabszámot, majd az összes versenyen keresd a legkisebb különbséget. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> mini(m);
    for (int i = 0; i < m; i++) {
        cin >> mini[i];
    }

    // diff[i] = -1, ha a versenyen legalább két minimumot elérő versenyző nincs
    vector<int> diff(m, -1);
    for (int i = 0; i < m; i++) {
        int ind;
        cin >> ind;
        int lo = INT_MAX, hi = INT_MIN, qualified = 0;
        for (int j = 0; j < ind; j++) {
            int s, p;
            cin >> s >> p;
            if (p >= mini[i]) {
                qualified++;
                lo = min(lo, p);
                hi = max(hi, p);
            }
        }
        if (qualified >= 2) {
            diff[i] = hi - lo;
        }
    }

    int best = -1;
    for (int i = 0; i < m; i++) {
        if (diff[i] >= 0 && (best < 0 || diff[i] < best)) {
            best = diff[i];
        }
    }

    vector<int> ans;
    if (best >= 0) {
        for (int i = 0; i < m; i++) {
            if (diff[i] == best) {
                ans.push_back(i + 1);
            }
        }
    }

    cout << ans.size();
    for (int x : ans) {
        cout << ' ' << x;
    }
    cout << '\n';
    return 0;
}
