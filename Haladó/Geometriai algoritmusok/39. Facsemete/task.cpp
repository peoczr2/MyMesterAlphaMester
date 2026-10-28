/*
Megoldás lényege:
Az A fából az AP félegyenest nézzük: a keresett háromszög B csúcsa az egyik, C csúcsa a másik oldalán áll, és a BC szakasz P mögött metszi az AP félegyenest. A-ból nézve minden sugáron csak a legközelebbi fa számít, mert a távolabbi csak akkor kerülhetne a háromszögbe, ha a közelebbi is bekerülne. Ha az AP-n az A és P között (vagy P-ben) áll fa, nincs megoldás; ha P mögött áll fa (q), akkor a BC-nek q előtt kell metszenie az AP-t, különben q a háromszögbe kerülne. A jobb oldali fákat (r) és a bal oldali fákat (l) is az AP-hez mért szög szerint rendezzük. Az (r, l) pár jó, ha az rl szakasz q előtt metszi az AP-t (q nélkül minden pár jó). A szög szerinti sorrendben minimális jó párok háromszöge üres, mert egy benne levő fa egy nála előbbi jó párt adna; ha van megoldás, akkor van olyan minimális jó pár is, amelynél P szigorúan belül van. Minden r-hez a legkisebb sorszámú megfelelő l-t a bal fák q körüli szög szerinti rendezésének szuffix-minimumával és bináris kereséssel találjuk meg, majd a szigorúan javuló sorszámú párok közül az első, amelynél P szigorúan belül van, a megoldás (különben 0 0). Idő: O(N log N).
*/
/*
Hint 1: || A háromszögben az A-ból induló AP félegyenes belül halad, ezért B és C az AP egyenes két oldalán áll, és P pontosan akkor van szigorúan a háromszögben, ha a BC szakasz az AP félegyenest P mögött metszi. Ha az AP-n P mögött nincs fa, akkor a két, szögben legközelebbi fa (A-ból nézve, az AP mindkét oldalán) a jó választás, ha egyáltalán van megoldás. ||
Hint 2: || Ha az AP-n P mögött áll egy q fa, akkor a BC-nek q előtt kell metszenie az AP-t, ezért nem mindig a szomszédos fák a jók, szélesebb háromszög is kellhet. Minden sugáron csak az A-hoz legközelebbi fa számít. Az (r, l) párok közül azok jók, amelyekre az rl szakasz q előtt metszi az AP-t, a keresett háromszög pedig a szög szerinti sorrendben minimális jó párok egyike. ||
Hint 3: || A jobb oldali fákat az AP-hez közelebbitől haladva dolgozd fel, a bal oldaliakat pedig rendezd a q körüli szög szerint is. Egy r-hez tartozó jó bal fák ebben a rendezésben egy szuffixot alkotnak (bináris kereséssel találod meg), az A körüli sorrendben a legkisebb sorszámú közülük a keresett l, de az (A, r, l) szöge 180 foknál kisebb kell legyen. Csak az a pár érdekes, amelynél l sorszáma szigorúan kisebb az eddigi minimumnál, és ott kell ellenőrizni, hogy P szigorúan belül van-e. ||
*/
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Pt { ll x, y; };

