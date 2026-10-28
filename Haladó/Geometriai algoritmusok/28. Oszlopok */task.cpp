/*
Megoldás lényege:
Egy oszlop akkor takar egy másikat az origóból nézve, ha ugyanarra a félegyenesre esnek, és az
egyik közelebb van. Ezért minden irányból pontosan a legközelebbi oszlop látszik.
Az irányt a (x,y) vektor egyszerűsített alakja adja: (x/g, y/g), ahol g = gcd(x,y).
A látható oszlopok száma tehát a különböző egyszerűsített irányvektorok száma.

Idő: O(N log C)
*/
/*
Hint 1: || Két oszlop akkor takarja egymást az origóból nézve, ha ugyanabba az irányba esnek. Így az irányok számát kell megszámolni. ||
Hint 2: || Az irányt a koordináták legnagyobb közös osztójával elosztva egyszerűsítheted, így az azonos irányú pontok ugyanazt a párt adják. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    if (!(cin >> N)) return 0;

    set<pair<int, int>> dirs;
    for (int i = 0; i < N; ++i) {
        int x, y;
        cin >> x >> y;
        int g = std::gcd(x, y);
        dirs.insert({x / g, y / g});
    }

    cout << dirs.size() << '\n';
    return 0;
}
