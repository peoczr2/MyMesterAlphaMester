/*
Megoldás lényege:
Egy oszlop akkor takar egy másikat az origóból nézve, ha ugyanarra a félegyenesre esnek, és az
egyik közelebb van. Ezért minden irányból pontosan a legközelebbi oszlop látszik.
Az irányt a (x,y) vektor egyszerűsített alakja adja: (x/g, y/g), ahol g = gcd(x,y).
A látható oszlopok száma tehát a különböző egyszerűsített irányvektorok száma.

Idő: O(N log C)
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
