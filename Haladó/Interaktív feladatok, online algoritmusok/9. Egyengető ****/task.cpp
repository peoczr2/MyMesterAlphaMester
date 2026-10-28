/*
Megoldás lényege:
Ha a sorozat elemei az [L, L+K] intervallumba kerülnek, minden a_i-t a legközelebbi pontjára kell mozgatni, így a költség f(L) = sum dist(a_i, [L, L+K]). Ez L-ben konvex, töröttvonalas függvény, a minimumát valamelyik töréspontban veszi fel. A meredekség vizsgálatából kiderül, hogy az optimális L az {a_i} és {a_i - K} együttes, 2m elemű halmaz m-edik legkisebb eleme, ahol m az eddig beolvasott elemek száma. Ezt a mediánt két kupac tartja karban: az alsó felet max-kupac, a felsőt min-kupac, így minden új elem O(log N) munkával beszúrható. A költséghez az L-nél nem nagyobb elemek darabszáma és összege, valamint az L+K-nál nagyobb elemek darabszáma és összege kell; ezt egy kulcs szerint rendezett, részfa-összegeket tároló treap adja. Egy elem feldolgozása O(log N), az összidő O(N log N), a memóriaigény O(N).
*/
/*
Hint 1: || Ha az [L, L+K] intervallumot rögzíted, minden a_i-t a legközelebbi intervallumbeli pontjára kell mozgatni. Így a teljes költség csak L függvénye: írd fel, és nézd meg, hol változik a meredeksége. ||
Hint 2: || A meredekség azon múlik, hány a_i van L alatt, és hány van L+K felett. A minimum ott van, ahol ez a két szám egyensúlyba kerül; átfogalmazva a minimum az {a_i} és {a_i - K} együttes, 2m elemű halmaz m-edik legkisebb eleménél van, ahol m az eddig beolvasott elemek száma. ||
Hint 3: || Az m-edik legkisebb elemet két kupaccal tartsd karban: az alsó felét max-kupacban, a felső felét min-kupacban. Minden új elemnél két értéket (a_i és a_i - K) kell beszúrni, majd a két kupac méretét m-re igazítani. ||
Hint 4: || A költséghez az L-nél nem nagyobb elemek (L - a_i) és az L+K-nál nagyobb elemek (a_i - L - K) összegét kell megkapni. Ehhez olyan adatszerkezet kell, amely beszúrásnál és kulcs szerinti összegző lekérdezésnél is gyors, például részfa-összeget tároló kiegyensúlyozott bináris fa. ||
*/
#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

// Kulcs szerint rendezett treap, részfánként darabszámmal és összeggel.
int keyv[MAXN], pri[MAXN], lc[MAXN], rc[MAXN], sz[MAXN];
long long sm[MAXN];
int nodeCnt = 0, root = 0;
mt19937 rng(20240601);

void pull(int t) {
    sz[t] = 1 + sz[lc[t]] + sz[rc[t]];
    sm[t] = keyv[t] + sm[lc[t]] + sm[rc[t]];
}

// A key-nél kisebb kulcsok a bal, a többiek a jobb fába kerülnek.
void split(int t, int key, int &l, int &r) {
    if (!t) {
        l = r = 0;
        return;
    }
    if (keyv[t] < key) {
        split(rc[t], key, rc[t], r);
        l = t;
    } else {
        split(lc[t], key, l, lc[t]);
        r = t;
    }
    pull(t);
}

int merge(int a, int b) {
    if (!a || !b) return a ? a : b;
    if (pri[a] > pri[b]) {
        rc[a] = merge(rc[a], b);
        pull(a);
        return a;
    }
    lc[b] = merge(a, lc[b]);
    pull(b);
    return b;
}

void insertKey(int x) {
    int n = ++nodeCnt;
    keyv[n] = x;
    pri[n] = (int)(rng() & 0x7fffffff);
    lc[n] = rc[n] = 0;
    sz[n] = 1;
    sm[n] = x;
    int a, b;
    split(root, x, a, b);
    root = merge(merge(a, n), b);
}

// A v-nél nem nagyobb kulcsok darabszáma és összege.
void prefixLE(long long v, long long &cnt, long long &sum) {
    cnt = 0;
    sum = 0;
    int t = root;
    while (t) {
        if (keyv[t] <= v) {
            cnt += sz[lc[t]] + 1;
            sum += sm[lc[t]] + keyv[t];
            t = rc[t];
        } else {
            t = lc[t];
        }
    }
}

// Az {a_i} és {a_i - K} halmaz median-kezelése: lo tartalmazza a legkisebb m elemet.
priority_queue<int> lo;
priority_queue<int, vector<int>, greater<int>> hi;

void addT(int x) {
    if (!lo.empty() && x <= lo.top()) lo.push(x);
    else hi.push(x);
}

void rebalance(int m) {
    while ((int)lo.size() > m) {
        hi.push(lo.top());
        lo.pop();
    }
    while ((int)lo.size() < m) {
        lo.push(hi.top());
        hi.pop();
    }
}

int main() {
    int n = getN();
    int k = getK();
    long long total = 0;
    for (int m = 1; m <= n; m++) {
        int x = Data();
        insertKey(x);
        total += x;
        addT(x);
        addT(x - k);
        rebalance(m);

        long long L = lo.top();
        long long c1, s1, c2, s2;
        prefixLE(L, c1, s1);
        prefixLE(L + k, c2, s2);
        long long below = c1 * L - s1;
        long long above = (total - s2) - (long long)(m - c2) * (L + k);
        Solution(below + above);
    }
    return 0;
}
