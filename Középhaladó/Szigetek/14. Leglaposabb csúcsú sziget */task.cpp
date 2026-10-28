/*
Megoldás lényege:
A szigetek most is a pozitív mérések összefüggő szakaszai, az első és az utolsó szakasz nem számít. Csúcs az a belső mérés egy szigeten, amelynek a két szomszédja kisebb nála, és a két szomszéd is pozitív, így a csúcs biztosan egy sziget belsejében van. Egy csúcs meredekségét a két oldal közül a meredekebbik adja, azaz a nagyobbik különbség. Egy bejárással minden szigeten megnézzük a csúcsait, és a legkisebb meredekségű csúcs szigetét tartjuk meg; döntetlennél a balról első szigetet. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Keresd meg a szigeteket: a pozitív mérések összefüggő szakaszai, amelyek nem érnek az első vagy az utolsó méréshez. Csúcs csak olyan mérés lehet, amelynek mindkét szomszédja pozitív és kisebb nála. ||
Hint 2: || Egy csúcs meredeksége a két szomszédos különbség közül a nagyobb abszolút érték. Ezt egy sziget szakaszán belül minden csúcsra kiszámolhatod. ||
Hint 3: || Tartsd nyilván az eddigi legkisebb meredekséget, és ha egy csúcs ennél kisebb, írd felül a megtalált sziget bal és jobb partjával. ||
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

    int legkisebb = INT_MAX;  // az eddigi legkisebb csúcsmeredekség
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

        // csúcs: a belső mérések közül az, amelynek mindkét szomszédja kisebb nála
        for (int j = l + 1; j < r; j++) {
            if (m[j - 1] < m[j] && m[j] > m[j + 1]) {
                int meredek = max(m[j] - m[j - 1], m[j] - m[j + 1]);
                if (meredek < legkisebb) {
                    legkisebb = meredek;
                    bal_part = l + 1;
                    jobb_part = r + 1;
                }
            }
        }
    }

    if (bal_part == 0) {
        cout << 0 << "\n";
    } else {
        cout << bal_part << ' ' << jobb_part << "\n";
    }
    return 0;
}
