/*
Megoldás lényege:
Sziget magassága a rajta mért legnagyobb érték. A szigeteket a 0-tól különböző mérések összefüggő szakaszai adják; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Egy bejárással minden szigeten kiszámoljuk a legnagyobb mérést, és ha az 1000-nél magasabb, a mérések sorrendjében egy listához fűzzük. A kiírás első sora a lista hossza, a második sorban a listaelemek állnak; ha nincs ilyen sziget, csak a 0 kerül ki. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A sziget magassága a rajta mért legnagyobb érték, és csak az 1000-nél szigorúan magasabbakat kell kiírni. A kontinenshez érő első és utolsó szakasz most sem sziget. ||
Hint 2: || Egy bejárásban szakaszonként tartsd nyilván a legnagyobb mérést, a szakasz végén pedig ha nagyobb 1000-nél, tedd egy vektorba. A kiírásnál a vektor mérete adja az első sort, az elemei a másodikat. ||
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

    vector<int> magas;  // az 1000 m-nél magasabb szigetek magasságai, a mérések sorrendjében

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        int csucs = 0;  // a sziget legmagasabb pontja
        while (i < n && m[i] > 0) {
            csucs = max(csucs, m[i]);
            i++;
        }
        int r = i - 1;  // a sziget [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget
        if (csucs > 1000) magas.push_back(csucs);
    }

    cout << magas.size() << "\n";
    if (!magas.empty()) {
        for (size_t k = 0; k < magas.size(); k++) {
            if (k > 0) cout << ' ';
            cout << magas[k];
        }
        cout << "\n";
    }
    return 0;
}
