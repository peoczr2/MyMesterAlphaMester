/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai, amelyek előtt és után is 0 áll. Az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Egy sziget szélessége a bal és a jobb part közötti mérések száma. Egy bejárással minden szigetet megvizsgálunk, és a legszélesebbet tartjuk meg; döntetlennél a balról első marad. A kiírás a sziget bal és jobb partjának sorszáma, ha nincs sziget, a válasz 0. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A sziget a 0-tól különböző mérések összefüggő szakasza, amelynek előtte és utána is 0 áll. A kontinenshez érő első és utolsó szakasz nem sziget. ||
Hint 2: || Egy bejárásban szakaszonként számold ki a szélességet a két part sorszámából, és csak a szigorúan nagyobbnál írd felül az eddigi legjobbat. ||
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

    int legszelesebb = 0;  // az eddigi legszélesebb sziget szélessége, 0: még nincs
    int bal = 0, jobb = 0; // a legszélesebb sziget partjai (1-től számozva)

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

        int szelesseg = r - l + 1;
        if (szelesseg > legszelesebb) {
            legszelesebb = szelesseg;
            bal = l + 1;
            jobb = r + 1;
        }
    }

    if (legszelesebb == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal << ' ' << jobb << "\n";
    }
    return 0;
}
