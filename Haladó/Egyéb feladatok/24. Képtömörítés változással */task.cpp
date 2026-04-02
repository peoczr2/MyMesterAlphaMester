/*
Megoldás:
Az első sort teljes egészében ki kell írni futamokra bontva. Minden további sorban csak azokat
az összefüggő pozíciószakaszokat kell kiírni, ahol az aktuális sor eltér az előzőtől. Egy ilyen
szakaszon belül tovább bontunk azonos karakterű maximális részekre.

Ehhez elég mindig az előző és az aktuális sort tárolni. Minden cellát konstans sokszor vizsgálunk,
tehát az algoritmus O(N*M) idejű és O(M) memóriájú.
*/
/*
Hint 1: || Az első sor külön eset: ott nincs előző sor, ezért azt teljesen fel kell írni. ||
Hint 2: || A többi sornál először azt döntsd el, hogy egy pozíció változott-e az előző sorhoz képest. ||
Hint 3: || Csak a megváltozott, egymás utáni és azonos betűjű részekből kell kiírni egy rekordot. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<char> previous(m), current(m);
    for (int j = 0; j < m; ++j) {
        cin >> previous[j];
    }

    cout << n << ' ' << m << '\n';

    int left = 0;
    while (left < m) {
        int right = left;
        while (right + 1 < m && previous[right + 1] == previous[left]) {
            ++right;
        }
        cout << 1 << ' ' << (left + 1) << ' ' << (right + 1) << ' ' << previous[left] << '\n';
        left = right + 1;
    }

    for (int i = 1; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> current[j];
        }

        int pos = 0;
        while (pos < m) {
            if (current[pos] == previous[pos]) {
                ++pos;
                continue;
            }

            int start = pos;
            char color = current[pos];
            while (pos + 1 < m && current[pos + 1] != previous[pos + 1] && current[pos + 1] == color) {
                ++pos;
            }
            cout << (i + 1) << ' ' << (start + 1) << ' ' << (pos + 1) << ' ' << color << '\n';
            ++pos;
        }

        previous.swap(current);
    }

    return 0;
}