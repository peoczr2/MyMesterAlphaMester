/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai, amelyek előtt és után is 0 áll; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Egy csúcs a sziget belső eleme, amelynek mindkét szomszédja kisebb nála. Egy csúcs meredekségét a két oldal különbségeinek nagyobbika adja, ami egyenlő a csúcs magasságának és a két szomszéd közül a kisebbiknek a különbségével. Egyetlen bejárással minden csúcs meredekségét konstans időben kiszámoljuk, és az eddigi legmeredekebbnél szigorúan meredekebb csúcs sziget partjait tartjuk meg, így döntetlen esetén a balról első sziget marad. Az időigény O(N), a memóriaigény O(1) a mérések tárolásán kívül.
*/
/*
Hint 1: || Egy csúcs meredekségét a két szomszédos különbség közül a nagyobb adja. Ez ugyanaz, mint a csúcs magassága mínusz a két szomszéd közül a kisebbik. ||
Hint 2: || Minden szigeten belüli csúcsra számold ki a meredekségét egy kis képlettel, és az eddigi legnagyobbat tartsd nyilván a sziget két partjával együtt. Csak szigorúan nagyobb meredekségnél írd felül. ||
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

    int legmeredekebb = 0;  // az eddigi legnagyobb meredekség (0: még nincs csúcs)
    int bal = 0, jobb = 0;  // a legmeredekebb csúcsú sziget partjai (1-től számozva)

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

        for (int j = l + 1; j < r; j++) {
            if (m[j - 1] < m[j] && m[j] > m[j + 1]) {
                int meredekseg = m[j] - min(m[j - 1], m[j + 1]);
                if (meredekseg > legmeredekebb) {
                    legmeredekebb = meredekseg;
                    bal = l + 1;
                    jobb = r + 1;
                }
            }
        }
    }

    if (legmeredekebb == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal << ' ' << jobb << "\n";
    }
    return 0;
}
