/*
Megoldás lényege:
Egy futár adott nap egyik irányban, másnap visszafelé halad ugyanabban az időintervallumban,
tehát egy adott napon minden futár egyszerre vagy az eredeti (s->e), vagy a fordított (e->s)
irányában mozog.
Két futár akkor találkozhat, ha az átfedő időintervallumban metszik egymást aznapi pályáik:
ezt két esetben kell ellenőrizni: (s->e, s->e) és (e->s, e->s). Mivel a különbség lineáris,
elég az átfedés két végpontját vizsgálni: ha eltérő előjelűek (vagy valamelyik 0), akkor van találkozás.

Idő: O(M^2), M<=2000 esetén megfelelő.
*/

#include <bits/stdc++.h>
using namespace std;

struct Courier {
    long double s, e;
    long double t1, t2;
};

static long double positionAt(const Courier& c, long double t) {
    if (fabsl(c.t2 - c.t1) < 1e-18L) return c.s;
    long double ratio = (t - c.t1) / (c.t2 - c.t1);
    return c.s + (c.e - c.s) * ratio;
}

static bool canMeetOneDirection(const Courier& a, bool aForward, const Courier& b, bool bForward) {
    const long double EPS = 1e-12L;
    long double L = max(a.t1, b.t1);
    long double R = min(a.t2, b.t2);
    if (L > R + EPS) return false;

    Courier aa = a, bb = b;
    if (!aForward) swap(aa.s, aa.e);
    if (!bForward) swap(bb.s, bb.e);

    long double dL = positionAt(aa, L) - positionAt(bb, L);
    long double dR = positionAt(aa, R) - positionAt(bb, R);
    if (fabsl(dL) <= EPS || fabsl(dR) <= EPS) return true;
    return (dL < 0 && dR > 0) || (dL > 0 && dR < 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    vector<Courier> c(M + 1);
    for (int i = 1; i <= M; ++i) {
        cin >> c[i].s >> c[i].e >> c[i].t1 >> c[i].t2;
    }

    vector<pair<int, int>> ans;

    for (int i = 1; i <= M; ++i) {
        for (int j = i + 1; j <= M; ++j) {
            bool meet =
                canMeetOneDirection(c[i], true,  c[j], true)  ||
                canMeetOneDirection(c[i], false, c[j], false);

            if (meet) ans.push_back({i, j});
        }
    }

    cout << ans.size() << '\n';
    for (auto [a, b] : ans) {
        cout << a << ' ' << b << '\n';
    }

    return 0;
}
