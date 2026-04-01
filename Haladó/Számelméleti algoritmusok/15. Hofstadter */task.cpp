/*
 * A Hofstadter R-S sorozatot a definíció alapján szimuláljuk. Mivel az S_n
 * értékek legfeljebb 2n-ig terjednek, elegendő 2N-ig nyilvántartani a felhasznált
 * számokat.
 
Hint 1: || A sorozat definíciója közvetlenül szimulálható, csak gyorsan kell tudnod megkeresni a legkisebb még nem használt pozitív egészet. ||
Hint 2: || Tarts fenn egy `used` tömböt, növeld R-et az előző S-sel, majd léptesd az új S jelöltjét addig, amíg szabad számot nem találsz. ||
*/

#include "../common.hpp"

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
