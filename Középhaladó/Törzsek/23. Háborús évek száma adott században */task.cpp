/*
Megoldás lényege:
A megadott századba eső háborús éveket kell megszámolni úgy, hogy minden évet csak egyszer számoljunk. Ezért minden háború intervallumát a század [alsó év, felső év] tartományára vágjuk, a nem üres metszeteket kezdő év szerint rendezzük, és egy menetben egyesítjük az átfedőket.
Az egyesített szakaszok éveinek összege adja a választ, mert a különböző szakaszok nem fedik egymást.
A római számú évszázadot (XVII., XVIII., XIX.) az értéke alapján dolgozzuk fel. Az idő O(K log K), ahol K a háborúk száma, a rendezés miatt.
*/
/*
Hint 1: || Itt nem az évek összege a kérdés: ha két háború ugyanazt az évet fedi, azt az évet csak egyszer szabad figyelembe venni. Először csak a megadott századba eső részeket nézd meg. ||
Hint 2: || Vágd minden háború intervallumát a század alsó és felső évére (max és min), a nem üres metszeteket rendezd kezdés szerint, és egy menetben egyesítsd az átfedőket. Az egyesített szakaszok (befejezés - kezdés + 1) hosszainak összege adja a választ. ||
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

    // A századra vágott, nem üres intervallumok.
    vector<pair<int, int>> metszet;
    for (const auto& [kezdet, vege] : haboru) {
        int a = max(kezdet, lo), b = min(vege, hi);
        if (a <= b) metszet.push_back({a, b});
    }
    sort(metszet.begin(), metszet.end());

    // Az átfedő intervallumok egyesítése, és a lefedett évek összeszámolása.
    long long evek = 0;
    if (!metszet.empty()) {
        int cs = metszet[0].first, ce = metszet[0].second;
        for (size_t i = 1; i < metszet.size(); i++) {
            int s = metszet[i].first, e = metszet[i].second;
            if (s <= ce) {
                ce = max(ce, e);
            } else {
                evek += ce - cs + 1;
                cs = s;
                ce = e;
            }
        }
        evek += ce - cs + 1;
    }
    cout << evek << '\n';
}
