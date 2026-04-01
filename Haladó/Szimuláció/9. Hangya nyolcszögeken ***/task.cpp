/*
Az állapotot a mező típusa és a koordinátái adják meg. Az oktagonok az egész rácspontokon
helyezkednek el, a négyzetek pedig a köztük levő egységnégyzetek. Oktagonból a négy
kardinális irány oktagonba vezet, a négy átlós irány pedig a megfelelő négyzetbe.
Négyzetből csak az átlós irányok használhatók, ezek a négy sarkon álló oktagonokba visznek.
Így egyszerű szimulációval követhető az út, közben számlálva a négyzetre érkezéseket és azt is,
hogy hány különböző mezőt érintett a hangya legalább kétszer.
*/
/*
Hint 1: || A mező típusa a lépés szabályát is meghatározza, ezért a négyzetet és a nyolcszöget külön kezeld. ||
Hint 2: || A többször érintett mezők száma egy egyszerű látogatásszámlálással megkapható. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct State {
    int type; // 0 = octagon, 1 = square
    int x, y;

    bool operator<(const State& other) const {
        if (type != other.type) return type < other.type;
        if (x != other.x) return x < other.x;
        return y < other.y;
    }
};

static bool isDiagonal(const string& d) {
    return d.size() == 2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int kx, ky;
    cin >> kx >> ky;

    State cur{0, kx, ky};
    map<State, int> cnt;
    cnt[cur] = 1;

    long long squareVisits = 0;

    string dir;
    while (cin >> dir) {
        if (cur.type == 0) {
            if (dir == "E") {
                ++cur.y;
            } else if (dir == "K") {
                ++cur.x;
            } else if (dir == "D") {
                --cur.y;
            } else if (dir == "N") {
                --cur.x;
            } else if (dir == "EK") {
                cur.type = 1;
            } else if (dir == "DK") {
                cur.type = 1;
                --cur.y;
            } else if (dir == "DN") {
                cur.type = 1;
                --cur.x;
                --cur.y;
            } else if (dir == "EN") {
                cur.type = 1;
                --cur.x;
            }
        } else {
            if (dir == "EK") {
                cur.type = 0;
                ++cur.x;
                ++cur.y;
            } else if (dir == "DK") {
                cur.type = 0;
                ++cur.x;
            } else if (dir == "DN") {
                cur.type = 0;
            } else if (dir == "EN") {
                cur.type = 0;
                ++cur.y;
            }
        }

        if (cur.type == 1) {
            ++squareVisits;
        }
        ++cnt[cur];
    }

    long long repeated = 0;
    for (const auto& [state, value] : cnt) {
        if (value >= 2) ++repeated;
    }

    cout << squareVisits << '\n';
    cout << cur.x << ' ' << cur.y << '\n';
    cout << repeated << '\n';
    return 0;
}