/*
Megoldás lényege:
Egy háború évei közül csak a megadott századba eső részt vesszük figyelembe: az intervallumot a század [alsó év, felső év] tartományára vágjuk, és a metszet éveit (a két végpontot is beleszámítva) összeadjuk.
Ha több háború fedi ugyanazt az évet, az a háború többször is beleszámít, ezért az eredmény akár 100-nál is nagyobb lehet.
A római számú évszázadot (XVII., XVIII., XIX.) az értéke alapján dolgozzuk fel. Az idő O(K), ahol K a háborúk száma.
*/
/*
Hint 1: || A kérdés az, hogy minden háború évei közül melyek esnek a megadott századba, és ezeket az éveket hogyan lehet megszámolni. Gondold végig, hogy egy háború intervallumát hogyan lehet a századra korlátozni. ||
Hint 2: || A század alsó és felső éve például a XIX. századnál 1801 és 1900. Minden háborúra vedd az intervallum és a század tartományának metszetét; ha nem üres, a benne lévő évek száma b - a + 1, és ezt add az összeghez. ||
*/
#include <bits/stdc++.h>
using namespace std;

// A római szám értéke (pl. "XIX." -> 19); a pont és a nem római karakter kimarad.
int romai(const string& s) {
    auto ertek = [](char c) {
        switch (c) {
            case 'I': return 1;
            case 'V': return 5;
            case 'X': return 10;
            case 'L': return 50;
            case 'C': return 100;
            default: return 0;
        }
    };
    int osszeg = 0;
    for (size_t i = 0; i < s.size(); i++) {
        int v = ertek(s[i]);
        if (v == 0) continue;
        int kovetkezo = (i + 1 < s.size()) ? ertek(s[i + 1]) : 0;
        osszeg += (v < kovetkezo) ? -v : v;
    }
    return osszeg;
}

int main() {
    // A minta be1 fájlja elején UTF-8 BOM állhat (3 bájt): ezt átugorjuk.
    if (cin.peek() == 0xEF) cin.ignore(3);

    int n, k;
    cin >> n >> k;
    vector<pair<int, int>> haboru(k);  // (kezdő év, befejező év)
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b >> haboru[i].first >> haboru[i].second;
    }
    string szazad;
    cin >> szazad;
    int c = romai(szazad);
    int lo = (c - 1) * 100 + 1, hi = c * 100;

    long long osszes = 0;
    for (const auto& [kezdet, vege] : haboru) {
        int a = max(kezdet, lo), b = min(vege, hi);
        if (a <= b) osszes += b - a + 1;
    }
    cout << osszes << '\n';
}
