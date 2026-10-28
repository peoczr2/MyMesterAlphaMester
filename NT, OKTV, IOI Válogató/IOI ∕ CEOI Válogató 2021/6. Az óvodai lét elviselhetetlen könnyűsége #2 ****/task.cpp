/*
Megoldás lényege:
Ha n gyerek van és K-t választanak, a legtöbb K-fős csoport alakul, így n mod K gyerek kiesik, és floor(n/K)*K marad. Legyen f(n) a szükséges körök száma, f(0)=0, és f(n) = 1 + min f(floor(n/K)*K) a listában szereplő K-kra, amelyekre K nem osztója n-nek (ha K osztója, a lépés nem változtat a létszámon). Egy n-re a minimum közvetlenül O(M)-ből jön, ez összesen O(N*M), ami túl lassú. Ehelyett minden K-ra az érték floor(n/K)*K csak n = K*j és n = K*j+1 pontokon változik, így összesen kb. N*log N változás van. Ezeket gyakorisági tömbbel követjük, a minimumot pedig 64-es szavas bitsettel (3 szint) kapjuk meg. Az időigény O(N log N + M + Q).
*/
/*
Hint 1: || Ha K-val lépsz, n mod K gyerek esik ki, és floor(n/K)*K marad. A feladat tehát legrövidebb út n-ből 0-ba, ahol az átmenet n -> floor(n/K)*K. Ha K osztója n-nek, az átmenet nem csökkent semmit. Ha a listában van n-nél nagyobb szám, egy körben vége. ||
Hint 2: || Legyen f(n) a minimális körszám n gyerekre, f(0)=0. Ekkor f(n) = 1 + min f(floor(n/K)*K) a listabeli K-kra, amelyekre K nem osztója n-nek. Ez közvetlenül O(N*M), ami túl lassú. ||
Hint 3: || Rögzített K-ra a floor(n/K)*K érték csak n = K*j és n = K*j+1 pontokon változik. Tartsd nyilván minden K aktuális értékét, egy gyakorisági tömbben számold, hány K-nak van adott értéke, és a minimumot bitsettel keresd minden n-nél. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Halmaz legkisebb elemének lekérdezése: 64-es szavas bitset, több szinten.
struct MinSet {
    vector<vector<unsigned long long>> seg;
    int lg;

    explicit MinSet(int n) {
        do {
            seg.push_back(vector<unsigned long long>((n + 63) >> 6, 0ULL));
            n = (n + 63) >> 6;
        } while (n > 1);
        lg = (int)seg.size();
    }

    void insert(int i) {
        for (int h = 0; h < lg; h++, i >>= 6)
            seg[h][i >> 6] |= 1ULL << (i & 63);
    }

    void erase(int i) {
        for (int h = 0; h < lg; h++, i >>= 6) {
            seg[h][i >> 6] &= ~(1ULL << (i & 63));
            if (seg[h][i >> 6]) break;
        }
    }

    bool empty() const { return seg[lg - 1][0] == 0; }

    // Nem üres halmazra.
    int min() const {
        int i = 0;
        for (int h = lg - 1; h >= 0; h--)
            i = (i << 6) | __builtin_ctzll(seg[h][i]);
        return i;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, Q;
    cin >> M >> Q;
    vector<int> K(M);
    for (int &x : K) cin >> x;
    vector<int> N(Q);
    for (int &x : N) cin >> x;

    int NMAX = *max_element(N.begin(), N.end());
    int KMAX = *max_element(K.begin(), K.end());

    // A K-k listája minden m <= NMAX számra: data[st[m] .. st[m+1]), ahol K | m.
    vector<int> st(NMAX + 2, 0);
    for (int k : K)
        if (k <= NMAX)
            for (int m = k; m <= NMAX; m += k) st[m + 1]++;
    for (int m = 1; m <= NMAX + 1; m++) st[m] += st[m - 1];

    vector<int> data(st[NMAX + 1]);
    vector<int> pos(st.begin(), st.end());
    for (int k : K)
        if (k <= NMAX)
            for (int m = k; m <= NMAX; m += k) data[pos[m]++] = k;

    const int INF = -1;
    // cur[k]: a k-hoz tartozó érték, f(floor(n/k)*k); kezdetben n=1 esetén f(0)=0.
    vector<int> cur(KMAX + 1, 0);
    // cnt[v]: hány K-nak van jelenleg f-értéke v.
    vector<int> cnt(NMAX + 2, 0);
    MinSet ms(NMAX + 2);
    cnt[0] = M;
    ms.insert(0);

    vector<int> f(NMAX + 1, INF);
    f[0] = 0;
    for (int n = 1; n <= NMAX; n++) {
        if (n >= 2) {
            // K | n: ezen K-val nincs csökkenés, az érték kikerül a halmazból.
            for (int p = st[n]; p < st[n + 1]; p++) {
                int k = data[p];
                int old = cur[k];
                if (old != INF) {
                    if (--cnt[old] == 0) ms.erase(old);
                    cur[k] = INF;
                }
            }
            // K | (n-1): most floor(n/K)*K = n-1, az érték f(n-1).
            int v = f[n - 1];
            if (v != INF) {
                for (int p = st[n - 1]; p < st[n]; p++) {
                    int k = data[p];
                    if (cnt[v]++ == 0) ms.insert(v);
                    cur[k] = v;
                }
            }
        }
        f[n] = ms.empty() ? INF : ms.min() + 1;
    }

    string out;
    for (int x : N) {
        out += to_string(f[x] == INF ? 0 : f[x]);
        out += '\n';
    }
    cout << out;
    return 0;
}
