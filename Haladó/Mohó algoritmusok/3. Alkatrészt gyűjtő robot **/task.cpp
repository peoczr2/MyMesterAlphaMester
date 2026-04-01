/*
Feladat: A robotoknak a rácson lévő 1-es mezőket a lehető legkevesebb, jobbra és lefelé haladó útvonalon kell begyűjteniük.
Ötlet: A mezőket sorok szerint növekvő sorrendbe vesszük, és a második koordinátára bontjuk a sorozatot a lehető legkevesebb nemcsökkenő láncra. Ez adja a minimális robotok számát.
Hint 1: || Egy robot útja mentén a sor- és oszlopszám is csak növekedhet. ||
Hint 2: || Ha a rácspontokat soronként, azon belül oszlopsorrendben nézed, akkor egy robot egy nemcsökkenő oszlopsorozatot ad. ||
Hint 3: || A válasz a lehető legkevesebb ilyen sorozat száma. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    vector<pair<int, int>> pts;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int x;
            cin >> x;
            if (x == 1) pts.push_back({i, j});
        }
    }

    sort(pts.begin(), pts.end());
    multiset<int> tails;
    for (auto [r, c] : pts) {
        auto it = tails.upper_bound(c);
        if (it == tails.begin()) {
            tails.insert(c);
        } else {
            --it;
            tails.erase(it);
            tails.insert(c);
        }
    }

    cout << tails.size() << '\n';
    return 0;
}