/*
Megoldás lényege:
Az A-B egyenes azon oldalát vesszük, ahol a csemete (Q) van; ha kell, A és B felcserélésével ez a bal oldal.
Egy C fa akkor jó, ha Q a belsejében van az ABC háromszögnek, ami három előjeles területtel ellenőrizhető.
A többi fát két szöggel jellemezzük: alfa az A csúcsból, béta a B csúcsból mérve az AB szakasztól. Egy P fa pontosan akkor
esik az ABC háromszögbe (a határt is beleértve), ha alfa(P) <= alfa(C) és béta(P) <= béta(C). Így a "hány fa van a
háromszögben" kérdés 2D dominanciaszámlálás: a fákat alfa szerint növekvően dolgozzuk fel, és egy Fenwick-fában a
béta-rangokat tartjuk nyilván. A legkevesebb fát tartalmazó jó C közül a legkisebb sorszámút írjuk ki, ha nincs jó C, a 0-t.
Idő: O(N log N).
*/
/*
Hint 1: || Csak az AB egyenes csemetével azonos oldalán lévő fák számítanak; ha Q az AB egyenes másik oldalán van,
cseréld meg A-t és B-t. C jó, ha Q szigorúan belül van az ABC háromszögben: ezt három előjeles terület adja. ||
Hint 2: || Egy P fa akkor van az ABC háromszögben, ha A-ból nézve a P-hez tartozó szög nem nagyobb a C szögénél, és
B-ből nézve szintén nem nagyobb a C szögénél. Így a két szög alapján kétdimenziós "kisebb vagy egyenlő" feltételt kapsz. ||
Hint 3: || Rendezd a fákat az A-ból mért szög szerint, és közben a B-ből mért szög szerinti rangokat egy Fenwick-fában
tartsd nyilván. Minden jó C-nél a már beszúrt fák közül lekérdezed, hányan vannak a C béta-rangjáig, majd kivonod C-t magát. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
};

// > 0, ha c az a->b iránytól balra van; < 0, ha jobbra; 0, ha egy egyenesen van.
static long long orient(const Pt& a, const Pt& b, const Pt& c) {
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Pt A, B, Q;
    if (!(cin >> A.x >> A.y >> B.x >> B.y >> Q.x >> Q.y)) return 0;
    int n;
    cin >> n;
    vector<Pt> p(n + 1);
    for (int i = 1; i <= n; ++i) cin >> p[i].x >> p[i].y;

    // Q az AB egyenesen van: nincs olyan háromszög, amelynek belsejében lenne.
    if (orient(A, B, Q) == 0) {
        cout << 0 << '\n';
        return 0;
    }
    // Q legyen az AB bal oldalán.
    if (orient(A, B, Q) < 0) swap(A, B);

    // Csak az AB bal oldalán lévő fák lehetnek C-k vagy a háromszögben lévő fák.
    vector<int> S;
    for (int i = 1; i <= n; ++i) {
        if (orient(A, B, p[i]) > 0) S.push_back(i);
    }

    // Rendezés A-ból mért szög szerint (sweep), és B-ből mért szög szerint (rangok).
    vector<int> byA = S, byB = S;
    sort(byA.begin(), byA.end(), [&](int i, int j) { return orient(A, p[i], p[j]) > 0; });
    sort(byB.begin(), byB.end(), [&](int i, int j) { return orient(B, p[i], p[j]) < 0; });

    // Béta-rangok: azonos szöghöz azonos rang tartozik.
    vector<int> rankB(n + 1, 0);
    int m = 0;
    for (size_t k = 0; k < byB.size(); ++k) {
        if (k == 0 || orient(B, p[byB[k - 1]], p[byB[k]]) != 0) ++m;
        rankB[byB[k]] = m;
    }

    // Fenwick-fa: hány beszúrt fa van adott béta-rang alatt (vagy azzal egyenlő).
    vector<int> bit(m + 1, 0);
    auto add = [&](int i) {
        for (int k = rankB[i]; k <= m; k += k & -k) bit[k]++;
    };
    auto query = [&](int r) {
        int s = 0;
        for (int k = r; k > 0; k -= k & -k) s += bit[k];
        return s;
    };

    long long bestCnt = LLONG_MAX;
    int best = 0;
    size_t k = 0;
    while (k < byA.size()) {
        // Azonos alfájú fák egy csoportot alkotnak: előbb mindet beszúrjuk, utána lekérdezünk.
        size_t e = k;
        while (e < byA.size() && orient(A, p[byA[k]], p[byA[e]]) == 0) ++e;
        for (size_t t = k; t < e; ++t) add(byA[t]);
        for (size_t t = k; t < e; ++t) {
            int c = byA[t];
            // Q szigorúan belül: alfa(Q) < alfa(C) és béta(Q) < béta(C).
            if (orient(A, Q, p[c]) > 0 && orient(B, Q, p[c]) < 0) {
                long long cnt = query(rankB[c]) - 1;  // C maga is benne van a lekérdezésben
                if (cnt < bestCnt || (cnt == bestCnt && c < best)) {
                    bestCnt = cnt;
                    best = c;
                }
            }
        }
        k = e;
    }

    cout << best << '\n';
    return 0;
}
