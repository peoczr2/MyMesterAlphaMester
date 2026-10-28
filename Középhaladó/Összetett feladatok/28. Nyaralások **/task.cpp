/*
Megoldás lényege:
Minden tanulóhoz eltároljuk a nyaralási helyei azonosítóinak rendezett, ismétlésmentes listáját. A helyneveket egész azonosítókra képezzük le az első előfordulásuk sorrendjében, így döntetlennél a kisebb azonosító a bemenetben korábbi helyet jelent. Két tanuló akkor kerülhet ugyanabba a csoportba, ha a helylistájuk pontosan egyezik, ezért a csoportok száma a különböző, nem üres helylisták számával egyenlő. Minden részfeladat egy-két végigjárással megoldható, a rendezés miatt az összidő O(Ny log Ny).
*/
/*
Hint 1: || A csoportok azonosak a tanulók helyhalmaza alapján: az 5. részfeladatban a különböző helyhalmazok számát kell megtalálni. ||
Hint 2: || Helyneveket képezz egész azonosítókra (pl. unordered_map), tanulónként gyűjtsd az azonosítókat, majd rendezéssel és unique-kel szűrd ki az ismétlődő (tanuló, hely) párokat. ||
Hint 3: || A helyenként megszámolt tanulók (cnt tömb) adják a 3. részfeladatot: a legnagyobb számlálóhoz tartozó hely kell, és döntetlennél a kisebb azonosító (vagyis a korábbi előfordulás) nyer. Az 5. részfeladatnál a rendezett helylisták szerint sorba rendezett tanulók közül a különböző listák darabszáma adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, ny;
    cin >> t >> ny;

    unordered_map<string, int> placeId;
    vector<string> placeName;
    vector<vector<int>> visits(t + 1);

    for (int k = 0; k < ny; ++k) {
        int s;
        string h;
        cin >> s >> h;
        auto it = placeId.find(h);
        int id;
        if (it == placeId.end()) {
            id = (int)placeName.size();
            placeId.emplace(h, id);
            placeName.push_back(h);
        } else {
            id = it->second;
        }
        visits[s].push_back(id);
    }

    for (auto& v : visits) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    // 1. részfeladat: a helyek száma
    cout << "#\n";
    cout << placeName.size() << "\n";

    // 2. részfeladat: tanulónként a helyek száma
    cout << "#\n";
    for (int i = 1; i <= t; ++i) {
        if (!visits[i].empty()) cout << i << " " << visits[i].size() << "\n";
    }

    // 3. részfeladat: a legtöbb tanuló által látogatott hely
    vector<int> cnt(placeName.size(), 0);
    for (int i = 1; i <= t; ++i)
        for (int p : visits[i]) cnt[p]++;
    int best = -1;
    for (int p = 0; p < (int)cnt.size(); ++p)
        if (best == -1 || cnt[p] > cnt[best]) best = p;
    cout << "#\n";
    if (best != -1) cout << placeName[best] << "\n";

    // 4. részfeladat: egy tanuló, aki sehol sem nyaralt
    cout << "#\n";
    int nowhere = -1;
    for (int i = 1; i <= t; ++i) {
        if (visits[i].empty()) {
            nowhere = i;
            break;
        }
    }
    cout << nowhere << "\n";

    // 5. részfeladat: a csoportok száma (azonos helylista = azonos csoport)
    vector<int> students;
    for (int i = 1; i <= t; ++i)
        if (!visits[i].empty()) students.push_back(i);
    sort(students.begin(), students.end(),
         [&](int a, int b) { return visits[a] < visits[b]; });
    int groupCount = 0;
    for (size_t k = 0; k < students.size(); ++k)
        if (k == 0 || visits[students[k]] != visits[students[k - 1]]) ++groupCount;
    cout << "#\n";
    cout << groupCount << "\n";
    return 0;
}
