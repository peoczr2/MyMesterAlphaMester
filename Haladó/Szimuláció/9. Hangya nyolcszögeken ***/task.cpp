/*
Az állapot a mező típusából (nyolcszög vagy négyzet) és a koordinátákból áll. A négyzetet a bal alsó csúcsában álló nyolcszög koordinátáival azonosítjuk, így az átlós lépések egyszerű koordinátaváltozást jelentenek. Az utat lépésenként szimuláljuk: a négyzetekre érkezéseket egy halmazba gyűjtjük, így a különböző érintett négyzetek száma a halmaz mérete lesz. A mezők látogatásait egy map-ben számoljuk (a kezdőpozíciót is beleértve), és a legalább kétszer érintett mezőket összeszámoljuk. A lépések száma L, egy lépés O(log L) map-műveletet igényel, így az összes idő O(L log L).
*/
/*
Hint 1: || A nyolcszögek és a négyzetek külön mezőtípusok: az állapotot (típus, x, y) hármasként tárold, és a lépés szabálya a típustól függ. ||
Hint 2: || Egy négyzetet a bal alsó sarkában álló nyolcszög koordinátáival azonosíthatsz, így az átlós lépések egyszerű koordinátaváltozást adnak. ||
Hint 3: || A különböző négyzetek számához ne az érkezéseket számold, hanem egy halmazban tárold a már érintett négyzeteket. ||
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int kx, ky;
    cin >> kx >> ky;

    State cur{0, kx, ky};
    map<State, int> cnt;
    cnt[cur] = 1;

    set<pair<int, int>> squares;

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
            squares.insert({cur.x, cur.y});
        }
        ++cnt[cur];
    }

    long long repeated = 0;
    for (const auto& [state, value] : cnt) {
        if (value >= 2) ++repeated;
    }

    cout << squares.size() << '\n';
    cout << cur.x << ' ' << cur.y << '\n';
    cout << repeated << '\n';
    return 0;
}