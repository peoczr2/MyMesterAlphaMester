/*
Feladat: A jelzőlámpákat a pályán a lehető legkevesebb robotnak kell elhelyeznie úgy, hogy minden robot csak jobbra vagy lefelé léphessen.
Ötlet: A pontokat sor szerint, azon belül oszlop szerint rendezzük, és a lehető legkevesebb nemcsökkenő oszlopsorozatra bontjuk őket. Minden robot egy ilyen lánc.
Hint 1: || Egy robot útja mentén mind a sor-, mind az oszlopszám csak nőhet. ||
Hint 2: || A sor szerinti rendezés után csak az oszlopokra kell figyelni. ||
Hint 3: || Mindig a legnagyobb még nem nagyobb végű láncba tedd az aktuális lámpát. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct Point { int r, c; };

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<Point> p(k);
    for (int i = 0; i < k; ++i) cin >> p[i].r >> p[i].c;
    sort(p.begin(), p.end(), [](const Point &a, const Point &b) {
        if (a.r != b.r) return a.r < b.r;
        return a.c < b.c;
    });

    multiset<pair<int,int>> tails;
    int cnt = 0;
    for (auto &pt : p) {
        auto it = tails.upper_bound({pt.c, INT_MAX});
        if (it == tails.begin()) {
            tails.insert({pt.c, ++cnt});
        } else {
            --it;
            int id = it->second;
            tails.erase(it);
            tails.insert({pt.c, id});
        }
    }

    cout << tails.size() << '\n';
    return 0;
}