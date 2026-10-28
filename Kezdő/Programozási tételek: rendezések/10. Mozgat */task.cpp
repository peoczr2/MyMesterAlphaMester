/*
Megoldás lényege:
A szöveget soronként mozgatni O(N·K) munka lenne, N akár 10^6, K pedig 1000 lehet, ezért nem tesszük. Helyette a sorozatot összefüggő, eredeti sorszámú szakaszok listájaként tároljuk. Egy művelet legfeljebb három helyen vág, így a szakaszok száma legfeljebb 3K+1 lehet, és egy művelet ezen a listán O(K) lépésben elvégezhető: kivágjuk az [A..B] szakaszt, majd a C-edik pozíció után beszúrjuk. A C a művelet előtti sorszám, ezért a kivágás után C-t kell átszámolni, ha C a kivágott rész után volt. A végén a lista elejéből kiolvasható, melyik eredeti sor van az első 10 helyen, és az eredeti 1..10 sorok pozíciója is a szakaszok hosszának összegéből adódik. Összesen O(K²) munka.
*/
/*
Hint 1: || Ne a szöveg soraival dolgozz, hanem tartsd nyilván a sorozatot szakaszok listájaként, ahol minden szakasz az eredeti sorok egy összefüggő, növekvő tartománya. ||
Hint 2: || Egy műveletnél három határon vágj: az A előtt, a B után és a C helyén. A kivágott szakasz és a maradék részek szakaszait egy új listába fűzd, a C-t pedig a kivágott rész hosszával csökkentsd, ha C ≥ B. ||
Hint 3: || A végső lista bejárásával mindkét kimenő sor kiszámolható: a pozíciók összegzéssel adódnak, és az első 10 pozíció eredeti sorszámai a szakaszok elejéről olvashatók ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Összefüggő, eredeti sorszámú szakasz: az eredeti [l..r] sorok, növekvő sorrendben.
struct Seg {
    long long l, r;
    long long len() const { return r - l + 1; }
};

// A szakaszlista 1-től számozott pozícióinak [from..to] tartományához tartozó darabok.
vector<Seg> cutpart(const vector<Seg> &v, long long from, long long to) {
    vector<Seg> res;
    long long start = 1;  // az aktuális szakasz első pozíciója
    for (const Seg &s : v) {
        long long end = start + s.len() - 1;
        long long lo = max(start, from), hi = min(end, to);
        if (lo <= hi) res.push_back({s.l + (lo - start), s.l + (hi - start)});
        start = end + 1;
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long n;
    int k;
    cin >> n >> k;
    vector<Seg> seq = {{1, n}};

    for (int t = 0; t < k; t++) {
        long long a, b, c;
        cin >> a >> b >> c;
        long long blen = b - a + 1;

        vector<Seg> block = cutpart(seq, a, b);  // a kivágott rész
        vector<Seg> rest = cutpart(seq, 1, a - 1);
        vector<Seg> tail = cutpart(seq, b + 1, n);
        rest.insert(rest.end(), tail.begin(), tail.end());  // a kivágás utáni sorozat

        // C a művelet előtti sorszám: C < A esetén nem változik, C >= B esetén a kivágott rész miatt csökken
        long long cc = (c < a) ? c : c - blen;
        vector<Seg> left = cutpart(rest, 1, cc);
        vector<Seg> right = cutpart(rest, cc + 1, n);

        seq = left;
        seq.insert(seq.end(), block.begin(), block.end());
        seq.insert(seq.end(), right.begin(), right.end());
    }

    // Az eredeti 1..10 sorok végső pozíciója, és az első 10 pozícióban álló eredeti sorok.
    vector<long long> where(11, 0);
    vector<long long> firstTen;
    long long pos = 0;  // az eddigi szakaszok összes hossza
    for (const Seg &s : seq) {
        long long len = s.len();
        for (long long x = 1; x <= 10; x++)
            if (s.l <= x && x <= s.r) where[x] = pos + (x - s.l) + 1;
        for (long long q = pos + 1; q <= min(pos + len, 10LL); q++)
            firstTen.push_back(s.l + (q - pos - 1));
        pos += len;
    }

    for (int x = 1; x <= 10; x++) cout << where[x] << (x < 10 ? ' ' : '\n');
    for (size_t i = 0; i < firstTen.size(); i++)
        cout << firstTen[i] << (i + 1 < firstTen.size() ? ' ' : '\n');
    return 0;
}
