/*
Megoldás lényege:
Két repülőtér akkor van közvetlen járatban, ha egyik sem nagyobb a másiknál mindkét koordinátában, vagy egyik sem kisebb. Így a (0,0) pontból induló BFS-ben egy pont szomszédai csak az északkeleti és a délnyugati negyedsíkba eső pontok lehetnek. Az éleket nem nézzük végig egyenként (az O(N^2) lenne), hanem minden csúcsnál a még nem látott pontokat keressük ki a két negyedsíkban: a pontokat x szerint rendezzük, és két maximumos szegmensfát építünk, az egyik az y, a másik a -y értékeket tárolja. Az északkeleti negyedsík az x-szerint rendezett sor jobb oldali szakasza, itt az y >= y_u feltételű pontokat keressük; a délnyugati negyedsík a bal oldali szakasz, ahol -y >= -y_u. Amint egy pontot megtaláltunk, mindkét fából töröljük, így minden pont legfeljebb egyszer kerül a sorba. Az egész O(N log N) időben fut, és a K-nál nagyobb távolságú vagy el nem érhető repülőtereket számoljuk meg.
*/
/*
Hint 1: || Két pont akkor van közvetlen járatban, ha a két koordinátájuk összehasonlítható és ugyanabba az irányba mutatnak. Így a (0,0) pont szomszédai is csak az északkeleti vagy a délnyugati negyedsíkban lehetnek. Gondold végig, hogyan kerülheted el, hogy minden élt külön ellenőrizz. ||
Hint 2: || Rendezd a repülőtereket x szerint, és egy szegmensfában tárold az y-okat, egy másikban a -y-okat. Egy u pont északkeleti szomszédai a rendezett sor jobb oldali szakaszában vannak, és ott az y-ok maximuma legalább y_u kell legyen. ||
Hint 3: || A délnyugati szomszédokat ugyanígy keresd a bal oldali szakaszban, a -y-ok maximumával. Amikor egy pontot először találsz meg, töröld mindkét fából, így minden pontot legfeljebb egyszer dolgozol fel. A BFS-t elég K szintig futtatni, utána a nem látott pontok a válasz. ||
*/
#include <bits/stdc++.h>
using namespace std;

const int NEG = INT_MIN;

// Maximumos szegmensfa; a törölt pozíciók értéke NEG.
struct MaxSeg {
    int sz;
    vector<int> t;

    explicit MaxSeg(const vector<int>& a) {
        sz = 1;
        while (sz < (int)a.size()) sz <<= 1;
        t.assign(2 * sz, NEG);
        for (int i = 0; i < (int)a.size(); i++) t[sz + i] = a[i];
        for (int i = sz - 1; i >= 1; i--) t[i] = max(t[2 * i], t[2 * i + 1]);
    }

    void erase(int p) {
        p += sz;
        t[p] = NEG;
        for (p >>= 1; p >= 1; p >>= 1) t[p] = max(t[2 * p], t[2 * p + 1]);
    }

    // A [l, r] pozíciók közül összegyűjti azokat, ahol az érték legalább thr.
    void collect(int node, int nl, int nr, int l, int r, int thr, vector<int>& out) const {
        if (nr < l || nl > r || t[node] < thr) return;
        if (nl == nr) {
            out.push_back(nl);
            return;
        }
        int mid = (nl + nr) / 2;
        collect(2 * node, nl, mid, l, r, thr, out);
        collect(2 * node + 1, mid + 1, nr, l, r, thr, out);
    }

    void collect(int l, int r, int thr, vector<int>& out) const {
        if (l > r) return;
        collect(1, 0, sz - 1, l, r, thr, out);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> X(n), Y(n);
    for (int i = 0; i < n; i++) cin >> X[i] >> Y[i];

    // A repülőtereket x szerint rendezzük; ord[p] a p-edik pont eredeti indexe.
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) { return X[a] < X[b]; });

    vector<int> sx(n), ay(n), by(n);
    for (int p = 0; p < n; p++) {
        int v = ord[p];
        sx[p] = X[v];
        ay[p] = Y[v];
        by[p] = -Y[v];
    }

    MaxSeg NE(ay);  // északkeleti: x >= ux és y >= uy
    MaxSeg SW(by);  // délnyugati: x <= ux és y <= uy, azaz -y >= -uy

    vector<int> dist(n, -1);

    // Az (ux, uy) csúcs még nem látott szomszédait d távolsággal felfedezi.
    auto expand = [&](int ux, int uy, int d, vector<int>& next) {
        int l = lower_bound(sx.begin(), sx.end(), ux) - sx.begin();
        int r = (int)(upper_bound(sx.begin(), sx.end(), ux) - sx.begin()) - 1;
        vector<int> found;
        NE.collect(l, n - 1, uy, found);
        SW.collect(0, r, -uy, found);
        for (int p : found) {
            int v = ord[p];
            if (dist[v] != -1) continue;
            dist[v] = d;
            NE.erase(p);
            SW.erase(p);
            next.push_back(v);
        }
    };

    // A (0,0) kezdőpont szomszédai 1 repüléssel érhetők el.
    vector<int> cur;
    expand(0, 0, 1, cur);
    for (int d = 1; d < k && !cur.empty(); d++) {
        vector<int> nxt;
        for (int u : cur) expand(X[u], Y[u], d + 1, nxt);
        cur.swap(nxt);
    }

    vector<int> bad;
    for (int i = 0; i < n; i++)
        if (dist[i] == -1) bad.push_back(i + 1);

    cout << bad.size() << '\n';
    for (size_t i = 0; i < bad.size(); i++) {
        if (i) cout << ' ';
        cout << bad[i];
    }
    cout << '\n';
    return 0;
}
