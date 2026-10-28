/*
Megoldás lényege:
A cégeket és a szaloncukor fajtákat az első előfordulásuk sorrendjében azonosítjuk, így a „több megoldás esetén a bemenetben először előforduló” szabály az azonosító szerinti legkisebb érték választásával adódik. Cég–fajta páronként a legkisebb árat tároljuk egy mátrixban, amelyből minden kérdés közvetlenül kiszámolható: a legolcsóbb termék a legkisebb árú sor, egy cég által gyártott fajta az, amelyhez egyetlen cég tartozik, a fajták listája az azonosítók sorrendjében írható ki, a legtöbb fajtát gyártó cég a sorok nem üres elemszámainak maximuma. Az 5. részfeladatnál fajtánként kiszámoljuk a legkisebb árat, és azt a céget keressük, amelynél minden általa gyártott fajta ára megegyezik ezzel a minimummal. Az idő O(N + C·F), ahol C és F legfeljebb N, így N ≤ 1000 mellett bőven belefér.
*/
/*
Hint 1: || Minden cég–fajta párhoz rendelj egy árat (a legolcsóbbat, ha egy párhoz több sor tartozik). A cégek és a fajták neveit tegyük azonosítóvá az első előfordulás sorrendjében, hogy a döntetlenek kezelése is ezzel egyezzen. ||
Hint 2: || Számold meg fajtánként, hány cég gyártja, és cégenként, hány fajtát gyárt. Az egyedül gyártott fajta és a legtöbb fajtát gyártó cég ebből már kiolvasható, a legolcsóbb termék pedig a bemenet egyetlen végigolvasásával adódik. ||
Hint 3: || Az 5. részfeladathoz fajtánként keresd meg a legkisebb árat. Egy cég akkor jó, ha minden általa gyártott fajtánál az ára megegyezik ezzel a minimummal, és ilyen cégből az azonosító szerint elsőt kell kiírni. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> cOf(n), fOf(n), pr(n);
    vector<string> cname, fname;
    unordered_map<string, int> cid, fid;

    for (int i = 0; i < n; ++i) {
        string c, f;
        cin >> c >> f >> pr[i];
        auto ic = cid.find(c);
        if (ic == cid.end()) {
            cOf[i] = (int)cname.size();
            cid.emplace(c, cOf[i]);
            cname.push_back(c);
        } else {
            cOf[i] = ic->second;
        }
        auto itf = fid.find(f);
        if (itf == fid.end()) {
            fOf[i] = (int)fname.size();
            fid.emplace(f, fOf[i]);
            fname.push_back(f);
        } else {
            fOf[i] = itf->second;
        }
    }

    const int C = (int)cname.size();
    const int F = (int)fname.size();
    const int INF = INT_MAX;

    vector<vector<int>> best(C, vector<int>(F, INF));
    for (int i = 0; i < n; ++i)
        best[cOf[i]][fOf[i]] = min(best[cOf[i]][fOf[i]], pr[i]);

    vector<int> minF(F, INF), compCnt(F, 0);
    for (int c = 0; c < C; ++c)
        for (int f = 0; f < F; ++f)
            if (best[c][f] != INF) {
                minF[f] = min(minF[f], best[c][f]);
                compCnt[f]++;
            }

    // 1. részfeladat: a legolcsóbb szaloncukor (fajta és gyártó)
    int cheap = 0;
    for (int i = 1; i < n; ++i)
        if (pr[i] < pr[cheap]) cheap = i;
    cout << "#\n";
    cout << fname[fOf[cheap]] << " " << cname[cOf[cheap]] << "\n";

    // 2. részfeladat: egy fajta, amelyet csak egy cég gyárt
    int single = -1;
    for (int i = 0; i < n; ++i)
        if (compCnt[fOf[i]] == 1) {
            single = fOf[i];
            break;
        }
    cout << "#\n";
    cout << (single == -1 ? string("NINCS") : fname[single]) << "\n";

    // 3. részfeladat: a boltban kapható fajták
    cout << "#\n";
    cout << F << "\n";
    for (int f = 0; f < F; ++f) cout << fname[f] << "\n";

    // 4. részfeladat: a legtöbb fajtát gyártó cég
    int bestC = 0, bestCnt = -1;
    for (int c = 0; c < C; ++c) {
        int cnt = 0;
        for (int f = 0; f < F; ++f)
            if (best[c][f] != INF) cnt++;
        if (cnt > bestCnt) {
            bestCnt = cnt;
            bestC = c;
        }
    }
    cout << "#\n";
    cout << cname[bestC] << "\n";

    // 5. részfeladat: olyan cég, amelynél minden fajta a legolcsóbb
    int good = -1;
    for (int c = 0; c < C && good == -1; ++c) {
        bool ok = true;
        for (int f = 0; f < F && ok; ++f)
            if (best[c][f] != INF && best[c][f] != minF[f]) ok = false;
        if (ok) good = c;
    }
    cout << "#\n";
    cout << (good == -1 ? string("NINCS") : cname[good]) << "\n";

    return 0;
}
