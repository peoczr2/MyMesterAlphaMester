/*
A lapokat egy hexagonális rács topologikus modelljével írjuk le: a tizenkétszög a rács
csúcsa, a négyzet az él, a háromszög pedig a csúcs melletti háromszögszelet. Így minden
lépés egyetlen lokális állapotátmenet: csúcs -> él / háromszög, él -> két csúcs vagy két
háromszög, háromszög -> egy csúcs és két él. Az érintett négyzeteket és a többször
érintett lapokat halmazokkal számoljuk.
*/
/*
Hint 1: || A tizenkétszög, a négyzet és a háromszög külön állapotot jelent; a lépés mindig a jelenlegi alakból olvasható ki. ||
Hint 2: || A végső négyzet- és többszörérintés-számot egy látogatásszámláló térképpel egyszerűen megkapod. ||
*/

#include <bits/stdc++.h>
using namespace std;

struct State {
    int type; // 0 = face, 1 = edge, 2 = vertex
    int x, y;  // axial coordinate for face; edge/vertex are anchored to a face
    int d;     // orientation index, depends on type

    bool operator==(const State& other) const {
        return type == other.type && x == other.x && y == other.y && d == other.d;
    }
};

struct Hash {
    size_t operator()(const State& s) const noexcept {
        size_t h = s.type;
        h = h * 239017u + (unsigned)(s.x + 1000);
        h = h * 239017u + (unsigned)(s.y + 1000);
        h = h * 239017u + (unsigned)(s.d + 16);
        return h;
    }
};

static const int dx[6] = {1, 1, 0, -1, -1, 0};
static const int dy[6] = {0, -1, -1, 0, 1, 1};

static string key(const State& s) {
    return to_string(s.type) + ':' + to_string(s.x) + ':' + to_string(s.y) + ':' + to_string(s.d);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int kx, ky;
    if (!(cin >> kx >> ky)) return 0;

    unordered_map<string, int> cnt;
    cnt.reserve(1 << 16);

    auto addVisit = [&](const State& s) {
        cnt[key(s)]++;
    };

    State cur{0, kx, ky, 0};
    addVisit(cur);

    string cmd;
    while (cin >> cmd) {
        if (cur.type == 0) {
            int idx = -1;
            if (cmd == "E") idx = 0;
            else if (cmd == "EEK") idx = 1;
            else if (cmd == "KEK") idx = 2;
            else if (cmd == "K") idx = 3;
            else if (cmd == "KDK") idx = 4;
            else if (cmd == "DDK") idx = 5;
            else if (cmd == "D") idx = 6;
            else if (cmd == "DDN") idx = 7;
            else if (cmd == "NDN") idx = 8;
            else if (cmd == "N") idx = 9;
            else if (cmd == "NEN") idx = 10;
            else if (cmd == "EEN") idx = 11;
            else return 0;

            if (idx % 2 == 0) {
                int dir = idx / 2;
                cur = {1, cur.x, cur.y, dir};
            } else {
                int corner = idx / 2;
                cur = {2, cur.x, cur.y, corner};
            }
        } else if (cur.type == 1) {
            // él: d az orientáció, E/K két csúcs, D/N a két szomszédos háromszögszelet
            int dir = cur.d;
            int nx = cur.x + dx[dir];
            int ny = cur.y + dy[dir];
            int px = cur.x;
            int py = cur.y;
            int vx1 = cur.x, vy1 = cur.y;
            int vx2 = cur.x + dx[(dir + 5) % 6];
            int vy2 = cur.y + dy[(dir + 5) % 6];

            if (cmd == "E") {
                cur = {0, px, py, 0};
            } else if (cmd == "K") {
                cur = {0, nx, ny, 0};
            } else if (cmd == "D") {
                cur = {2, px, py, dir};
            } else if (cmd == "N") {
                cur = {2, nx, ny, (dir + 5) % 6};
            } else {
                return 0;
            }
        } else {
            // háromszög: E a csúcsra, K és D a két élre
            int dir = cur.d;
            if (cmd == "E") {
                cur = {0, cur.x, cur.y, 0};
            } else if (cmd == "K") {
                cur = {1, cur.x, cur.y, dir};
            } else if (cmd == "D") {
                cur = {1, cur.x, cur.y, (dir + 1) % 6};
            } else {
                return 0;
            }
        }
        addVisit(cur);
    }

    long long squares = 0;
    long long repeated = 0;
    for (const auto& [k, c] : cnt) {
        if (c >= 2) repeated++;
        if (!k.empty() && k[0] == '1') squares++;
    }

    cout << squares << '\n';
    cout << cur.x << ' ' << cur.y << '\n';
    cout << repeated << '\n';
    return 0;
}
