/*
Megoldás lényege:
A szigetek a 0-tól különböző mérések összefüggő szakaszai; az első és az utolsó szakasz a kontinenshez tartozik, ezeket kihagyjuk. Hegycsúcs az a mérés, amely 500 méternél magasabb, mindkét szomszédja pozitív, a bal oldali szomszédja kisebb nála, a jobb oldali szomszédja pedig szigorúan kisebb nála. Ilyen pont csak a sziget belső pontja lehet, így a szakasz első és utolsó mérését nem kell vizsgálni. Egy bejárásban a belső pontokat a mérések sorrendjében végigjárjuk, és a feltételt teljesítő magasságokat egy vektorba tesszük. A kiírás első sora a darabszám, a második sorban a magasságok állnak, ha van közöttük. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || Hegycsúcs csak olyan mérés lehet, amelynek mindkét szomszédja pozitív, vagyis ugyanabban a szigetben van. Így a sziget első és utolsó mérése soha nem csúcs. ||
Hint 2: || Egy bejárásban szakaszonként vizsgáld a belső pontokat: ha a mérés 500-nál magasabb, a bal szomszédja kisebb nála, a jobb szomszédja pedig szigorúan kisebb, tedd egy vektorba. A kontinenshez érő szakaszokat most is hagyd ki. ||
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

    vector<int> csucsok;  // a szigeteken lévő hegycsúcsok magasságai, a mérések sorrendjében

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

        // a szakasz szélső pontjainak egyik szomszédja 0, ezért csak a belsőket vizsgáljuk
        for (int j = l + 1; j < r; j++) {
            if (m[j] > 500 && m[j - 1] < m[j] && m[j] > m[j + 1]) csucsok.push_back(m[j]);
        }
    }

    cout << csucsok.size() << "\n";
    for (size_t k = 0; k < csucsok.size(); k++) {
        if (k > 0) cout << ' ';
        cout << csucsok[k];
    }
    if (!csucsok.empty()) cout << "\n";
    return 0;
}
