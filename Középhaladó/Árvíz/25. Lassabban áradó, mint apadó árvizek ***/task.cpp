/*
Megoldás lényege:
Először az árvizeket határozzuk meg: ezek a 800 cm-nél magasabb mérések maximális, egymás utáni sorozatai, amelyek egy balról jobbra haladó bejárással kinyerhetők.
Egy árvíz áradása a kezdetén lévő szigorúan növekvő szakasz, apadása a végén lévő szigorúan csökkenő szakasz; mindkettő hosszát egy-egy léptetéssel számoljuk, a kezdő, illetve a záró méréstől indulva.
Az árvizet akkor írjuk ki a lassabban áradók közé, ha az áradás hossza nagyobb az apadásénál; mindkét hosszt ugyanúgy, mérések számában mérjük, így az összehasonlítás pontos.
Mivel a léptetések mind az árvíz hosszába esnek, az összes munka O(N), ami N ≤ 10 000 esetén az időkorláton belül van.
*/
/*
Hint 1: || Az árvizeket most is a 800 cm-nél magasabb, egymás utáni mérések sorozataként határozd meg, és minden árvízre külön vizsgáld meg a két szakaszt. ||
Hint 2: || Az áradás hosszát a kezdő méréstől indulva számold, amíg a vízállás szigorúan nő; az apadás hosszát a záró méréstől visszafelé, amíg a vízállás szigorúan csökken. ||
Hint 3: || Az árvizet akkor írd ki, ha az áradás hossza nagyobb az apadás hosszánál. Egy egyelemű árvíz mindkét hossza 1, így nem lesz lassabban áradó. ||
*/
#include <bits/stdc++.h>
using namespace std;

// Kiírja a darabszámot, majd a [kezdet, vége] párokat egy sorban.
// Nulla darabszám esetén nincs további sor.
void kiir(const vector<pair<int, int>> &v) {
    cout << v.size() << '\n';
    if (v.empty()) return;
    for (size_t k = 0; k < v.size(); k++) {
        if (k > 0) cout << ' ';
        cout << v[k].first << ' ' << v[k].second;
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<pair<int, int>> arvizek, lassu;
    int i = 0;
    while (i < n) {
        if (a[i] <= 800) {
            i++;
            continue;
        }
        int l = i, r = i;
        while (r + 1 < n && a[r + 1] > 800) r++;
        arvizek.push_back({l + 1, r + 1});

        // Áradás: a kezdő, szigorúan növekvő szakasz hossza
        int aradas = 1;
        while (l + aradas <= r && a[l + aradas] > a[l + aradas - 1]) aradas++;
        // Apadás: a záró, szigorúan csökkenő szakasz hossza
        int apadas = 1;
        while (r - apadas >= l && a[r - apadas] > a[r - apadas + 1]) apadas++;

        if (aradas > apadas) lassu.push_back({l + 1, r + 1});
        i = r + 1;
    }

    kiir(arvizek);
    if (!arvizek.empty()) kiir(lassu);
    return 0;
}
