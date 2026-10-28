/*
Megoldás lényege:
Völgy az a sziget belső pontja, amelynek a szigeten belül van nála magasabb pont a bal oldalán és a jobb oldalán is. A szigeteket a 0-tól különböző mérések összefüggő szakaszai adják; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Szigetenként a balról haladva az eddigi maximumot, a jobbról számítva pedig a hátralévő szakasz maximumát tároljuk egy tömbben, így minden pont ellenőrzése O(1). A legmélyebb völgyet tartjuk meg, a döntetlen esetén a balról első marad, és a hozzá tartozó sziget bal és jobb partját írjuk ki. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy pont akkor völgy, ha a szigeten belül van nála magasabb pont balra is és jobbra is. A szigetek határait most is a nulla mérések adják, az első és az utolsó szakasz nem sziget. ||
Hint 2: || Szigetenként számold ki egy tömbben, hogy az adott indextől jobbra mekkora a legnagyobb mérés, a bal oldali maximumot pedig egy változóban viheted végig. A völgyek közül a legkisebb magasságút tartsd meg, a partjaival együtt. ||
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

    int legmelyebb = INT_MAX;  // az eddigi legmélyebb völgy magassága
    int bal = 0, jobb = 0;     // a legmélyebb völgyű sziget partjai (1-től számozva), 0: nincs völgy

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        while (i < n && m[i] > 0) i++;
        int r = i - 1;  // a szakasz [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget

        int len = r - l + 1;
        vector<int> suffix(len + 1, 0);  // suffix[k] = max(m[l+k..r])
        for (int k = len - 1; k >= 0; k--) {
            suffix[k] = max(m[l + k], suffix[k + 1]);
        }

        int prefix = 0;  // max(m[l..j-1]): a bal oldali legnagyobb mérés
        for (int j = l; j <= r; j++) {
            if (j > l && j < r && prefix > m[j] && suffix[j - l + 1] > m[j] && m[j] < legmelyebb) {
                legmelyebb = m[j];
                bal = l + 1;
                jobb = r + 1;
            }
            prefix = max(prefix, m[j]);
        }
    }

    if (bal == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal << ' ' << jobb << "\n";
    }
    return 0;
}
