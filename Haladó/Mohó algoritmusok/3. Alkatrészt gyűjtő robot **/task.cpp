/*
Megoldás lényege: A robotok minimális száma a Dilworth-tétel szerint a legnagyobb antilánc mérete, a számítást mégis mohó láncfedéssel végezzük. Az 1-es mezőket sor, majd oszlop szerint rendezzük; egy robot útja olyan sorozat, amelyben az oszlopszám nemcsökkenő. Minden mezőt a legnagyobb olyan lánc végére teszünk, amelynek utolsó oszlopa nem nagyobb nála, különben új robot indul. Ez a legkevesebb láncot adja, az időigény O(P log P), ahol P az 1-es mezők száma (legfeljebb 10 000).
*/
/*
Hint 1: || Egy robot útja mentén a sor- és oszlopszám is csak növekedhet. ||
Hint 2: || Ha a rácspontokat soronként, azon belül oszlopsorrendben nézed, akkor egy robot egy nemcsökkenő oszlopsorozatot ad. ||
Hint 3: || Mohón haladva egy mezőt ahhoz a már kezdett sorozathoz csatolj, amelynek utolsó oszlopa a legnagyobb, de még nem nagyobb a mező oszlopánál; ha nincs ilyen, nyiss új sorozatot. ||
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