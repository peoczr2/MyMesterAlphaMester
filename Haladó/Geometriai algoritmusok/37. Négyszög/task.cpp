/*
Megoldás lényege:
Négy pont akkor alkot konvex négyszöget, ha közülük nincs három egy egyenesen, és egyik sem esik a másik három háromszögébe.
Ha N ≤ 6, minden 4 pontos részhalmazt megnézünk. Ha N ≥ 7 és nincs konvex négyszög, akkor a pontok szinte mind egy
egyenesen vannak: van olyan egyenes, amelyen legalább N−2 pont fekszik. Ezt az állítást kimerítő kereséssel kis esetekre
ellenőriztük, általános bizonyítása itt nincs. Ha ilyen egyenes létezik, az első 5 pont közül legalább 3 rajta van, így
van közöttük két pont, amelyek egyenese épp ez az egyenes: elég 10 egyenest megnézni. Ha az egyenesen kívül legfeljebb
1 pont van, nincs konvex négyszög; ha pontosan 2 pont (X, Y) van kívül, előjel- és arányvizsgálattal döntünk.
Idő: O(N log N) a rendezés miatt, a vizsgálat O(N).
*/
/*
Hint 1: || Ha N ≥ 7 és nincs konvex négyszög, akkor a pontok szinte mind egy egyenesen vannak. Ezt az egyenest kell megtalálni, nem kell minden négyest kipróbálni. ||
Hint 2: || Ha az egyenesen kívül pontosan két pont (X és Y) van, akkor a négyszög csúcsai az egyenesen lévő P, Q pontok és X, Y. Nézd meg, hol metszi az XY egyenes az egyenest (Z), és hogy X, Y ugyanazon vagy ellentétes oldalán van-e. ||
Hint 3: || Ellentétes oldalon akkor lesz konvex, ha Z a P és Q közé esik. Azonos oldalon akkor, ha Z nincs a P és Q közötti szakaszon. Ha XY párhuzamos az egyenessel, mindig van ilyen pár. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

struct Pt {
    ll x, y;
    bool operator<(const Pt& o) const {
        if (x != o.x) return x < o.x;
        return y < o.y;
    }
    bool operator==(const Pt& o) const { return x == o.x && y == o.y; }
};

// a, b, c iránya: 1 ha balra fordul, -1 ha jobbra, 0 ha egy egyenesen vannak
static int orient(const Pt& a, const Pt& b, const Pt& c) {
    lll v = (lll)(b.x - a.x) * (c.y - a.y) - (lll)(b.y - a.y) * (c.x - a.x);
    return (v > 0) - (v < 0);
}

// igaz, ha a négy pont szigorúan konvex négyszöget alkot
static bool konvexNegyszog(const Pt q[4]) {
    for (int i = 0; i < 4; i++)
        for (int j = i + 1; j < 4; j++)
            for (int k = j + 1; k < 4; k++)
                if (orient(q[i], q[j], q[k]) == 0) return false;
    for (int p = 0; p < 4; p++) {
        Pt t[3];
        int m = 0;
        for (int r = 0; r < 4; r++)
            if (r != p) t[m++] = q[r];
        int s1 = orient(t[0], t[1], q[p]);
        int s2 = orient(t[1], t[2], q[p]);
        int s3 = orient(t[2], t[0], q[p]);
        if (s1 == s2 && s2 == s3) return false;  // q[p] a másik három háromszögében van
    }
    return true;
}

// p, q: az egyenes két pontja; X, Y: az egyenesen kívüli két pont;
// tv: az egyenesen lévő pontok paraméterei (t = (P-p)·(q-p)).
// Igaz, ha van az egyenesen két olyan pont, amellyel konvex négyszög lesz.
static bool vanKonvexKet(const Pt& p, const Pt& q, const Pt& X, const Pt& Y, const vector<ll>& tv) {
    ll dx = q.x - p.x, dy = q.y - p.y;
    auto side = [&](const Pt& P) { return dx * (P.y - p.y) - dy * (P.x - p.x); };
    auto pos = [&](const Pt& P) { return dx * (P.x - p.x) + dy * (P.y - p.y); };
    ll sX = side(X), sY = side(Y);  // nem nulla, mert X, Y kívül van
    if (sX == sY) return tv.size() >= 2;  // XY párhuzamos az egyenessel
    // Z = XY metszéspontja az egyenessel, paraméterben num / den
    lll den = (lll)sX - sY;
    lll num = (lll)sX * pos(Y) - (lll)sY * pos(X);
    if (den < 0) { den = -den; num = -num; }
    int less = 0, greater = 0;
    for (ll t : tv) {
        lll v = (lll)t * den - num;
        if (v < 0) less++;
        else if (v > 0) greater++;
    }
    bool ellentetes = (sX > 0) != (sY > 0);
    if (ellentetes) return less >= 1 && greater >= 1;
    return less >= 2 || greater >= 2;
}

static bool van(const vector<Pt>& S) {
    int M = S.size();
    if (M < 4) return false;
    if (M <= 6) {
        for (int a = 0; a < M; a++)
            for (int b = a + 1; b < M; b++)
                for (int c = b + 1; c < M; c++)
                    for (int d = c + 1; d < M; d++) {
                        Pt q[4] = {S[a], S[b], S[c], S[d]};
                        if (konvexNegyszog(q)) return true;
                    }
        return false;
    }
    // M >= 7: az első 5 pont közül két ponttal kijelölt egyenesek
    for (int i = 0; i < 5; i++)
        for (int j = i + 1; j < 5; j++) {
            const Pt& p = S[i];
            const Pt& q = S[j];
            ll dx = q.x - p.x, dy = q.y - p.y;
            vector<Pt> kint;
            vector<ll> tv;
            for (const Pt& P : S) {
                ll s = dx * (P.y - p.y) - dy * (P.x - p.x);
                if (s == 0) tv.push_back(dx * (P.x - p.x) + dy * (P.y - p.y));
                else kint.push_back(P);
            }
            if (kint.size() <= 1) return false;  // minden 4-es részhalmazban legalább 3 pont egy egyenesen van
            if (kint.size() == 2) return vanKonvexKet(p, q, kint[0], kint[1], tv);
        }
    return true;  // nincs ilyen egyenes: a pontok általános helyzetűek, van konvex négyszög
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    while (T--) {
        int N;
        cin >> N;
        vector<Pt> p(N);
        for (int i = 0; i < N; i++) cin >> p[i].x >> p[i].y;
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        cout << (van(p) ? "VAN" : "NINCS") << "\n";
    }
    return 0;
}
