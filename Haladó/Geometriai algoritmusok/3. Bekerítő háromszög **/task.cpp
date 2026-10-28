/*
Megoldás lényege:
Ha q az ab egyenesen van, vagy az ab szakasz belsejében pont található, nincs megoldás. Különben legyen q az a->b irány
bal oldalán (szükség esetén a és b cseréjével). Egy c pont pontosan akkor jó, ha q az (a,b,c) háromszög belsejében van,
és nincs más pont a zárt háromszögben. Minden, az ab egyenes q-val azonos oldalán lévő p pontot az a-ból mért szögével
(alfa) és a b-ből mért szögével (béta) jellemezhetünk; p pontosan akkor esik a zárt (a,b,c) háromszögbe, ha alfa_p <= alfa_c
és béta_p <= béta_c. Így a jó c csak olyan pont lehet, amelyet más pont nem előz meg mindkét szögben. Ezeket alfa szerint
rendezve a béta szigorúan csökken, így a jó pontok (alfájuk nagyobb q alfájánál, bétájuk nagyobb q bétájánál) összefüggő
szakaszt alkotnak; ezek közül a legkisebb sorszámút adjuk meg.
Idő: O(N log N).
*/
/*
Hint 1: || A c csúcsnak ugyanarra az oldalra kell esnie, mint q az ab egyenesen. q akkor belső pont, ha c a q pontból nézve az a és b irányával ellentétes tartományban van. ||
Hint 2: || Minden más pontot két szöggel jellemezz: az a-ból és a b-ből mért szöggel. Egy p pont pontosan akkor esik az (a,b,c) háromszögbe, ha mindkét szöge nem nagyobb c megfelelő szögénél. ||
Hint 3: || A minimális pontokat (amelyeket más pont nem előz meg mindkét szögben) az a-ból mért szög szerint rendezve a b-ből mért szög szigorúan csökken. A q-nál nagyobb a-ból mért szögű minimális pontok közül azok jók, amelyek b-ből mért szöge is nagyobb q-énál. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Pt {
    long long x, y;
    int id;
};

// Az a->b egyenes melyik oldalán van c: +1 bal, -1 jobb, 0 egy egyenesen.
static int orient(const Pt& a, const Pt& b, const Pt& c) {
    long long v = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
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
    int side = orient(A, B, q);
    if (side == 0) {
        cout << 0 << '\n';
        return 0;
    }
    if (side < 0) swap(A, B);

    vector<int> cand;
    for (int i = 1; i <= n; ++i) {
        if (i == aId || i == bId) continue;
        int s = orient(A, B, p[i]);
        if (s > 0) {
            cand.push_back(i);
        } else if (s == 0) {
            // Az ab szakaszon fekvő pont minden (a,b,c) háromszög oldalán van.
            if (min(A.x, B.x) <= p[i].x && p[i].x <= max(A.x, B.x) &&
                min(A.y, B.y) <= p[i].y && p[i].y <= max(A.y, B.y)) {
                cout << 0 << '\n';
                return 0;
            }
        }
    }

    // Alfa (a-bol mert szog) szerint rendezés, azonos alfánál béta szerint.
    sort(cand.begin(), cand.end(), [&](int i, int j) {
        int o = orient(A, p[i], p[j]);
        if (o != 0) return o > 0;
        return orient(B, p[i], p[j]) < 0;
    });

    // Minimális pontok: nincs más pont, amely alfában és bétában sem nagyobb.
    vector<int> minimal;
    int bestB = -1;
    for (int i : cand) {
        if (bestB == -1 || orient(B, p[i], p[bestB]) < 0) {
            minimal.push_back(i);
            bestB = i;
        }
    }

    // A jó pontok a minimális sorozat egy összefüggő szakasza: alfa > alfa_q és béta > béta_q.
    int best = -1;
    for (int i : minimal) {
        if (orient(A, q, p[i]) <= 0) continue;
        if (orient(B, q, p[i]) >= 0) break;
        if (best == -1 || p[i].id < p[best].id) best = i;
    }

    cout << (best == -1 ? 0 : p[best].id) << '\n';
    return 0;
}
