/*
Megoldás lényege:
Két reptér pontosan akkor köthető közvetlen járattal, ha az egyik mindkét koordinátája nem kisebb a másikénál, vagy mindkettő nem nagyobb. Egy repülőtér szomszédai tehát az északkeleti negyedsík (x és y is nem kisebb) és a délnyugati negyedsík (x és y is nem nagyobb) pontjai. A feladat így szélességi bejárás a (0,0) pontból, legfeljebb K szintig. A bejárás minden pontot legfeljebb egyszer fedez fel, ezért a még fel nem fedezett pontokat x szerint rendezve két szegmensfában tartjuk nyilván: az egyik a y, a másik a -y értékeket tárolja maximumra. Egy negyedsík lekérdezése egy x-intervallumban keresi a megfelelő y-határt, a talált pontokat pedig törölhetjük a fákból. Az egész algoritmus O(N log N) időben fut. A kimenetben a nem elérhető repterek x-koordináta szerint növekvő sorrendben szerepelnek.
*/
/*
Hint 1: || Két reptér pontosan akkor van közvetlen járattal összekötve, ha az egyik mindkét koordinátája nem kisebb a másikénál, vagy mindkettő nem nagyobb. Így a feladat szélességi bejárás (BFS), amelyet a (0,0) pontból indítasz, és legfeljebb K szintig futtatsz. ||
Hint 2: || Szélességi bejárásban minden repteret elég egyszer felfedezni. Tartsd nyilván a még fel nem fedezett pontokat, és minden csúcsnál csak azokat a pontokat gyűjtsd ki a két negyedsíkból, amelyek még nincsenek nyilvántartva. ||
Hint 3: || Rendezd a pontokat x szerint: ekkor minden negyedsík egy x-intervallum, és az y-feltétel egy szegmensfával kezelhető. Az északkeleti negyedsíkhoz a y-ra, a délnyugatihoz a -y-ra építs maximumfát, és a felfedezett pontokat mindkét fából töröld. ||
*/
#include <bits/stdc++.h>
using namespace std;

const long long NEG_INF = LLONG_MIN / 4;

// Szegmensfa: a leveleken értékek vannak, a törölt pont értéke NEG_INF.
// A [l, r) intervallumban kigyűjti azokat a pozíciókat, ahol az érték legalább thr.
struct MaxSegTree {
    int sz;
    vector<long long> t;

    explicit MaxSegTree(const vector<long long>& a) {
        sz = 1;
        while (sz < (int)a.size()) sz <<= 1;
        t.assign(2 * sz, NEG_INF);
        for (int i = 0; i < (int)a.size(); ++i) t[sz + i] = a[i];
        for (int v = sz - 1; v >= 1; --v) t[v] = max(t[2 * v], t[2 * v + 1]);
    }

    void erase(int p) {
        int v = p + sz;
        t[v] = NEG_INF;
        for (v >>= 1; v >= 1; v >>= 1) t[v] = max(t[2 * v], t[2 * v + 1]);
    }

    void collect(int v, int nl, int nr, int l, int r, long long thr, vector<int>& out) const {
        if (nr <= l || r <= nl || t[v] < thr) return;
        if (nr - nl == 1) {
            out.push_back(nl);
            return;
        }
        int mid = (nl + nr) / 2;
        collect(2 * v, nl, mid, l, r, thr, out);
        collect(2 * v + 1, mid, nr, l, r, thr, out);
    }

    void collect(int l, int r, long long thr, vector<int>& out) const {
        if (l < r) collect(1, 0, sz, l, r, thr, out);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    // A 0. pont a központi reptér (0,0), az 1..n pontok a repterek.
    vector<long long> X(n + 1, 0), Y(n + 1, 0);
    for (int i = 1; i <= n; ++i) cin >> X[i] >> Y[i];

    // Pontok rendezése x, majd y szerint: ord[p] a p-edik pont azonosítója, pos[id] a helye.
    vector<int> ord(n + 1), pos(n + 1);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return X[a] != X[b] ? X[a] < X[b] : Y[a] < Y[b];
    });
    vector<long long> xs(n + 1), ys(n + 1), negYs(n + 1);
    for (int p = 0; p <= n; ++p) {
        int id = ord[p];
        pos[id] = p;
        xs[p] = X[id];
        ys[p] = Y[id];
        negYs[p] = -Y[id];
    }
    // upTree: az y értékek (északkeleti negyedsík), downTree: a -y értékek (délnyugati negyedsík).
    MaxSegTree upTree(ys), downTree(negYs);

    vector<char> seen(n + 1, 0);
    seen[0] = 1;
    upTree.erase(pos[0]);
    downTree.erase(pos[0]);

    // A talált pontokat törli a fákból, megjelöli, és a következő szintbe teszi.
    auto discover = [&](const vector<int>& found, vector<int>& next) {
        for (int p : found) {
            upTree.erase(p);
            downTree.erase(p);
            seen[ord[p]] = 1;
            next.push_back(ord[p]);
        }
    };

    vector<int> frontier = {0};
    vector<int> found;
    for (int step = 0; step < k && !frontier.empty(); ++step) {
        vector<int> next;
        for (int u : frontier) {
            // Északkeleti negyedsík: x >= X[u] és y >= Y[u].
            int lo = int(lower_bound(xs.begin(), xs.end(), X[u]) - xs.begin());
            found.clear();
            upTree.collect(lo, n + 1, Y[u], found);
            discover(found, next);

            // Délnyugati negyedsík: x <= X[u] és y <= Y[u], azaz -y >= -Y[u].
            int hi = int(upper_bound(xs.begin(), xs.end(), X[u]) - xs.begin());
            found.clear();
            downTree.collect(0, hi, -Y[u], found);
            discover(found, next);
        }
        frontier.swap(next);
    }

    // A nem elérhető repterek x szerint rendezve.
    vector<int> unreached;
    for (int i = 1; i <= n; ++i)
        if (!seen[i]) unreached.push_back(i);
    sort(unreached.begin(), unreached.end(), [&](int a, int b) {
        if (X[a] != X[b]) return X[a] < X[b];
        if (Y[a] != Y[b]) return Y[a] < Y[b];
        return a < b;
    });

    cout << unreached.size() << '\n';
    for (size_t i = 0; i < unreached.size(); ++i) {
        if (i) cout << ' ';
        cout << unreached[i];
    }
    cout << '\n';
    return 0;
}
