/*
Megoldás lényege:
Két képpont pontosan akkor kerül egy osztályba, ha fényességük 1-es különbségű láncon keresztül összeköthető, ezért az osztályok a képen előforduló, egymást követő egész fényességértékek maximális szakaszai. Nem kell képpontpárokat vizsgálni: minden fényességértékhez eltároljuk, hol fordul elő a képen (a legkisebb és legnagyobb sor- és oszlopindexét), majd az értékeket növekvő sorrendben végigjárva minden szakaszra megkapjuk a különböző értékek számát és a befoglaló téglalapot. Az időigény O(N * M + 100000), a memóriaigény az értéktartománnyal arányos.
*/
/*
Hint 1: || Figyeld meg, hogy a képpontok helye nem számít, csak a fényességük. Két fényességérték ugyanabba az osztályba kerül, ha különbségük legfeljebb 1, és ez láncolódhat. Így elég a fényességértékek halmazát vizsgálni. ||
Hint 2: || Egy beolvasás alatt minden fényességértékhez jegyezd meg, előfordul-e a képen, és a legkisebb és legnagyobb sor- és oszlopindexet, ahol szerepel. Ezekből a szélsőértékekből később az osztály befoglaló téglalapja összeállítható. ||
Hint 3: || Az értékeket növekvő sorrendben bejárva az egymást követő, előforduló értékek egy-egy osztályt alkotnak. Az osztály különböző értékeinek száma a szakasz hossza, a befoglaló téglalap széleit pedig a szakaszhoz tartozó értékek szélsőértékei adják. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const int MAXV = 100000;
    int n, m;
    cin >> n >> m;

    // fényességértékenként: előfordul-e, és a legkisebb/legnagyobb sor- és oszlopindex
    vector<char> present(MAXV + 2, 0);
    vector<int> rmin(MAXV + 2, INT_MAX), rmax(MAXV + 2, INT_MIN);
    vector<int> cmin(MAXV + 2, INT_MAX), cmax(MAXV + 2, INT_MIN);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int f;
            cin >> f;
            present[f] = 1;
            rmin[f] = min(rmin[f], i);
            rmax[f] = max(rmax[f], i);
            cmin[f] = min(cmin[f], j);
            cmax[f] = max(cmax[f], j);
        }
    }

    int classes = 0, bestCount = 0;
    int bestR1 = 0, bestC1 = 0, bestR2 = 0, bestC2 = 0;

    int v = 1;
    while (v <= MAXV) {
        if (!present[v]) { v++; continue; }
        // egy osztály: egymást követő, előforduló fényességértékek
        int count = 0;
        int r1 = INT_MAX, c1 = INT_MAX, r2 = INT_MIN, c2 = INT_MIN;
        while (v <= MAXV && present[v]) {
            count++;
            r1 = min(r1, rmin[v]);
            c1 = min(c1, cmin[v]);
            r2 = max(r2, rmax[v]);
            c2 = max(c2, cmax[v]);
            v++;
        }
        classes++;
        if (count > bestCount) {
            bestCount = count;
            bestR1 = r1; bestC1 = c1; bestR2 = r2; bestC2 = c2;
        }
    }

    cout << classes << '\n';
    cout << bestCount << '\n';
    cout << bestR1 << ' ' << bestC1 << ' ' << bestR2 << ' ' << bestC2 << '\n';
    return 0;
}
