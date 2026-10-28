/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai, amelyek előtt és után is 0 áll. Az első és az utolsó mérés a kontinens fölött van, ezért az ezekhez érő szakasz nem sziget, ezeket kihagyjuk. Egy sziget magassága a rajta mért legnagyobb érték. Egyetlen bejárással minden szigeten kiszámoljuk a maximumot, és ha az 100-nál alacsonyabb, a magasságát sorban egy listába tesszük. A végén a lista hossza adja az első sort, a listaelemek a második sort. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Egy sziget a 0-tól különböző mérések összefüggő szakasza, amelynek előtte és utána is 0 áll. A kontinenshez érő első és utolsó szakasz nem sziget. ||
Hint 2: || Szakaszonként egy ciklusban keresd meg a legnagyobb mérést, és ha az 100-nál kisebb, tedd egy vektorba. A kiíráshoz a vektor mérete és elemei kellenek, a sorrend a balról jobbra haladásé. ||
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

    vector<int> alacsony;  // a 100 m-nél alacsonyabb szigetek magasságai, sorrendben

    int i = 0;
    while (i < n) {
        if (m[i] == 0) {
            i++;
            continue;
        }
        int l = i;
        int magassag = 0;
        while (i < n && m[i] > 0) {
            magassag = max(magassag, m[i]);
            i++;
        }
        int r = i - 1;  // a szakasz [l..r] indexei (0-tól számozva)

        if (l == 0 || r == n - 1) continue;  // a kontinenshez érő szakasz nem sziget
        if (magassag < 100) alacsony.push_back(magassag);
    }

    cout << alacsony.size() << "\n";
    if (!alacsony.empty()) {
        for (size_t k = 0; k < alacsony.size(); k++) {
            if (k > 0) cout << ' ';
            cout << alacsony[k];
        }
        cout << "\n";
    }
    return 0;
}
