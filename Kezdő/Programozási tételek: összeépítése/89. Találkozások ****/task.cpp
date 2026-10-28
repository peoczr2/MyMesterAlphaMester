/*
Két ember pontosan akkor találkozik, ha az egyik érkezése nem későbbi a másik távozásánál, és ez fordítva is igaz. Az egyenlőség is találkozásnak számít. Az i-edik emberrel találkozók száma ezért: hány érkezés van legfeljebb T_i-ig, mínusz hány távozás van E_i előtt, mert az utóbbi emberek mindig teljesítik az első feltételt. Végül a saját magunkat levonjuk. Az érkezési és távozási időpontokat külön-külön rendezzük, így minden emberre két bináris keresés adja az eredményt. Az időigény O(N log N), a memóriaigény O(N). A legtöbb találkozót elérő, legkisebb sorszámú embert írjuk ki.
*/
/*
Hint 1: || Két ember pontosan akkor találkozik, ha az egyik érkezése nem későbbi, mint a másik távozása, és ez fordítva is igaz. Az egyenlőség is találkozás, vagyis az egyik távozása és a másik érkezése egy időpontra esik. ||
Hint 2: || Rendezd külön az érkezési és a távozási időpontokat. Az i-edik emberre a találkozók száma: (hány érkezés van legfeljebb T_i-ig) - (hány távozás van E_i előtt), és ebből a saját magadat vond le. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> e(n), t(n);
    for (int i = 0; i < n; i++) cin >> e[i] >> t[i];

    vector<int> se = e, st = t;
    sort(se.begin(), se.end());
    sort(st.begin(), st.end());

    int legjobbEmber = 1, legjobbDb = -1;
    for (int i = 0; i < n; i++) {
        // hány ember érkezése nem későbbi, mint T_i
        int felso = upper_bound(se.begin(), se.end(), t[i]) - se.begin();
        // hány ember távozása előzi meg E_i-t (ezek mind szerepelnek a felsőben)
        int also = lower_bound(st.begin(), st.end(), e[i]) - st.begin();
        int db = felso - also - 1; // a saját magunkat nem számoljuk
        if (db > legjobbDb) {
            legjobbDb = db;
            legjobbEmber = i + 1;
        }
    }

    cout << legjobbEmber << "\n" << legjobbDb << "\n";
    return 0;
}
