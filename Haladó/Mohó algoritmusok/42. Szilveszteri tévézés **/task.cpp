/*
Feladat: A lehető legtöbb teljes filmet kell megnézni úgy, hogy egyszerre csak egy film mehet.
Ötlet: Az intervallumokat befejezési idő szerint rendezzük, és mindig a legkorábban végződő, még nem ütköző filmet választjuk.
Hint 1: || Csak teljes filmet nézünk, ezért az átfedés kizáró ok. ||
Hint 2: || A korábban befejező filmek több későbbi filmet hagynak meg. ||
Hint 3: || A kiválasztott filmek összideje csak a hosszok összege. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Movie { int s, e, id; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Movie> a(n);
    for (int i = 0; i < n; ++i) {
        int channel, ch1, cm1, ch2, cm2;
        cin >> channel >> ch1 >> cm1 >> ch2 >> cm2;
        a[i].s = ch1 * 60 + cm1;
        a[i].e = ch2 * 60 + cm2;
        a[i].id = i + 1;
    }
    sort(a.begin(), a.end(), [](const Movie &x, const Movie &y) {
        if (x.e != y.e) return x.e < y.e;
        if (x.s != y.s) return x.s < y.s;
        return x.id < y.id;
    });

    vector<int> ans;
    int last = -1;
    int total = 0;
    for (auto &m : a) {
        if (m.s >= last) {
            ans.push_back(m.id);
            total += m.e - m.s;
            last = m.e;
        }
    }

    cout << ans.size() << ' ' << total << '\n';
    for (int x : ans) cout << x << '\n';
    return 0;
}