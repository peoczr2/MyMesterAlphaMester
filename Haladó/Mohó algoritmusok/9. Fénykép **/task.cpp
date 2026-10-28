/*
Megoldás lényege:
A fénykép egy x időpontban az E <= x < T intervallumba eső vendégeket fedi le, így a feladat intervallumok lefogása egy legkisebb ponthalmazzal. A vendégeket távozási idejük (T) szerint növekvően rendezzük, és az első még lefedetlen vendég távozása előtti utolsó pillanatban (T-1) készítünk képet. Ez a pont a legkorábban záruló intervallum legkésőbbi lehetséges pontja, így a legtöbb további vendéget fedi le, a mohó választás tehát optimális. Az időigény O(N log N).
*/
/*
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