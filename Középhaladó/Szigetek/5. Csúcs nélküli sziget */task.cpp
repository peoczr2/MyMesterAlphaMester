/*
Megoldás lényege:
A 0-ás mérések darabolják a szigeteket: egy sziget a nullától különböző mérések összefüggő
szakasza, bal partja a szakasz első, jobb partja az utolsó mérése. Csak az a szakasz kap
mindkét partot, amelyet előtte és utána is 0-ás mérés határol, mert az első és az utolsó mérés
nem 0, így a szélső szakaszoknak nincs mindkét partjuk. Csúcs csak a sziget belső mérésénél
lehet, mert a csúcs feltétele pozitív szomszédot kíván, a partok szomszédja pedig 0. Balról
jobbra haladva az első csúcs nélküli sziget adja a választ, ami az Európához legközelebbi
megoldás. Az időigény O(N), mert minden mérést legfeljebb kétszer nézünk meg.
*/
/*
Hint 1: || A 0-ás mérések választják el a szigeteket: keresd meg a nullától különböző mérések összefüggő szakaszait. Csak az a szakasz érdekes, amelynek előtte és utána is van 0. ||
Hint 2: || Egy belső mérés akkor csúcs, ha mindkét szomszédjánál nagyobb. A szakasz első és utolsó eleme sosem csúcs, mert az egyik szomszédjuk 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> h(n + 2, 0);  // h[1..n] a mérések, h[0] és h[n+1] nulla
    for (int i = 1; i <= n; i++) cin >> h[i];

    int i = 1;
    while (i <= n) {
        if (h[i] == 0) {
            i++;
            continue;
        }
        // egy sziget: a nullától különböző mérések összefüggő szakasza [l, r]
        int l = i;
        while (i <= n && h[i] > 0) i++;
        int r = i - 1;

        // csak az a sziget érdekes, amelynek van bal és jobb partja
        if (l == 1 || r == n) continue;

        // belső elemek csúcs-ellenőrzése: A < B > C
        bool van_csucs = false;
        for (int j = l + 1; j < r; j++) {
            if (h[j - 1] < h[j] && h[j] > h[j + 1]) {
                van_csucs = true;
                break;
            }
        }
        if (!van_csucs) {
            cout << l << ' ' << r << '\n';
            return 0;
        }
    }

    cout << 0 << '\n';
    return 0;
}
