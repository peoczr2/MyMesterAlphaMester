/*
Megoldás lényege:
Az origóból egy P csúcs akkor köthető egyenes vezetékkel, ha az OP szakasz nem metszi a sokszög többi pontját, vagyis
P az origóból nézve a sugár első közös pontja. Minden csúcs irányát primitív egész vektorként tároljuk, így egy sugár
egyértelmű, és az egy sugárra eső csúcsok közül csak a legközelebbi lehet látható. A sugarak szögszerinti sorrendjében
söprünk: a sokszög azon éleit tartjuk nyilván egy rendezett halmazban, amelyek a sugarat belsőleg metszik, és ezek közül
a legközelebbi metszéspontot hasonlítjuk a sugár legközelebbi csúcsához. A halmaz rendezését a söprés aktuális sugarán
mért távolság adja, a közös végpontú élek sorrendjét a sugár utáni szakasz dönti el. Az időigény O(N log N).
*/
/*
Hint 1: || Egy csúcs csak akkor látszik az origóból, ha az origóba vezető sugarán nincs nála közelebbi pontja a sokszögnek. Így egy sugárra legfeljebb egy csúcs eshet a látható halmazba. ||
Hint 2: || Rendezd a csúcsokat szög szerint az origóból (keresztszorzattal), és a szögek közötti söprésnél tartsd nyilván, mely élek metszik a sugarat belsőleg. Az egyenes metszésének távolságát egy egyszerű törttel lehet összehasonlítani. ||
Hint 3: || Az élek halmazát a söprés aktuális sugarán mért távolság szerint rendezd, és a közös végpontú élek sorrendjét a sugár utáni szakasz dönti el. A sugarak irányait primitív egész vektorként tárold, a szorzatoknál pedig 128 bites egész számot használj a túlcsordulás ellen. ||
*/
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef __int128 lll;

struct Pt {
    ll x, y;
};

ll crossP(const Pt& a, const Pt& b) { return a.x * b.y - a.y * b.x; }
ll dotP(const Pt& a, const Pt& b) { return a.x * b.x + a.y * b.y; }

Pt curDir;             // a söprés aktuális sugarának primitív iránya
vector<Pt> Lp, Hp;     // az élek szögszerint kisebb (L) és nagyobb (H) végpontja
vector<ll> ecross;     // cross(L, H) > 0

// Az élek rendezése a curDir sugáron mért távolság szerint; egyenlőség esetén a sugár utáni sorrend dönt.
struct ByDistance {
    bool operator()(int a, int b) const {
        Pt wa{Hp[a].x - Lp[a].x, Hp[a].y - Lp[a].y};
        Pt wb{Hp[b].x - Lp[b].x, Hp[b].y - Lp[b].y};
        lll Da = crossP(curDir, wa);
        lll Db = crossP(curDir, wb);
        lll lhs = (lll)ecross[a] * Db;
        lll rhs = (lll)ecross[b] * Da;
        if (lhs != rhs) return lhs < rhs;
        lll Ea = dotP(curDir, wa);
        lll Eb = dotP(curDir, wb);
        lll l2 = Ea * Db;
        lll r2 = Eb * Da;
        if (l2 != r2) return l2 < r2;
        return a < b;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Pt> P(n);
    for (auto& p : P) cin >> p.x >> p.y;

    // csúcsok primitív iránya és szorzója: P = mu * dir
    vector<Pt> dir(n);
    vector<ll> mu(n);
    for (int i = 0; i < n; i++) {
        ll g = gcd(P[i].x, P[i].y);
        dir[i] = {P[i].x / g, P[i].y / g};
        mu[i] = g;
    }

    // szög szerinti rendezés, azonos irányon belül a közelebbi csúcs elöl
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        ll c = crossP(dir[a], dir[b]);
        if (c != 0) return c > 0;
        return mu[a] < mu[b];
    });

    // sugarak: különböző irányok, minden sugárhoz a legközelebbi csúcs
    vector<Pt> rayDir;
    vector<int> rayNear;
    vector<ll> rayMu;
    vector<int> rayOf(n);
    for (int idx = 0; idx < n; idx++) {
        int v = ord[idx];
        if (rayDir.empty() || crossP(rayDir.back(), dir[v]) != 0) {
            rayDir.push_back(dir[v]);
            rayNear.push_back(v);
            rayMu.push_back(mu[v]);
        }
        rayOf[v] = (int)rayDir.size() - 1;
    }
    int R = (int)rayDir.size();

    // élek: csak azok, amelyek nem az origón mennek át (az origón átmenő élek a csúcsok kizárásával már kezelve vannak)
    vector<vector<int>> insAt(R), remAt(R);
    for (int i = 0; i < n && n >= 2; i++) {
        int j = (i + 1) % n;
        ll cr = crossP(P[i], P[j]);
        if (cr == 0) continue;
        int a = i, b = j;
        if (cr < 0) swap(a, b);
        int e = (int)Lp.size();
        Lp.push_back(P[a]);
        Hp.push_back(P[b]);
        ecross.push_back(crossP(P[a], P[b]));
        insAt[rayOf[a]].push_back(e);
        remAt[rayOf[b]].push_back(e);
    }
    int M = (int)Lp.size();

    set<int, ByDistance> active;
    vector<set<int, ByDistance>::iterator> pos(M);
    vector<int> visible;
    for (int k = 0; k < R; k++) {
        for (int e : remAt[k]) active.erase(pos[e]);
        curDir = rayDir[k];
        bool vis = true;
        if (!active.empty()) {
            int e = *active.begin();
            Pt w{Hp[e].x - Lp[e].x, Hp[e].y - Lp[e].y};
            lll D = crossP(curDir, w);
            // az e élnek a sugárral való metszéspontja λ*dir, λ = c / D; a csúcs μ*dir
            if ((lll)ecross[e] < (lll)rayMu[k] * D) vis = false;
        }
        if (vis) visible.push_back(rayNear[k]);
        for (int e : insAt[k]) pos[e] = active.insert(e).first;
    }

    sort(visible.begin(), visible.end());
    cout << visible.size() << '\n';
    for (size_t i = 0; i < visible.size(); i++) {
        if (i) cout << ' ';
        cout << visible[i] + 1;
    }
    cout << '\n';
    return 0;
}
