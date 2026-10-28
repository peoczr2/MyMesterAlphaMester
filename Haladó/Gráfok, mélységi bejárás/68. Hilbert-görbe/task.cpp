/*
Megoldás lényege:
A Hilbert-görbén minden pontnak van egy sorszáma (d), amely bitenként számolható. A legfelső bittől haladva megnézzük, melyik negyedben van a pont (rx, ry), és az s² · ((3·rx) xor ry) értéket hozzáadjuk d-hez, ahol s az aktuális bit értéke. Ezután a pontot a negyedben érvényes forgatással és tükrözéssel átalakítjuk, hogy az alacsonyabb bitekre ugyanez a szabály vonatkozzon. A pontokat d szerint növekvően rendezve megkapjuk a bejárási sorrendet. A sorszámok legfeljebb 2^60 nagyságúak, ezért 64 bites egész kell. Idő: O(M·N + M log M), ahol N ≤ 30 és M ≤ 100 000.
*/
/*
Hint 1: || A görbe rekurzív: az N-edrendű görbe négy (N−1)-edrendű részből áll, és a pont helye a négy rész közül határozza meg, melyikben van. A sorszámot ezért a legfelső bittől kezdve, bitenként lehet felépíteni. ||
Hint 2: || Egy szinten a negyed sorszáma 0, 1, 2 vagy 3, és ezt a két koordináta-bit együtt adja. A bal alsó és a jobb alsó negyedben a részgörbe másként van elforgatva és tükrözve, ezért a koordinátákat a következő, kisebb bitekre való lépés előtt át kell alakítani. ||
Hint 3: || Ha minden ponthoz kiszámoltad a görbén elfoglalt sorszámát, a feladat már csak egy rendezés: a pontokat ezen sorszám szerint növekvően kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A (x, y) pont sorszáma a Hilbert-görbén, a görbe 2^N × 2^N-es rácson, n = 2^N.
long long hilbertIndex(long long n, long long x, long long y) {
    long long d = 0;
    for (long long s = n / 2; s > 0; s /= 2) {
        long long rx = (x & s) > 0;
        long long ry = (y & s) > 0;
        d += s * s * ((3 * rx) ^ ry);
        if (ry == 0) {
            if (rx == 1) {
                x = n - 1 - x;
                y = n - 1 - y;
            }
            swap(x, y);
        }
    }
    return d;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;
    long long n = 1LL << N;

    vector<tuple<long long, long long, long long>> pts(M);
    for (int i = 0; i < M; i++) {
        long long x, y;
        cin >> x >> y;
        pts[i] = make_tuple(hilbertIndex(n, x, y), x, y);
    }
    sort(pts.begin(), pts.end());

    for (const auto &p : pts) {
        cout << get<1>(p) << ' ' << get<2>(p) << '\n';
    }
    return 0;
}
