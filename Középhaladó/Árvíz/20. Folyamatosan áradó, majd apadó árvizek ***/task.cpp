/*
Megoldás lényege:
Árvíz minden maximális, egymás melletti, 800 cm-nél magasabb vízállásokból álló szakasz. Egy árvíz akkor folyamatosan áradó, majd apadó,
ha benne a vízállások szigorúan nőnek egy csúcsig, utána pedig szigorúan csökkennek; az egyelemű és a csak nővő vagy csak csökkenő árvíz is ilyen.
Balról jobbra haladva megkeressük az árvizeket, majd minden árvízen belül addig lépünk előre, amíg szigorúan nő a sorozat,
utána amíg szigorúan csökken. Ha a szakasz végére érünk, az árvíz megfelel. Az egyenlő egymás melletti értékek megszakítják a sorozatot.
Az időigény O(N), ami N = 10 000 esetén bőven belefér a 0,1 mp-es időlimitbe.
*/
/*
Hint 1: || Egy vízállás akkor tartozik árvízhez, ha meghaladja a 800 cm-t. Keresd meg az ilyen, egymás melletti vízállásokból álló maximális szakaszokat. ||
Hint 2: || Egy árvízen belül a vízállásokat balról jobbra nézve először szigorúan növekedniük kell, majd szigorúan csökkenniük. Egy bejárással mindkét rész könnyen ellenőrizhető. ||
Hint 3: || Ha a növekedési rész a szakasz végéig tart, vagy a csökkenési rész a végéig tart, az árvíz áradó majd apadó. Egyenlő két egymás melletti érték már nem szigorú, ezért a sorozat ott megszakad. ||
*/
#include <bits/stdc++.h>
using namespace std;

void printPairs(const vector<pair<int, int>>& v) {
    for (size_t k = 0; k < v.size(); k++) {
        if (k > 0) cout << ' ';
        cout << v[k].first << ' ' << v[k].second;
    }
    cout << '\n';
}

int main() {
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<pair<int, int>> arviz;
    vector<pair<int, int>> aradoApado;

    int i = 1;
    while (i <= n) {
        if (a[i] <= 800) {
            i++;
            continue;
        }
        int l = i;
        int r = i;
        while (r + 1 <= n && a[r + 1] > 800) r++;
        arviz.push_back({l, r});

        int j = l;
        while (j + 1 <= r && a[j] < a[j + 1]) j++;
        while (j + 1 <= r && a[j] > a[j + 1]) j++;
        if (j == r) aradoApado.push_back({l, r});

        i = r + 1;
    }

    cout << arviz.size() << '\n';
    if (arviz.empty()) return 0;
    printPairs(arviz);

    cout << aradoApado.size() << '\n';
    if (aradoApado.empty()) return 0;
    printPairs(aradoApado);

    return 0;
}
