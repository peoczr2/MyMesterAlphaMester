/*
Megoldás lényege:
Egy oszlop állapota a teteje (az utoljára rakott, így a legkisebb rendeltetési hely), és az x konténer csak olyan oszlop tetejére rakható, amelynek teteje legalább x. Mohó módon mindig a legkisebb, x-nél nem kisebb tetejű oszlopra rakjuk a konténert; ha nincs ilyen, új oszlopot nyitunk. Ez a választás optimális, mert a minimális oszlopszám a leghosszabb szigorúan növekvő részsorozat hossza (Dilworth-tétel), és a legkisebb megfelelő tető választásával a nagyobb tetejű oszlopok a későbbi nagy értékeknek maradnak. A tetejek halmazát két szintű bitmezőben tároljuk, így a következő elem keresése gyakorlatilag konstans idejű. Az összidő O(N), ami a 2 000 000 elemű bemenetnél szükséges az időlimit betartásához; ezért a bemenetet is pufferelten olvassuk.
*/
/*
Hint 1: || Ha több megfelelő oszlop teteje is >= x, mindig a „legszűkebbet” (legkisebb tetejűt) érdemes választani. ||
Hint 2: || A felső értékek halmazában az x-nél nem kisebb legkisebb elemet kell megtalálni: erre rendezett szerkezet vagy bitmező alkalmas. ||
Hint 3: || Minden konténerhez mentsd el az oszlopazonosítót, ez lesz a második sor kimenete. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Gyors bemenet-olvasás (fread-del, pufferelten).
static char ibuf[1 << 16];
static size_t ipos = 0, ilen = 0;

static int gc() {
    if (ipos == ilen) {
        ilen = fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen == 0) return -1;
    }
    return ibuf[ipos++];
}

static int readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9')) c = gc();
    int x = 0;
    while (c >= '0' && c <= '9') {
        x = x * 10 + (c - '0');
        c = gc();
    }
    return x;
}

// Egészek halmaza a [0, n] tartományból. Két szintű bitmező: w0 a bitek szavai,
// w1 jelzi, mely w0-szavak nem üresek. A "legkisebb elem >= i" lekérdezés gyors.
struct IntSet {
    vector<unsigned long long> w0, w1;

    explicit IntSet(int n) : w0((n >> 6) + 1, 0), w1((n >> 12) + 1, 0) {}

    void insert(int i) {
        w0[i >> 6] |= 1ULL << (i & 63);
        w1[i >> 12] |= 1ULL << ((i >> 6) & 63);
    }

    void erase(int i) {
        w0[i >> 6] &= ~(1ULL << (i & 63));
        if (!w0[i >> 6]) w1[i >> 12] &= ~(1ULL << ((i >> 6) & 63));
    }

    // a legkisebb benne lévő elem, ami >= i; -1, ha nincs ilyen
    int lowerBound(int i) const {
        int b = i >> 6;
        unsigned long long m = w0[b] & (~0ULL << (i & 63));
        if (m) return (b << 6) | __builtin_ctzll(m);
        int nb = b + 1;
        for (int c = nb >> 6; c < (int)w1.size(); ++c) {
            unsigned long long mm = w1[c];
            if (c == (nb >> 6)) mm &= ~0ULL << (nb & 63);
            if (mm) {
                int blk = (c << 6) | __builtin_ctzll(mm);
                return (blk << 6) | __builtin_ctzll(w0[blk]);
            }
        }
        return -1;
    }
};

int main() {
    int N = readInt();
    int K = readInt();

    IntSet tops(K);                     // az oszlopok aktuális tetejei (értékek)
    vector<vector<int>> colsAt(K + 1);  // adott tetejű oszlopok azonosítói
    vector<int> ans(N);
    int cols = 0;

    for (int i = 0; i < N; ++i) {
        int x = readInt();
        int t = tops.lowerBound(x);
        int id;
        if (t == -1) {
            id = ++cols;
        } else {
            id = colsAt[t].back();
            colsAt[t].pop_back();
            if (colsAt[t].empty()) tops.erase(t);
        }
        colsAt[x].push_back(id);
        tops.insert(x);
        ans[i] = id;
    }

    // kimenet: a sorok kiírása pufferelten
    vector<char> out;
    out.reserve((size_t)N * 8 + 16);
    auto put = [&](int v) {
        char tmp[12];
        int len = 0;
        do { tmp[len++] = char('0' + v % 10); v /= 10; } while (v);
        while (len) out.push_back(tmp[--len]);
    };
    put(cols);
    out.push_back('\n');
    for (int i = 0; i < N; ++i) {
        if (i) out.push_back(' ');
        put(ans[i]);
    }
    out.push_back('\n');
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
