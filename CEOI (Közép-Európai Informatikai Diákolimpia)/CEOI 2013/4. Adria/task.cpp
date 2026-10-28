/*
Megoldás lényege:
Két sziget között egy lépés akkor lehetséges, ha a sorszámuk és az oszlopszámuk is szigorúan ugyanabba az irányba változik.
A legrövidebb út hossza nem korlátozódik 3-ra: a szigetek cikcakkos láncot is alkothatnak, ilyenkor 4 vagy több lépés kell.
Ezért minden kezdő szigetből szélességi bejárást (BFS) futtatunk, és a távolságok összegét adjuk ki.
A bejárásban a csúcs szomszédai a nála északnyugatra és délkeletre lévő, még nem látogatott szigetek; ezeket a sorszám szerint rendezett szigeteken két szegmensfa (oszlopszám minimum) adja meg, a meglátogatott szigetet törléssel kivesszük.
Időigény: O(N^2 log N); a teljes korlátnál (N <= 250 000) ez már túl lassú, ott gyorsabb ötlet kell.
*/
/*
Hint 1: || Két sziget között a lépés csak akkor lehetséges, ha mindkét koordináta szigorúan ugyanabba az irányba változik. Ezért a szomszédok két átlós negyedsíkban vannak, és a távolság nem korlátozódik 3-ra: próbálj ki egy cikcakkos láncot. ||
Hint 2: || Mivel a távolság tetszőlegesen nagy lehet, kezdő szigetenként szélességi bejárást futtass, és a sziget összes távolságát add össze. ||
Hint 3: || A sorban a szomszédok keresése gyors legyen: a szigeteket sorszám szerint rendezd, így az északnyugati és délkeleti tartomány sorszám szerint prefix és szuffix. Az oszlopszámra egy minimum-szegmensfa adja a feltételt, és a már látogatott szigetet töröld belőle. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Minimum-szegmensfa: egy pozíció törölhető (az értéke INT_MAX lesz), és egy
// tartományban meg lehet keresni egy olyan pozíciót, ahol az érték x-nél kisebb.
struct MinSeg {
    int n = 0;
    vector<int> t;

    void build(int v, int l, int r, const vector<int>& a) {
        if (l == r) {
            t[v] = a[l];
            return;
        }
        int m = (l + r) / 2;
        build(2 * v, l, m, a);
        build(2 * v + 1, m + 1, r, a);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    void init(const vector<int>& a) {
        n = a.size();
        t.assign(4 * n, INT_MAX);
        build(1, 0, n - 1, a);
    }
    void erase(int v, int l, int r, int pos) {
        if (l == r) {
            t[v] = INT_MAX;
            return;
        }
        int m = (l + r) / 2;
        if (pos <= m) erase(2 * v, l, m, pos);
        else erase(2 * v + 1, m + 1, r, pos);
        t[v] = min(t[2 * v], t[2 * v + 1]);
    }
    void erase(int pos) {
        erase(1, 0, n - 1, pos);
    }
    int find(int v, int l, int r, int ql, int qr, int x) const {
        if (qr < l || r < ql || t[v] >= x) return -1;
        if (l == r) return l;
        int m = (l + r) / 2;
        int res = find(2 * v, l, m, ql, qr, x);
        if (res != -1) return res;
        return find(2 * v + 1, m + 1, r, ql, qr, x);
    }
    // egy pozíció a [ql, qr] tartományból, ahol az érték < x; -1, ha nincs
    int find(int ql, int qr, int x) const {
        if (ql > qr) return -1;
        return find(1, 0, n - 1, ql, qr, x);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> r(n), c(n);
    for (int i = 0; i < n; ++i) cin >> r[i] >> c[i];

    // a szigetek sorszám (majd oszlopszám) szerint rendezett sorrendben
    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return r[a] != r[b] ? r[a] < r[b] : c[a] < c[b];
    });

    vector<int> R(n), C(n), negC(n), pos(n), lo(n), hi(n);
    for (int p = 0; p < n; ++p) {
        R[p] = r[ord[p]];
        C[p] = c[ord[p]];
        negC[p] = -C[p];
        pos[ord[p]] = p;
    }
    for (int p = 0; p < n; ++p) {
        // lo[p]: az első pozíció, ahol a sorszám nem kisebb R[p]-nél; hi[p]: ahol nagyobb
        lo[p] = lower_bound(R.begin(), R.end(), R[p]) - R.begin();
        hi[p] = upper_bound(R.begin(), R.end(), R[p]) - R.begin();
    }

    MinSeg lessC, greaterC;  // lessC az oszlopszámokat, greaterC a negatívjukat tartalmazza
    vector<int> dist(n);
    for (int s = 0; s < n; ++s) {
        lessC.init(C);
        greaterC.init(negC);
        fill(dist.begin(), dist.end(), -1);

        queue<int> q;
        int sp = pos[s];
        dist[sp] = 0;
        lessC.erase(sp);
        greaterC.erase(sp);
        q.push(sp);

        while (!q.empty()) {
            int p = q.front();
            q.pop();
            // északnyugat: sorszám kisebb és oszlopszám kisebb
            while (true) {
                int x = lessC.find(0, lo[p] - 1, C[p]);
                if (x == -1) break;
                dist[x] = dist[p] + 1;
                lessC.erase(x);
                greaterC.erase(x);
                q.push(x);
            }
            // délkelet: sorszám nagyobb és oszlopszám nagyobb
            while (true) {
                int x = greaterC.find(hi[p], n - 1, negC[p]);
                if (x == -1) break;
                dist[x] = dist[p] + 1;
                lessC.erase(x);
                greaterC.erase(x);
                q.push(x);
            }
        }

        long long sum = 0;
        for (int p = 0; p < n; ++p)
            if (dist[p] > 0) sum += dist[p];
        cout << sum << '\n';
    }
    return 0;
}
