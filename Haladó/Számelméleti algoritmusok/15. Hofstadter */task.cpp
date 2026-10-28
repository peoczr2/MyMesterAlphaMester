/*
Megoldás lényege: a sorozatot közvetlenül szimuláljuk. Minden lépésben R_n = R_{n-1} + S_{n-1}, majd S_n a legkisebb
pozitív egész, amely még nem szerepel a korábbi R- és S-értékek között. Az értékeket egy "felhasznált" jelölőtömbben
tartjuk nyilván, így a szabad szám keresése egyszerű. S_n legfeljebb 2n lehet, mert az első n darab R- és az első
n-1 darab S-érték 2n-1 különböző szám, ezért 2n+5-ig tartó tömb elegendő. A keresés az előző S-értéktől indul,
így a teljes futás O(N) időigényű.
*/
/*
Hint 1: || A sorozat definíciója közvetlenül szimulálható, csak gyorsan kell tudnod megkeresni a legkisebb még nem használt pozitív egészet. ||
Hint 2: || Tarts fenn egy `used` tömböt, növeld R-et az előző S-sel, majd léptesd az új S jelöltjét addig, amíg szabad számot nem találsz. ||
Hint 3: || Gondold meg, meddig kell a tömböt tartani: n darab R-érték és n-1 darab S-érték már 2n-1 különböző számot foglal el, így S_n nem lehet nagyobb 2n-nél. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int limit = 2 * n + 5;
    vector<char> used(limit + 1, false);
    long long r = 1, s = 2;
    used[1] = used[2] = true;
    if (n == 1) {
        cout << 1 << ' ' << 2 << '\n';
        return 0;
    }
    for (int i = 2; i <= n; ++i) {
        r += s;
        if (r <= limit) used[(int)r] = true;
        int next = (int)s + 1;
        while (next <= limit && used[next]) ++next;
        s = next;
        if (s <= limit) used[s] = true;
    }
    cout << r << ' ' << s << '\n';
    return 0;
}
