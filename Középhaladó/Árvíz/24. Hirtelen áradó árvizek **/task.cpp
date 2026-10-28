/*
Megoldás lényege:
Egy árvíz a 800 cm-nél magasabb mérések maximális, egymás utáni sorozata, ezért egyetlen balról jobbra haladó bejárással mindegyik megtalálható.
Egy árvíz akkor hirtelen áradó, ha már a kezdő mérése is harmadfokú, vagyis meghaladja az 1000 cm-t, így ez a kezdő mérés értékéből eldönthető.
Minden árvíz kezdő és záró sorszámát (1-től számozva) eltároljuk, a hirtelen áradókat pedig külön listában gyűjtjük, így mindkét lista sorszám szerint növekvő sorrendben készül el.
Az időigény O(N), ami N ≤ 10 000 esetén messze az időkorláton belül van.
*/
/*
Hint 1: || Az árvizek a 800 cm-nél magasabb mérések maximális, egymás utáni sorozatai. Balról jobbra haladva, amikor egy ilyen sorozat elkezdődik, lépkedj a végéig, majd folytasd a következő mérésnél. ||
Hint 2: || Egy árvíz hirtelen áradó, ha a kezdő mérése nagyobb 1000 cm-nél. Az árvizeket egy listában, a hirtelen áradókat egy másikban tárold, és a kiírás előtt a darabszám a lista hossza. ||
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

    vector<pair<int, int>> arvizek, hirtelen;
    int i = 0;
    while (i < n) {
        if (a[i] <= 800) {
            i++;
            continue;
        }
        int j = i;
        while (j + 1 < n && a[j + 1] > 800) j++;
        arvizek.push_back({i + 1, j + 1});
        if (a[i] > 1000) hirtelen.push_back({i + 1, j + 1});
        i = j + 1;
    }

    kiir(arvizek);
    if (!arvizek.empty()) kiir(hirtelen);
    return 0;
}
