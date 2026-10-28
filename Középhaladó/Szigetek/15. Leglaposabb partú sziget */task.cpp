/*
Megoldás lényege:
A szigetek most is a pozitív mérések összefüggő szakaszai, amelyek nem érnek az első vagy az utolsó méréshez. Egy part meredeksége a parti mérés és a tengerszint (0) különbsége, azaz maga a parti mérés magassága. Egy sziget leglaposabb partja a két part közül a kisebb meredekségű. Egy bejárással minden szigetre kiszámoljuk ezt a minimumot, és azt a szigetet tartjuk meg, amelynek a legkisebb ilyen értéke van; döntetlennél a balról első szigetet. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A part meredeksége a parti mérés magassága, mert a tengerszint 0. Egy sziget két partja a szakasz első és utolsó pozitív mérése. ||
Hint 2: || Egy szigetnél a leglaposabb part a két partmagasság közül a kisebb. Ezt a minimumot tartsd nyilván, és a legkisebb eddigi értékhez tartozó sziget bal és jobb partját jegyezd meg. ||
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

    int legkisebb = INT_MAX;  // az eddigi legkisebb partmeredekség
    int bal_part = 0, jobb_part = 0;  // 1-től számozott partok, 0: nincs sziget

    int i = 0;
    while (i < n) {
        if (m[i] <= 0) {
            i++;
            continue;
        }
        int l = i;
        while (i + 1 < n && m[i + 1] > 0) i++;
        int r = i;
        i++;

        if (l == 0 || r == n - 1) continue;  // a kontinens szakasza nem sziget

        int laposabb_part = min(m[l], m[r]);  // a sziget leglaposabb partja
        if (laposabb_part < legkisebb) {
            legkisebb = laposabb_part;
            bal_part = l + 1;
            jobb_part = r + 1;
        }
    }

    if (bal_part == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal_part << ' ' << jobb_part << "\n";
    }
    return 0;
}
