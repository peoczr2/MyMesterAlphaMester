/*
Megoldás lényege:
A völgy olyan pont a szigeten, amelynek a bal és a jobb oldalán is van nála magasabb mérés ugyanazon a szigeten. A szigeteket a 0-tól különböző mérések összefüggő szakaszai adják; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Szigetenként a bal oldali maximumot balról haladva tartjuk nyilván, a jobb oldalit egy előre kiszámolt segédtömbből vesszük, így minden pont O(1) alatt ellenőrizhető. A legtöbb völgyet tartalmazó sziget partjait tartjuk meg, döntetlennél a balról első marad. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy pont akkor völgy, ha a szigeten belül van nála magasabb pont balra is és jobbra is. A szigetek határait most is a 0 mérések adják, a kontinenshez érő szakaszt hagyd ki. ||
Hint 2: || Balról jobbra haladva tartsd nyilván az eddigi maximumot, a jobb oldali maximumot pedig egy segédtömbben számold ki jobbról balra. Így minden pontról konstans időben eldönthető, hogy völgy-e. ||
Hint 3: || Szigetenként számold meg a völgyeket egy változóban. Ha az aktuális sziget völgyeinek száma szigorúan nagyobb az eddigi legnagyobbnál, jegyezd meg a sziget két partját is. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> m(n);
    for (auto &x : m) cin >> x;

    int legtobb = -1;       // az eddigi legtöbb völgy száma egy szigeten
    int bal = 0, jobb = 0;  // a legtöbb völgyet tartalmazó sziget partjai (1-től számozva), 0: nincs sziget

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a sziget [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        int len = r - l + 1;
        vector<int> suffix(len + 1, 0);  // suffix[k] = max(m[l+k..r])
        for (int k = len - 1; k >= 0; k--) {
            suffix[k] = max(m[l + k], suffix[k + 1]);
        }

        int prefix = 0;  // max(m[l..j-1]): a bal oldali legnagyobb mérés
        int volgyek = 0;
        for (int j = l; j <= r; j++) {
            if (prefix > m[j] && suffix[j - l + 1] > m[j]) volgyek++;
            prefix = max(prefix, m[j]);
        }

        if (volgyek > legtobb) {
            legtobb = volgyek;
            bal = l + 1;
            jobb = r + 1;
        }
    }

    if (bal == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal << ' ' << jobb << "\n";
    }
    return 0;
}
