/*
Megoldás lényege:
Az előzőnél gyorsabb vonat az, amelynek menetideje kisebb, mint a közvetlenül előtte álló vonaté.
Balról jobbra haladva minden i-re (i ≥ 2) összevetjük az i-edik és az (i-1)-edik menetidőt, és az első olyan
i-t írjuk ki, ahol a mostani érték kisebb az előzőnél. Ha végig nincs ilyen vonat, a válasz -1.
Az időigény O(N), és a feladat egyetlen bejárással megoldható.
*/
/*
Hint 1: || Elég minden vonatot az őt közvetlenül megelőzőhöz hasonlítani, nem kell párokat keresgélni. ||
Hint 2: || Az első találatnál azonnal kiírhatod a sorszámot, mert a feladat az elsőt kéri. A vonatok sorszáma 1-től indul. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> t(n);
    for (int& x : t)
        cin >> x;

    for (int i = 1; i < n; ++i) {
        if (t[i] < t[i - 1]) {
            cout << i + 1 << "\n";
            return 0;
        }
    }

    cout << -1 << "\n";
    return 0;
}
