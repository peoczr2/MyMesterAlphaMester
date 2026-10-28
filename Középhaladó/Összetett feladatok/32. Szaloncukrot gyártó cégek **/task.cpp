/*
Megoldás lényege:
A cégeket és a szaloncukor fajtákat az első előfordulásuk sorrendjében azonosítjuk, így a „több megoldás esetén a bemenetben először előforduló” szabály az azonosító szerinti legkisebb érték kiválasztásával adódik. Cég–fajta páronként a legkisebb árat tároljuk egy mátrixban, amelyből minden kérdés kiszámolható: a legdrágább termék a legnagyobb árú sor, egy fajtát csak egy cég gyárt, ha a cég fajtáinak száma 1, a cégek listája az azonosítók sorrendjében írható ki, a legtöbb céget befoglaló fajta a fajtánkénti cégszám maximuma. Az 5. részfeladatnál fajtánként kiszámoljuk a legkisebb árat, és azt a céget keressük, amelynél minden általa gyártott fajta ára megegyezik ezzel a minimummal. Az idő O(N + C·F), ahol C és F legfeljebb N, így N ≤ 1000 mellett bőven belefér.
*/
/*
Hint 1: || Minden cég–fajta párhoz rendelj egy árat (a legolcsóbbat, ha egy párhoz több sor tartozik). A cégek és a fajták neveit tegyük azonosítóvá az első előfordulás sorrendjében, hogy a döntetlenek kezelése is ezzel egyezzen. ||
Hint 2: || Számold meg cégenként, hány fajtát gyárt, és fajtánként, hány cég gyártja. Az egyetlen fajtát gyártó cég és a legtöbb céget befoglaló fajta ebből kiolvasható, a legdrágább termék pedig a bemenet egyetlen végigolvasásával adódik. ||
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
        cin >> f >> c >> pr[i];
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

    // 1. részfeladat: a legdrágább szaloncukor (fajta és gyártó)
    int expensive = 0;
    for (int i = 1; i < n; ++i)
        if (pr[i] > pr[expensive]) expensive = i;
    cout << "#\n";
    cout << fname[fOf[expensive]] << " " << cname[cOf[expensive]] << "\n";

    // 2. részfeladat: egy cég, amely csak egyféle szaloncukrot gyárt
    int oneKind = -1;
    for (int c = 0; c < C && oneKind == -1; ++c) {
        int cnt = 0;
        for (int f = 0; f < F; ++f)
            if (best[c][f] != INF) cnt++;
        if (cnt == 1) oneKind = c;
    }
    cout << "#\n";
    cout << (oneKind == -1 ? string("NINCS") : cname[oneKind]) << "\n";

    // 3. részfeladat: a szaloncukrot gyártó cégek
    cout << "#\n";
    cout << C << "\n";
    for (int c = 0; c < C; ++c) cout << cname[c] << "\n";

    // 4. részfeladat: a legtöbb cég által gyártott fajta
    int bestF = 0;
    for (int f = 1; f < F; ++f)
        if (compCnt[f] > compCnt[bestF]) bestF = f;
    cout << "#\n";
    cout << fname[bestF] << "\n";

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
