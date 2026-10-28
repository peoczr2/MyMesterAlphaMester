/*
Megoldás lényege:
A számsorozat növekvően rendezett, ezért minden tipphez bináris kereséssel (lower_bound) megkeressük az első olyan elemet, amely nem kisebb a tippnél. A választ ez az elem és az előtte álló elem dönti el: a két távolság közül a kisebbet keressük, egyenlőségnél a kisebb értéket írjuk ki. Ha a tipp a sorozat elé vagy mögé esik, csak az egyik jelölt létezik. Minden tipp O(log N) időben feldolgozható, így az összidő O(N + M log N).
*/
/*
Hint 1: || A sorozat rendezett, ezért minden tippre alkalmazható a bináris keresés: keresd meg az első olyan elemet, amely nem kisebb a tippnél. ||
Hint 2: || A két szomszédos jelölt (a találat és az előtte álló elem) távolságát hasonlítsd össze a tippel. Egyenlőségnél a kisebb értéket írd ki, és a széleken csak az egyik jelölt van. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<long long> s(n);
    for (auto &x : s) cin >> x;

    for (int j = 0; j < m; j++) {
        long long t;
        cin >> t;
        auto it = lower_bound(s.begin(), s.end(), t);
        long long best;
        if (it == s.end()) {
            best = s.back();
        } else if (it == s.begin()) {
            best = *it;
        } else {
            long long right = *it;
            long long left = *prev(it);
            // Egyenlő távolságnál a kisebb érték (a bal oldali) nyer
            best = (t - left <= right - t) ? left : right;
        }
        cout << best << (j + 1 < m ? ' ' : '\n');
    }
    return 0;
}
