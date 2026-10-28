/*
Megoldás lényege:
Négy különböző pont akkor alkot konvex négyszöget, ha valamelyik párosításuk két szakasza belsőpontban metszi egymást; ha közülük három egy egyenesen van, nincs ilyen négyszög. Ha N <= 6, az összes négyes végignézése elég. Ha N >= 7 és nincs konvex négyszög, akkor van olyan egyenes, amely a pontok legalább N-2-jét tartalmazza; ezt az egyenest az első öt pont párjainak egyenesei közül keressük meg, párjanként O(N) ellenőrzéssel. Ha nincs ilyen egyenes, a válasz VAN. Ha az egyenesen kívül legfeljebb egy pont van, a válasz NINCS. Ha két külső pont (P, Q) van: azonos oldalon VAN; különböző oldalon pontosan akkor VAN, ha az egyenes pontjai között van a PQ egyenes két különböző oldalán is. A teljes megoldás O(T*N) időben fut.
*/
/*
Hint 1: || Négy pont akkor alkot konvex négyszöget, ha valamelyik párosításuk szakaszai belsőpontban metszik egymást. Ha közülük három egy egyenesen van, a négy pont nem alkot konvex négyszöget, ezeket a négyeseket tehát kihagyhatod. Kis N-re (N <= 6) az összes négyes végignézése elég. ||
Hint 2: || N >= 7 esetén, ha nincs konvex négyszög, a pontok szinte mind egy egyenesen vannak: keress olyan egyenest, amely legalább N-2 pontot tartalmaz. Ha ilyen egyenes nincs, a válasz VAN. Ha van, egyetlen egy lehet, és az első öt pont közül bármely két rajta lévő pont meghatározza. ||
Hint 3: || Ha az egyenesen kívül legfeljebb egy pont van, nincs konvex négyszög. Két külső pont P és Q esetén: ha azonos oldalon vannak, van konvex négyszög. Ha különböző oldalon, a PQ egyenes az egyenest egyetlen pontban metszi, és akkor van konvex négyszög, ha az egyenes pontjai a PQ két oldalán is megvannak. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Pt {
    ll x, y;
    bool operator<(const Pt& o) const { return x != o.x ? x < o.x : y < o.y; }
    bool operator==(const Pt& o) const { return x == o.x && y == o.y; }
};

// (b-a) x (c-a): pozitív, ha c az a->b iránytól balra van
ll cross(const Pt& a, const Pt& b, const Pt& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int sgn(ll v) { return (v > 0) - (v < 0); }

// Igaz, ha az ab és cd szakaszok belsőpontban metszik egymást
bool properCross(const Pt& a, const Pt& b, const Pt& c, const Pt& d) {
    return sgn(cross(a, b, c)) * sgn(cross(a, b, d)) < 0 &&
           sgn(cross(c, d, a)) * sgn(cross(c, d, b)) < 0;
}

// Négy különböző pont pontosan akkor konvex, ha valamelyik párosítás metszi egymást
bool convex4(const Pt& a, const Pt& b, const Pt& c, const Pt& d) {
    return properCross(a, b, c, d) || properCross(a, c, b, d) || properCross(a, d, b, c);
}

bool solveSmall(const vector<Pt>& p) {
    int n = p.size();
    for (int a = 0; a < n; a++)
        for (int b = a + 1; b < n; b++)
            for (int c = b + 1; c < n; c++)
                for (int d = c + 1; d < n; d++)
                    if (convex4(p[a], p[b], p[c], p[d])) return true;
    return false;
}

// A és B határozza meg az egyenest, amely legalább n-2 pontot tartalmaz
bool solveLine(const vector<Pt>& p, const Pt& A, const Pt& B) {
    vector<Pt> off;
    for (const Pt& q : p)
        if (cross(A, B, q) != 0) off.push_back(q);
    if (off.size() <= 1) return false;

    const Pt& P = off[0];
    const Pt& Q = off[1];
    if (sgn(cross(A, B, P)) == sgn(cross(A, B, Q))) return true;

    // Különböző oldalon: az egyenes pontjai között kell lennie a PQ két oldalán is
    bool pos = false, neg = false;
    for (const Pt& q : p) {
        if (cross(A, B, q) != 0) continue;
        ll c = cross(P, Q, q);
        if (c > 0) pos = true;
        if (c < 0) neg = true;
    }
    return pos && neg;
}

bool solve(vector<Pt> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    int n = p.size();
    if (n <= 6) return solveSmall(p);

    // Ha van N-2 pontot tartalmazó egyenes, az első öt pont közül legalább három rajta van,
    // így a párjaik egyike megadja az egyenest.
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++) {
            int cnt = 0;
            for (const Pt& q : p)
                if (cross(p[i], p[j], q) == 0) cnt++;
            if (cnt >= n - 2) return solveLine(p, p[i], p[j]);
        }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        int n;
        cin >> n;
        vector<Pt> p(n);
        for (Pt& q : p) cin >> q.x >> q.y;
        cout << (solve(p) ? "VAN" : "NINCS") << '\n';
    }
    return 0;
}
