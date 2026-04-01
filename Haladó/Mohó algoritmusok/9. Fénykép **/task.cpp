/*
Feladat: A lehető legkevesebb fényképen kell minden vendéget legalább egyszer lefényképezni.
Ötlet: Sorba rendezzük a vendégeket a távozási idő szerint, és mindig az első be nem fedett vendég távozása előtti pillanatban készítünk egy képet. Ez a pont a lehető legtöbb további vendéget is lefedi.
Hint 1: || A legkorábban távozó még lefedetlen vendég határozza meg, mikor kell elkészülni az aktuális képpel. ||
Hint 2: || Ha az ő távozása előtti legutolsó időpontban fotózunk, akkor minden olyan vendég rajta lehet, aki ebben a pillanatban még jelen van. ||
Hint 3: || Ezután minden olyan vendéget kihagyhatsz, akit ez a fotó már lefed. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<tuple<int, int, int>> a;
    a.reserve(n);
    for (int i = 1; i <= n; ++i) {
        int e, t;
        cin >> e >> t;
        a.push_back({t, e, i});
    }
    sort(a.begin(), a.end());

    vector<int> times;
    int last = INT_MIN;
    for (auto [t, e, id] : a) {
        if (!(e <= last && last < t)) {
            last = t - 1;
            times.push_back(last);
        }
    }

    cout << times.size() << '\n';
    for (int i = 0; i < (int)times.size(); ++i) {
        if (i) cout << ' ';
        cout << times[i];
    }
    cout << '\n';
    return 0;
}