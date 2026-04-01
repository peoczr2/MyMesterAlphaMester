/*
Megoldás lényege:
Olyan háromszöget kell választani, amelyben a kijelölt pont belül van, és amelynek belsejében nincs más pont. A megoldás a pontok rendezésére és a lehetséges harmadik csúcsok vizsgálatára épül.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static int orient(const Pt& a, const Pt& b, const Pt& c) {
    __int128 v = (__int128)(b.x - a.x) * (c.y - a.y) - (__int128)(b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Pt A, B, Q;
    int n;
    if (!(cin >> A.x >> A.y >> B.x >> B.y >> Q.x >> Q.y)) return 0;
    cin >> n;

    vector<Pt> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i;
    }

    if (orient(A, B, Q) <= 0) swap(A, B);

    Pt AA{0, 0, 0}, BB{0, 0, 0}, C{0, 0, 0};

    for (int i = 1; i <= n; ++i) {
        int firAB = orient(A, B, p[i]);
        int firBQ = orient(B, Q, p[i]);
        int firQA = orient(Q, A, p[i]);

        if (firAB > 0 && firQA < 0 && firBQ > 0) {
            if (AA.id == 0 || orient(A, AA, p[i]) < 0) AA = p[i];
        }

        if (firAB > 0 && firQA > 0 && firBQ < 0) {
            if (BB.id == 0 || orient(B, BB, p[i]) > 0) BB = p[i];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (p[i].id == AA.id || p[i].id == BB.id) continue;
        if ((AA.id == 0 || orient(A, AA, p[i]) < 0) &&
            (BB.id == 0 || orient(B, BB, p[i]) > 0) &&
            orient(Q, A, p[i]) < 0 &&
            orient(B, Q, p[i]) < 0) {
            C = p[i];
            break;
        }
    }

    if (C.id == 0) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = C.id + 1; i <= n; ++i) {
        if (p[i].id == AA.id || p[i].id == BB.id) continue;
        if (orient(A, B, p[i]) > 0 && orient(A, C, p[i]) < 0 && orient(B, C, p[i]) > 0) {
            C = p[i];
        }
    }

    cout << C.id << '\n';
    return 0;
}
