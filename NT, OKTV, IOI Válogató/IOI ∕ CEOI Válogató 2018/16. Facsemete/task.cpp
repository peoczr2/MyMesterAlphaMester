/*
Húzzuk meg az A-ból a P facsemetén át induló félegyenest: a jó háromszögben B ennek jobb, C a bal
oldalán van, és a BC oldal P után metszi a félegyenest. Ha A és P között (vagy P-ben) fa áll,
nincs megoldás. Ha P után sincs fa a félegyenesen, mindkét oldalon az A körüli szögben a
félegyeneshez legközelebbi fát vesszük (azonos szögnél a közelebbit): a két fa közötti szögtartományban
nincs fa, így a háromszög üres; ha pedig B', C' jó pár, akkor ez a két fa a B'C' oldalon túl van
(vagy épp B', C'), ezért BC is P után metszi a félegyenest, vagyis ha ez a pár nem jó, nincs megoldás.
Ha P után van fa, legyen V a legközelebbi: ekkor BC-nek a PV szakaszt kell metszenie, és belátható,
hogy ha van jó pár, akkor olyan is van, amelyre az A, V, B és az A, V, C háromszög is üres. Ezeket a
fákat szög szerint rendezve egy menetben gyűjtjük ki (egy fa akkor kell, ha az utoljára kigyűjtött a
V-vel összekötő egyenesén túl van). A két listán a "V a BC túloldalán van" feltétel a sorszámokkal
egyre könnyebb, a "P a BC innenső oldalán van" egyre nehezebb, így két mutatóval végigmehetünk.
Időigény: a rendezés miatt O(N log N), memória O(N).
*/
/*
Hint 1: || Húzd meg az A-ból P-n át induló félegyenest: B az egyik, C a másik oldalán van, és BC-nek P után kell metszenie. Ha a félegyenesen P után nincs fa, elég mindkét oldalon az A körüli szögben legközelebbi fát kipróbálni. ||
Hint 2: || Ha P után van fa a félegyenesen (a legközelebbi V), akkor BC-nek a PV szakaszt kell metszenie. Elég olyan B-t nézni, amelyre az A, V, B háromszög üres; A körüli szög szerint rendezve ezek egy menetben kigyűjthetők, mindig az utoljára elfogadott fával összevetve. ||
Hint 3: || A két listán haladva a "V a BC másik oldalán van" feltétel egyre könnyebb, a "P a BC innenső oldalán van" egyre nehezebb. Így minden B-hez elég a legelső, V-t már kizáró C-t kipróbálni, és ez két mutatóval megy. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

struct Pt {
    ll x, y;
};

// Az o -> a -> b irányított terület kétszerese: pozitív, ha b az o -> a bal oldalán van.
static ll cross(const Pt& o, const Pt& a, const Pt& b) {
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}

static int sgn(ll v) { return (v > 0) - (v < 0); }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, ai;
    if (!(cin >> n >> ai)) return 0;
    Pt p;
    cin >> p.x >> p.y;
    vector<Pt> t(n + 1);
    for (int i = 1; i <= n; ++i) cin >> t[i].x >> t[i].y;

    const Pt A = t[ai];
    auto none = []() { cout << "0 0\n"; };
    if (A.x == p.x && A.y == p.y) { none(); return 0; }

    ll dx = p.x - A.x, dy = p.y - A.y, len2 = dx * dx + dy * dy;
    vector<int> R, L;  // R: az A->P jobb oldala (ide kerül B), L: a bal oldala (ide kerül C)
    int v = 0;
    ll vd = 0;  // V: a P utáni legközelebbi fa a félegyenesen
    for (int i = 1; i <= n; ++i) {
        if (i == ai) continue;
        ll s = cross(A, p, t[i]);
        if (s < 0) R.push_back(i);
        else if (s > 0) L.push_back(i);
        else {
            ll d = (t[i].x - A.x) * dx + (t[i].y - A.y) * dy;
            if (d < 0) continue;              // A mögött van, nem számít
            if (d <= len2) { none(); return 0; }  // A és P között (vagy A-ban, P-ben)
            if (v == 0 || d < vd) { v = i; vd = d; }
        }
    }
    if (R.empty() || L.empty()) { none(); return 0; }

    auto dist2 = [&](int i) {
        ll ex = t[i].x - A.x, ey = t[i].y - A.y;
        return ex * ex + ey * ey;
    };
    // Rendezés A körül: a félegyeneshez közelebbi szög előre, azonos szögnél a közelebbi fa előre.
    sort(R.begin(), R.end(), [&](int u, int w) {
        ll c = cross(A, t[u], t[w]);
        if (c != 0) return c < 0;
        return dist2(u) < dist2(w);
    });
    sort(L.begin(), L.end(), [&](int u, int w) {
        ll c = cross(A, t[u], t[w]);
        if (c != 0) return c > 0;
        return dist2(u) < dist2(w);
    });

    if (v == 0) {
        int b = R[0], c = L[0];
        if (cross(t[b], t[c], p) > 0) cout << b << ' ' << c << '\n';
        else none();
        return 0;
    }

    const Pt V = t[v];
    // Azok a fák, amelyekre az A, V, T háromszög üres: T akkor jó, ha az utoljára
    // elfogadott fa szigorúan a V-T egyenes túloldalán van (A-hoz képest).
    auto chain = [&](const vector<int>& side) {
        vector<int> res;
        int cur = 0;
        for (int u : side) {
            if (cur == 0 || sgn(cross(V, t[u], t[cur])) == -sgn(cross(V, t[u], A))) {
                res.push_back(u);
                cur = u;
            }
        }
        return res;
    };
    vector<int> G = chain(R), H = chain(L);

    // V legyen a BC túloldalán (felfelé zárt), P az innenső oldalán (lefelé zárt).
    size_t j = 0;
    for (int i = (int)G.size() - 1; i >= 0; --i) {
        while (j < H.size() && cross(t[G[i]], t[H[j]], V) >= 0) ++j;
        if (j == H.size()) break;
        if (cross(t[G[i]], t[H[j]], p) > 0) {
            cout << G[i] << ' ' << H[j] << '\n';
            return 0;
        }
    }
    none();
    return 0;
}
