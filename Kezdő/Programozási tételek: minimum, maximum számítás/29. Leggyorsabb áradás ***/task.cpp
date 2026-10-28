/*
Megoldás lényege:
A mérések három kategóriába sorolhatók: árvízmentes (legfeljebb 800 cm), harmadfokú (1000 cm felett) és a köztes, árvízi, de nem harmadfokú állapot. Az elsőfokú és másodfokú készültség közti 900 cm-es határ az eredményt nem befolyásolja. Az egymás melletti, azonos kategóriájú mérésekből álló maximális sorozatok adják a szakaszokat, amelyeket egyetlen menetben, sorszám szerint gyűjtünk. A P értékhez azokat az (árvízmentes, harmadfokú) szomszédos szakaszpárokat keressük, ahol nincs közbeeső árvízmentes szakasz. A legközelebbi párt sorban haladva keressük: minden harmadfokú szakaszhoz az előtte lévő utolsó árvízmentes szakasz a legközelebbi jelölt, és egyenlő távolságnál a korábbi pár marad. Az időigény O(N), a memóriaigény O(N).
*/
/*
Hint 1: || A feladat csak három állapotot különböztet meg: árvízmentes (legfeljebb 800 cm), harmadfokú (1000 cm felett) és minden más. A 900 cm-es határ ehhez nem kell. ||
Hint 2: || Szakaszokat kell keresni: egymás melletti, azonos állapotú mérések maximális sorozatait. Az árvízmentes és a harmadfokú szakaszokat külön-külön gyűjtsd, de a sorrendjüket (sorszám szerint) tartsd meg. ||
Hint 3: || A P értékhez és a legközelebbi párhoz érdemes a szakaszokat sorszám szerinti sorrendben egymás után nézni: az árvízmentes szakasz után következő szakasz harmadfokú-e? A távolság a harmadfokú kezdete és az árvízmentes vége közti különbség. ||
Hint 4: || Csak az a pár számít, ahol az árvízmentes szakasz a harmadfokú előtt van, a fordított sorrend nem. Ha több pár is egyenlő távolságra van, a sorszám szerint korábbit kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Seg {
    int l, r;   // a szakasz kezdete és vége (1-től számozva)
    int type;   // 0 = árvízmentes, 2 = harmadfokú
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 0: árvízmentes (<= 800), 1: árvíz, de nem harmadfokú, 2: harmadfokú (> 1000)
    vector<int> cat(n + 1);
    for (int i = 1; i <= n; i++) {
        int a;
        cin >> a;
        if (a <= 800) cat[i] = 0;
        else if (a <= 1000) cat[i] = 1;
        else cat[i] = 2;
    }

    // Csak az árvízmentes és a harmadfokú szakaszokat tároljuk, sorszám szerinti sorrendben.
    vector<Seg> segs;
    for (int i = 1; i <= n; ) {
        int j = i;
        while (j < n && cat[j + 1] == cat[i]) j++;
        if (cat[i] != 1) segs.push_back({i, j, cat[i]});
        i = j + 1;
    }

    vector<pair<int, int>> arv, harm, pairsP;
    for (const Seg& s : segs) {
        if (s.type == 0) arv.push_back({s.l, s.r});
        else harm.push_back({s.l, s.r});
    }

    // P: árvízmentes szakasz, amelyet közvetlenül (közbülső árvízmentes szakasz nélkül) harmadfokú követ
    for (size_t k = 0; k + 1 < segs.size(); k++) {
        if (segs[k].type == 0 && segs[k + 1].type == 2) {
            pairsP.push_back({segs[k].r, segs[k + 1].l});
        }
    }

    // Legközelebbi árvízmentes-harmadfokú pár (árvízmentes szakasz van előbb).
    // Sorban haladva az utolsó árvízmentes szakasz a legközelebbi jelölt; egyenlő távolságnál a korábbi marad.
    bool found = false;
    int bestGap = 0, bl = 0, br = 0, hl = 0, hr = 0;
    int lastArv = -1;
    for (int k = 0; k < (int)segs.size(); k++) {
        if (segs[k].type == 0) {
            lastArv = k;
            continue;
        }
        if (lastArv < 0) continue;
        int gap = segs[k].l - segs[lastArv].r;
        if (!found || gap < bestGap) {
            found = true;
            bestGap = gap;
            bl = segs[lastArv].l;
            br = segs[lastArv].r;
            hl = segs[k].l;
            hr = segs[k].r;
        }
    }

    auto printPairs = [](const vector<pair<int, int>>& v) {
        for (size_t k = 0; k < v.size(); k++) {
            if (k > 0) cout << ' ';
            cout << v[k].first << ' ' << v[k].second;
        }
        if (!v.empty()) cout << "\n";
    };

    cout << arv.size() << "\n";
    printPairs(arv);
    cout << harm.size() << "\n";
    printPairs(harm);
    cout << pairsP.size() << "\n";
    printPairs(pairsP);
    if (found) {
        cout << bl << ' ' << br << ' ' << hl << ' ' << hr << "\n";
    }
    return 0;
}