static ll cross(const Pt& o, const Pt& a, const Pt& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
static ll crossv(ll ax, ll ay, ll bx, ll by) { return ax * by - ay * bx; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, a;
    cin >> n >> a;
    a--;
    Pt p;
    cin >> p.x >> p.y;
    vector<Pt> t(n);
    for (auto& q : t) cin >> q.x >> q.y;

    const Pt A = t[a];
    ll ux = p.x - A.x, uy = p.y - A.y;  // az A -> P irány
    ll uu = ux * ux + uy * uy;
    if (uu == 0) { cout << "0 0\n"; return 0; }

    // Az AP egyenesen álló fák: az A és P közötti (vagy a P-ben álló) fa mindig a háromszögbe
    // kerülne, a P mögötti legközelebbi fa (q) viszont csak kívül maradhat.
    // A többi fa az AP egyenes bal (c > 0) vagy jobb (c < 0) oldalán van.
    int q = -1;
    ll qd = 0;
    vector<int> left, right;
    for (int i = 0; i < n; i++) {
        if (i == a) continue;
        ll vx = t[i].x - A.x, vy = t[i].y - A.y;
        ll c = crossv(ux, uy, vx, vy);
        if (c > 0) left.push_back(i);
        else if (c < 0) right.push_back(i);
        else {
            ll d = ux * vx + uy * vy;  // az AP-re vetített hossz (|AP|^2 egységben)
            if (d <= 0) continue;      // A mögött áll: nem számít
            if (d <= uu) { cout << "0 0\n"; return 0; }
            if (q < 0 || d < qd) { q = i; qd = d; }
        }
    }

    // A-ból nézve minden sugáron csak a legközelebbi fa számít (a távolabbiak nem kerülhetnek
    // a háromszögbe, ha a közelebbi nem), a sorrend az AP-hez mért szög szerinti.
    auto reduce = [&](vector<int>& v, bool leftSide) {
        auto sq = [&](int i) {
            return (t[i].x - A.x) * (t[i].x - A.x) + (t[i].y - A.y) * (t[i].y - A.y);
        };
        sort(v.begin(), v.end(), [&](int i, int j) {
            ll c = crossv(t[i].x - A.x, t[i].y - A.y, t[j].x - A.x, t[j].y - A.y);
            if (c != 0) return leftSide ? c > 0 : c < 0;
            return sq(i) < sq(j);
        });
        vector<int> w;
        for (int i : v) {
            if (!w.empty() && crossv(t[w.back()].x - A.x, t[w.back()].y - A.y, t[i].x - A.x, t[i].y - A.y) == 0)
                continue;  // ugyanazon a sugáron, távolabb
            w.push_back(i);
        }
        v = w;
    };
    reduce(left, true);
    reduce(right, false);
    int L = (int)left.size(), R = (int)right.size();

    // A bal fákat a q körüli szög szerint is rendezzük, és megjegyezzük, hogy egy szuffixukban
    // melyik a legkisebb sorszámú (az A körüli sorrendben).
    vector<int> byQ, sufMin;
    if (q >= 0) {
        byQ.resize(L);
        iota(byQ.begin(), byQ.end(), 0);
        sort(byQ.begin(), byQ.end(), [&](int i, int j) { return cross(t[q], t[left[i]], t[left[j]]) > 0; });
        sufMin.assign(L + 1, INT_MAX);
        for (int k = L - 1; k >= 0; k--) sufMin[k] = min(sufMin[k + 1], byQ[k]);
    }

    // A jobb fákat az AP-hez közelebbitől haladva keressük az (r, l) párt, ahol l a legkisebb
    // sorszámú bal fa, amellyel az rl szakasz a q előtt metszi az AP-t. Csak az a pár érdekes,
    // amelyben l sorszáma szigorúan kisebb az eddigiekénél: az üres háromszöget ad.
    int curMin = INT_MAX;
    for (int ai = 0; ai < R; ai++) {
        const Pt& r = t[right[ai]];
        // a bal fák közül az első bmax darabbal alkot az (A, r, l) háromszög <180 fokos szöget
        int lo = 0, hi = L;
        while (lo < hi) {
            int mid = (lo + hi) / 2;
            if (cross(A, r, t[left[mid]]) > 0) lo = mid + 1; else hi = mid;
        }
        int bmax = lo, b;
        if (q < 0) {
            b = bmax > 0 ? 0 : INT_MAX;
        } else {
            // az r-t és q-t összekötő egyenes bal oldalán levő bal fák egy szuffixot alkotnak a q körüli rendezésben
            ll dx = t[q].x - r.x, dy = t[q].y - r.y;
            int l2 = 0, h2 = L;
            while (l2 < h2) {
                int mid = (l2 + h2) / 2;
                const Pt& l = t[left[byQ[mid]]];
                if (crossv(dx, dy, l.x - t[q].x, l.y - t[q].y) > 0) h2 = mid; else l2 = mid + 1;
            }
            int m = sufMin[l2];
            b = (m < bmax) ? m : INT_MAX;
        }
        if (b == INT_MAX || b >= curMin) continue;
        curMin = b;
        const Pt& l = t[left[b]];
        if (cross(r, l, p) > 0) {  // P szigorúan a háromszögön belül van
            cout << right[ai] + 1 << ' ' << left[b] + 1 << '\n';
            return 0;
        }
    }
    cout << "0 0\n";
    return 0;
}
