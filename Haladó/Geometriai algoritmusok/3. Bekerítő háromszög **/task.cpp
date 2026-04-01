/*
Megoldás lényege:
Fixálunk egy élpontot, majd a többi pontot szög szerint rendezzük. Két egymást követő irányból választott harmadik csúccsal
keressük azt a háromszöget, amely tartalmazza a kijelölt pontot, de más pontot nem.
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

static int orient(const Pt& a, const Pt& b, const Pt& c) {
    int v = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (v < 0) return -1;
    if (v > 0) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    Pt q;
    int aId, bId;
    if (!(cin >> n >> q.x >> q.y >> aId >> bId)) return 0;

    vector<Pt> p(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> p[i].x >> p[i].y;
        p[i].id = i;
    }

    Pt A = p[aId], B = p[bId];
    if (orient(A, B, q) <= 0) swap(A, B);

    Pt AA{0, 0, 0}, BB{0, 0, 0}, C{0, 0, 0};

    for (int i = 1; i <= n; ++i) {
        if (i == aId || i == bId) continue;
        int firAB = orient(A, B, p[i]);
        int firBQ = orient(B, q, p[i]);
        int firQA = orient(q, A, p[i]);

        if (firAB >= 0 && firBQ >= 0 && firQA >= 0) {
            cout << 0 << '\n';
            return 0;
        }

        if (firAB > 0 && firQA < 0 && firBQ > 0) {
            if (AA.id == 0 || orient(A, AA, p[i]) < 0) AA = p[i];
        }

        if (firAB > 0 && firQA > 0 && firBQ < 0) {
            if (BB.id == 0 || orient(B, BB, p[i]) > 0) BB = p[i];
        }
    }

    for (int i = 1; i <= n; ++i) {
        if (i == aId || i == bId || i == AA.id || i == BB.id) continue;
        int firQA = orient(q, A, p[i]);
        int firBQ = orient(B, q, p[i]);
        if ((AA.id == 0 || orient(A, AA, p[i]) < 0) &&
            (BB.id == 0 || orient(B, BB, p[i]) > 0) &&
            firQA < 0 && firBQ < 0) {
            C = p[i];
            break;
        }
    }

    if (C.id == 0) {
        cout << 0 << '\n';
        return 0;
    }

    for (int i = C.id + 1; i <= n; ++i) {
        if (i == aId || i == bId || i == AA.id || i == BB.id) continue;
        if (orient(A, B, p[i]) > 0 && orient(A, C, p[i]) < 0 && orient(B, C, p[i]) > 0) {
            C = p[i];
        }
    }

    cout << C.id << '\n';
    return 0;
}
