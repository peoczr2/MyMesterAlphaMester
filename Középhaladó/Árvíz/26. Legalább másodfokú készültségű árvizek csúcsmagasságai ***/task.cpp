/*
Megoldás lényege:
Az árvizek most is a 800 cm-nél magasabb mérések maximális, egymás utáni sorozatai. Egy árvíz akkor legalább másodfokú készültségű, ha az egész ideje alatt legalább másodfokú a készültség, vagyis minden mérése meghaladja a 900 cm-t.
Egy bejárás során minden árvízre ellenőrizzük ezt a feltételt, és közben megkeressük a legmagasabb vízállást; egyenlőség esetén a korábbi helyet tartjuk meg.
A megfelelő árvizek kezdő és záró sorszámát, valamint a csúcs helyét és értékét külön listában gyűjtjük, és ebben a sorrendben írjuk ki.
Az időigény O(N), ami N ≤ 10 000 esetén az időkorláton belül van.
*/
/*
Hint 1: || Az árvizek a 800 cm-nél magasabb mérések egymás utáni sorozatai. Egy árvíz csak akkor kerül a listába, ha minden mérése 900 cm-nél magasabb, tehát már egyetlen ilyen nem teljesítő mérés is kizárja. ||
Hint 2: || Az árvíz bejárása közben egyszerre ellenőrizd a feltételt és keresd a legnagyobb vízállást. A csúcs helyéhez az első előfordulást kell megadni, ezért szigorú „nagyobb” összehasonlítást használj. ||
Hint 3: || Két listát érdemes vezetni: az árvizek [kezdet, vége] párjait és a csúcsok [hely, érték] párjait. A darabszám mindkettőnél a lista hossza, és nulla esetén a kimenet csak a 0. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int &x : a) cin >> x;

    vector<pair<int, int>> arvizek;  // [kezdet, vége], 1-től számozva
    vector<pair<int, int>> csucsok;  // [hely, érték]
    int i = 0;
    while (i < n) {
        if (a[i] <= 800) {
            i++;
            continue;
        }
        int l = i, r = i;
        while (r + 1 < n && a[r + 1] > 800) r++;

        bool legalabb2 = true;
        int hely = l;
        for (int k = l; k <= r; k++) {
            if (a[k] <= 900) legalabb2 = false;
            if (a[k] > a[hely]) hely = k;  // egyenlőnél marad a korábbi
        }
        if (legalabb2) {
            arvizek.push_back({l + 1, r + 1});
            csucsok.push_back({hely + 1, a[hely]});
        }
        i = r + 1;
    }

    cout << arvizek.size() << '\n';
    if (arvizek.empty()) return 0;
    for (size_t k = 0; k < arvizek.size(); k++) {
        if (k > 0) cout << ' ';
        cout << arvizek[k].first << ' ' << arvizek[k].second;
    }
    cout << '\n';
    for (size_t k = 0; k < csucsok.size(); k++) {
        if (k > 0) cout << ' ';
        cout << csucsok[k].first << ' ' << csucsok[k].second;
    }
    cout << '\n';
    return 0;
}
