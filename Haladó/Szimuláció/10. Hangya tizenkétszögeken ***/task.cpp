/*
Megoldás lényege: a tizenkétszögek egy négyzetrácsot alkotnak, a rácscellák közepén egy négyzet van, amelyet négy háromszög vesz körül. A hangya lépései így a jelenlegi lap típusától és helyzetétől függő átmenetek: tizenkétszögből 30 fokonként 12 irányba lehet menni, háromszögből és négyzetből a kilépési irány a lap helyzetéből adódik. A bejárás során minden érintett lap látogatásszámát hash-táblában tartjuk, így az érintett különböző négyzetek száma és a legalább kétszer érintett lapok száma egy bejárással megkapható. Egy lépés állandó idejű, a teljes út ideje a lépések számával arányos.
*/
/*
Hint 1: || A tizenkétszögek rácsot alkotnak; a cellák közepén lévő négyzetet és a körülötte levő négy háromszöget külön lapként kell azonosítani, például a cella bal alsó csúcsával és egy oldalazonosítóval. ||
Hint 2: || Az irányokat 30 fokos egységekben kódold (K=0, KEK=1, …, KDK=11): a tizenkétszögből a 0, 3, 6, 9 irány közvetlenül szomszédos tizenkétszögbe vezet, a többi háromszögbe, és a háromszög kilépési irányait a helyzete határozza meg. ||
Hint 3: || Minden lépés után a lap azonosítóját növeld egy hash-táblában, a négyzeteknél pedig csak az első látogatáskor növeld a különböző négyzetek számát. ||
*/

#include <bits/stdc++.h>
using namespace std;

// Lap: t = 0 tizenkétszög (x, y), t = 1 négyzet (x, y a cella bal alsó csúcsa),
// t = 2 háromszög (x, y a cella bal alsó csúcsa, s az oldal: 0 alsó, 1 jobb, 2 felső, 3 bal).
struct Tile {
    int t;
    int s;
    long long x;
    long long y;
};

static const char *dirNames[12] = {"K", "KEK", "EEK", "E", "EEN", "NEN", "N", "NDN", "DDN", "D", "DDK", "KDK"};

static Tile moveFrom(const Tile &c, int a) {
    if (c.t == 0) {
        long long x = c.x, y = c.y;
        switch (a) {
            case 0: return {0, 0, x + 1, y};
            case 3: return {0, 0, x, y + 1};
            case 6: return {0, 0, x - 1, y};
            case 9: return {0, 0, x, y - 1};
            case 1: return {2, 0, x, y};
            case 2: return {2, 3, x, y};
            case 4: return {2, 1, x - 1, y};
            case 5: return {2, 0, x - 1, y};
            case 7: return {2, 2, x - 1, y - 1};
            case 8: return {2, 1, x - 1, y - 1};
            case 10: return {2, 3, x, y - 1};
            case 11: return {2, 2, x, y - 1};
        }
    } else if (c.t == 2) {
        long long hx = c.x, hy = c.y;
        if (c.s == 0) {
            if (a == 3) return {1, 0, hx, hy};
            if (a == 7) return {0, 0, hx, hy};
            if (a == 11) return {0, 0, hx + 1, hy};
        } else if (c.s == 2) {
            if (a == 9) return {1, 0, hx, hy};
            if (a == 5) return {0, 0, hx, hy + 1};
            if (a == 1) return {0, 0, hx + 1, hy + 1};
        } else if (c.s == 1) {
            if (a == 6) return {1, 0, hx, hy};
            if (a == 10) return {0, 0, hx + 1, hy};
            if (a == 2) return {0, 0, hx + 1, hy + 1};
        } else {
            if (a == 0) return {1, 0, hx, hy};
            if (a == 8) return {0, 0, hx, hy};
            if (a == 4) return {0, 0, hx, hy + 1};
        }
    } else {
        switch (a) {
            case 3: return {2, 2, c.x, c.y};
            case 0: return {2, 1, c.x, c.y};
            case 9: return {2, 0, c.x, c.y};
            case 6: return {2, 3, c.x, c.y};
        }
    }
    return c;
}

static long long keyOf(const Tile &c) {
    const long long OFF = 1LL << 20;
    const long long M = 1LL << 21;
    return ((c.t * 4 + c.s) * M + (c.x + OFF)) * M + (c.y + OFF);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long kx, ky;
    if (!(cin >> kx >> ky)) return 0;

    unordered_map<string, int> dirIdx;
    for (int i = 0; i < 12; ++i) dirIdx[dirNames[i]] = i;

    unordered_map<long long, int> visits;
    visits.reserve(1 << 16);
    int squares = 0;

    auto visit = [&](const Tile &c) {
        int &v = visits[keyOf(c)];
        if (v == 0 && c.t == 1) ++squares;
        ++v;
    };

    Tile cur{0, 0, kx, ky};
    visit(cur);

    string cmd;
    while (cin >> cmd) {
        auto it = dirIdx.find(cmd);
        if (it == dirIdx.end()) break;
        cur = moveFrom(cur, it->second);
        visit(cur);
    }

    long long repeated = 0;
    for (const auto &p : visits) {
        if (p.second >= 2) ++repeated;
    }

    cout << squares << '\n';
    cout << cur.x << ' ' << cur.y << '\n';
    cout << repeated << '\n';
    return 0;
}
