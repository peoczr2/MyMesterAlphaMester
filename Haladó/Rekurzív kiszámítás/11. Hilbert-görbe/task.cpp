/*
Megoldás lényege:
Minden ponthoz kiszámítjuk a Hilbert-görbe indexét a szokásos kvadránsos rekurzió
alapján, majd ezek szerint rendezzük a pontokat. A feladatban megadott első rendű görbe
pontsorrendje pontosan a standard Hilbert-orientáció.

*/

// Hint 1: || Minden szintben csak azt kell eldönteni, melyik negyedbe esik a pont. ||
// Hint 2: || A Hilbert-indexet bitenként, felülről lefelé is fel lehet építeni. ||
// Hint 3: || A végén egyszerűen index szerint rendezd a pontokat. ||

#include <bits/stdc++.h>
using namespace std;

static void rot(unsigned int n, unsigned int& x, unsigned int& y, unsigned int rx, unsigned int ry) {
    if (ry == 0) {
        if (rx == 1) {
            x = n - 1 - x;
            y = n - 1 - y;
        }
        swap(x, y);
    }
}

static unsigned long long hilbertIndex(int order, unsigned int x, unsigned int y) {
    unsigned long long d = 0;
    for (unsigned int s = 1u << (order - 1); s > 0; s >>= 1) {
        unsigned int rx = (x & s) ? 1u : 0u;
        unsigned int ry = (y & s) ? 1u : 0u;
        d += 1ULL * s * s * ((3u * rx) ^ ry);
        rot(s, x, y, rx, ry);
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    struct P { unsigned long long d; int x, y; };
    vector<P> pts(M);
    for (int i = 0; i < M; ++i) {
        cin >> pts[i].x >> pts[i].y;
        pts[i].d = hilbertIndex(N, (unsigned int)pts[i].x, (unsigned int)pts[i].y);
    }

    sort(pts.begin(), pts.end(), [](const P& a, const P& b) {
        if (a.d != b.d) return a.d < b.d;
        if (a.x != b.x) return a.x < b.x;
        return a.y < b.y;
    });

    for (const auto& p : pts) cout << p.x << ' ' << p.y << '\n';
    return 0;
}
