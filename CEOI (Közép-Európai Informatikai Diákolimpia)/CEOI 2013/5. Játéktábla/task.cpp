/*
Megoldás lényege:
Egy csúcs szintjét és balról jobbra számolt sorszámát a gyökértől vezető lépéssorozat adja meg: a bal fiú 0, a jobb fiú 1 bitet ad a sorszám bináris alakjához.
A vízszintes lépés a sorszámot eggyel növeli vagy csökkenti, az 'U' lépés az utolsó bitet törli, ezért a sorszámot bitenként tároljuk, az átvitelt szavanként kezeljük.
Legyen L a két csúcs közös őseinek legmagasabb szintje (a sorszámok közös prefixe). A legrövidebb út felmegy egy h szintre (L <= h <= min(kA,kB)), ott vízszintesen |a_h - b_h| lépést tesz, és lemegy, így a költség (kA-h)+(kB-h)+|a_h-b_h|.
A d_h = a_h - b_h különbség rekurzívan számolható: d_h = 2*d_{h-1} + (A bitje - B bitje), |d_h| nem csökken, és 3 vagy nagyobb értéknél a költség h növelésével már nem csökken, ezért a keresés ott megállhat.
Időigény: a keresés O(n), ahol n a két útvonal hossza; a sorszámok átvitele szavanként legrosszabb esetben O(n^2 / 64).
*/
/*
Hint 1: || A csúcs szintje és sorszáma a gyökértől vezető karakterekből kiolvasható, a sorszám bitjei a bal-jobb fiú döntésekből állnak. Az L és R lépés átvitellel járhat, ezért a sorszámot érdemes bitekként tárolni. ||
Hint 2: || Két csúcs között a legrövidebb út egy h szinten vízszintesen halad: felmegy a csúcsból h szintre, ott lép |a_h - b_h| -t, majd lemegy. Melyik h szinteket kell megvizsgálni, és mennyi a két csúcs költsége az adott h-n? ||
Hint 3: || Az a_h - b_h különbség h növelésével kétszereződik, és egy bit különbsége adódik hozzá, így rekurzívan számolható. A költség csak addig csökkenhet, amíg a különbség abszolút értéke legfeljebb 2, ezért a keresés korán megállítható. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Egy csúcs: szint (k) és sorszám bitjei. A p = 0 a legfelső (első) bit, a p = k-1 az utolsó bit.
struct Node {
    int k = 0;
    vector<unsigned long long> w;

    int get(int p) const {
        return (w[p >> 6] >> (p & 63)) & 1ULL;
    }
    void set(int p, int v) {
        unsigned long long m = 1ULL << (p & 63);
        if (v) w[p >> 6] |= m;
        else w[p >> 6] &= ~m;
    }
    // a [lo, hi) bitek beállítása v-re, a teljes szavakat egyszerre
    void fill(int lo, int hi, int v) {
        int p = lo;
        while (p < hi) {
            if ((p & 63) == 0 && p + 64 <= hi) {
                w[p >> 6] = v ? ~0ULL : 0ULL;
                p += 64;
            } else {
                set(p, v);
                ++p;
            }
        }
    }
    // a legnagyobb p < k, amelyre get(p) == v; -1, ha nincs ilyen
    int lastWith(int v) const {
        int p = k - 1;
        while (p >= 0) {
            int wi = p >> 6, off = p & 63;
            unsigned long long x = v ? w[wi] : ~w[wi];
            if (off < 63) x &= (1ULL << (off + 1)) - 1;
            if (x) return (wi << 6) + 63 - __builtin_clzll(x);
            p = (wi << 6) - 1;
        }
        return -1;
    }
    void push(int b) { set(k, b); ++k; }  // bal/jobb fiú: x -> 2x + b
    void pop() { --k; }                    // 'U': x -> x / 2
    void inc() {                           // 'R': x -> x + 1
        int p = lastWith(0);
        if (p < 0) return;
        fill(p + 1, k, 0);
        set(p, 1);
    }
    void dec() {                           // 'L': x -> x - 1
        int p = lastWith(1);
        if (p < 0) return;
        fill(p + 1, k, 1);
        set(p, 0);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string sa, sb;
    cin >> sa >> sb;

    auto build = [](const string& s) {
        Node x;
        x.w.assign(s.size() / 64 + 2, 0ULL);
        for (char ch : s) {
            if (ch == '1') x.push(0);
            else if (ch == '2') x.push(1);
            else if (ch == 'U') x.pop();
            else if (ch == 'L') x.dec();
            else if (ch == 'R') x.inc();
        }
        return x;
    };
    Node A = build(sa), B = build(sb);

    int M = min(A.k, B.k);
    int L = 0;
    while (L < M && A.get(L) == B.get(L)) ++L;

    // h = L: a közös ősig megyünk fel, majd le
    long long best = (long long)(A.k - L) + (B.k - L);
    long long d = 0;  // d = a_h - b_h, ahol a_h, b_h a h szintű ősök sorszáma
    for (int h = L + 1; h <= M; ++h) {
        d = 2 * d + (A.get(h - 1) - B.get(h - 1));
        long long ad = llabs(d);
        best = min(best, (long long)(A.k - h) + (B.k - h) + ad);
        if (ad >= 3) break;
    }

    cout << best << '\n';
    return 0;
}
