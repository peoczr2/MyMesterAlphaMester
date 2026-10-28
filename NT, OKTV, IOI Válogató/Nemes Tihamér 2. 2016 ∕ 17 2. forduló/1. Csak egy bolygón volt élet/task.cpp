/*
    A két bolygó életszakaszai rendezett, zárt intervallumok. Azok a részek,
    ahol pontosan az egyik bolygón van élet, a két halmaz szimmetrikus
    különbségét adják. Minden intervallumhoz két eseményt rendelünk: a kezdetnél
    +1-et, a vége utáni évnél -1-et. Az eseményeket időrendbe rendezzük, és
    egyszerre végigmegyünk rajtuk: nyilvántartjuk, hány bolygón van élet.
    Azonos évhez tartozó változásokat összevonjuk, így a szomszédos időszakok
    automatikusan egybeolvadnak. Időigény: O(N log N), ahol N az intervallumok száma.
*/
/*
Hint 1: || Gondolj úgy az intervallumokra, mint nyitó és záró eseményekre az időtengelyen, és számold, hányan vannak élőben egy adott évben. ||
Hint 2: || Ha az eseményeket rendezed, az egy bolygóra jutó időszakok azok a szakaszok, ahol a számláló éppen 1. Az 1-es szintről való belépés kezdetet, a kilépés végződést jelent (a végződés a kilépést megelőző év). ||
Hint 3: || Ugyanazon az x időpontban történő több esemény eredőjét egyszerre vedd figyelembe: így egy időpontban történő belépés és kilépés nem szakít meg egy folyamatos időszakot. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    vector<pair<long long, int>> esemenyek;

    auto beolvas = [&](int darab) {
        for (int i = 0; i < darab; ++i) {
            long long l, r;
            cin >> l >> r;
            esemenyek.push_back({l, 1});
            esemenyek.push_back({r + 1, -1});
        }
    };

    beolvas(a);
    beolvas(b);
    sort(esemenyek.begin(), esemenyek.end());

    vector<pair<long long, long long>> valasz;
    int aktiv = 0;
    long long kezdet = 0;
    for (size_t i = 0; i < esemenyek.size();) {
        long long x = esemenyek[i].first;
        int delta = 0;
        while (i < esemenyek.size() && esemenyek[i].first == x) {
            delta += esemenyek[i].second;
            ++i;
        }
        int uj = aktiv + delta;
        if (aktiv != 1 && uj == 1) kezdet = x;
        if (aktiv == 1 && uj != 1) valasz.push_back({kezdet, x - 1});
        aktiv = uj;
    }

    cout << valasz.size() << '\n';
    for (auto [l, r] : valasz) cout << l << ' ' << r << '\n';
    return 0;
}