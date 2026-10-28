/*
Megoldás lényege:
Az A és B pontot összekötő egyenes két oldalára bontjuk a többi pontot. Az egyik oldal
pontjait A körül, a másik oldalét B körül szögrendezzük: így egy oldalon belül a szomszédos
szakaszok diszjunkt szögtartományokban vannak, tehát nem metszik egymást. Az A-ból induló
lánc utolsó pontja az AB iránya felé (A-ból nézve) legközelebbi pont, a B-be érkező lánc
első pontja pedig ugyanígy a B-hez legközelebbi pont. Az összekötő szakasz csak akkor jó,
ha az AB egyenest a két láncnak megfelelő irányban metszi, ezért három lehetséges irányt
és az oldalak sorrendjét végigpróbáljuk. Az időigény O(N log N).
*/
/*
Hint 1: || Az AB egyenes két oldalát külön kezeld: ha az egyik oldal pontjait A körül szög szerint rendezed, a szomszédos szakaszok nem metszhetik egymást, mert különböző szögtartományokban vannak. ||
Hint 2: || A másik oldal pontjait B körül rendezd. Az A-ból induló lánc utolsó pontja az AB irányához legközelebbi legyen, a B-ből induló lánc első pontja pedig szintén a B-hez tartozó legközelebbi pont. ||
Hint 3: || Az összekötő szakasz és az AB egyenes metszéspontjának helye (A előtt, A és B között vagy B után) dönti el, melyik irányú végpontokat kell választani. Ezt a három esetet egyszerűen végigpróbálhatod. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

struct Pt {
    ll x, y;
};

static ll cross(const Pt& u, const Pt& v) { return u.x * v.y - u.y * v.x; }
static ll dot(const Pt& u, const Pt& v) { return u.x * v.x + u.y * v.y; }
static Pt sub(const Pt& p, const Pt& q) { return {p.x - q.x, p.y - q.y}; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, A, B;
    cin >> n >> A >> B;
    vector<Pt> P(n + 1);
    for (int i = 1; i <= n; ++i) cin >> P[i].x >> P[i].y;
    const Pt d = sub(P[B], P[A]);

    // o-ból nézve: p szögben közelebb van-e az s*d félegyeneshez, mint q.
    auto closer = [&](int o, int s, int p, int q) {
        Pt vp = sub(P[p], P[o]), vq = sub(P[q], P[o]);
        Pt r = {s * d.x, s * d.y};
        return cross(r, vp) > 0 ? cross(vp, vq) > 0 : cross(vp, vq) < 0;
    };

    vector<int> up, lo;
    for (int i = 1; i <= n; ++i) {
        if (i == A || i == B) continue;
        if (cross(d, sub(P[i], P[A])) > 0) up.push_back(i);
        else lo.push_back(i);
    }

    // (sA, sB): melyik félegyenes felé nézzen az A-, illetve a B-végpont
    const int dirs[3][2] = {{1, -1}, {-1, -1}, {1, 1}};

    vector<int> path;
    for (int first = 0; first < 2 && path.empty(); ++first) {
        const vector<int>& S1 = first == 0 ? up : lo;  // A körüli legyező
        const vector<int>& S2 = first == 0 ? lo : up;  // B körüli legyező
        for (int c = 0; c < 3 && path.empty(); ++c) {
            const int sA = dirs[c][0], sB = dirs[c][1];
            if (S1.empty() && sB != -1) continue;
            if (S2.empty() && sA != 1) continue;

            int pe = A, qe = B;
            if (!S1.empty()) {
                pe = S1[0];
                for (int q : S1) if (closer(A, sA, q, pe)) pe = q;
            }
            if (!S2.empty()) {
                qe = S2[0];
                for (int q : S2) if (closer(B, sB, q, qe)) qe = q;
            }

            if (!S1.empty() && !S2.empty()) {
                // u: az összekötő szakasz és az AB egyenes metszéspontjának helye (A: 0, B: 1)
                ll cP = cross(d, sub(P[pe], P[A])), cQ = cross(d, sub(P[qe], P[A]));
                ll dP = dot(sub(P[pe], P[A]), d), dQ = dot(sub(P[qe], P[A]), d);
                lll N = (lll)cP * dQ - (lll)cQ * dP;
                lll D = (lll)(cP - cQ) * dot(d, d);
                if (D == 0) continue;
                if (D < 0) { D = -D; N = -N; }
                bool ok = (c == 0) ? (N > 0 && N < D) : (c == 1 ? N < 0 : N > D);
                if (!ok) continue;
            }

            vector<int> f1 = S1, f2 = S2;
            stable_sort(f1.begin(), f1.end(), [&](int p, int q) { return closer(A, sA, p, q); });
            reverse(f1.begin(), f1.end());  // a legközelebbi pont kerül az utolsó helyre
            stable_sort(f2.begin(), f2.end(), [&](int p, int q) { return closer(B, sB, p, q); });

            path.push_back(A);
            path.insert(path.end(), f1.begin(), f1.end());
            path.insert(path.end(), f2.begin(), f2.end());
            path.push_back(B);
        }
    }

    if (path.empty()) {
        path.push_back(A);
        for (int i = 1; i <= n; ++i)
            if (i != A && i != B) path.push_back(i);
        path.push_back(B);
    }

    for (size_t i = 0; i < path.size(); ++i) {
        if (i) cout << ' ';
        cout << path[i];
    }
    cout << '\n';
    return 0;
}
