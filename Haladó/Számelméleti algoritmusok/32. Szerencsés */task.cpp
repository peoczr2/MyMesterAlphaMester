/*
 * Lucky number sieve.
 
Hint 1: || Ez egy szita, csak itt nem prímos számokat törölsz, hanem mindig a következő megmaradt szám lépésközével. ||
Hint 2: || Tartsd fenn a még megmaradt listát, és a 2., 3., 7., ... megmaradt számok szerint szűrd újra meg újra. ||
*/

#include "../common.hpp"

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    iota(a.begin(), a.end(), 1);
    for (int i = 1; i < (int)a.size(); ++i) {
        int step = a[i];
        if (step > (int)a.size()) break;
        vector<int> b;
        b.reserve(a.size());
        for (int j = 0; j < (int)a.size(); ++j) {
            if ((j + 1) % step != 0) b.push_back(a[j]);
        }
        a.swap(b);
    }
    for (int i = 0; i < (int)a.size(); ++i) {
        if (i) cout << ' ';
        cout << a[i];
    }
    cout << '\n';
    return 0;
}
