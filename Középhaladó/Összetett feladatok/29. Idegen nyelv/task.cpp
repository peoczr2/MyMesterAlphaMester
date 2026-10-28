/*
Megoldás lényege:
Minden dolgozóhoz eltároljuk az általa beszélt nyelvek azonosítóinak rendezett, ismétlésmentes listáját. A nyelvneveket egész azonosítókra képezzük le az első előfordulásuk sorrendjében, így döntetlennél a kisebb azonosító a bemenetben korábbi nyelvet jelent. Két dolgozó akkor kerülhet ugyanabba a csoportba, ha a nyelvlistájuk pontosan egyezik, ezért a csoportok száma a különböző, nem üres nyelvlisták számával egyenlő. Minden részfeladat egy-két végigjárással megoldható, a rendezés miatt az összidő O(M log M).
*/
/*
Hint 1: || A csoportok azonosak a dolgozók nyelvhalmaza alapján: az 5. részfeladatban a különböző nyelvhalmazok számát kell megtalálni. ||
Hint 2: || Nyelvneveket képezz egész azonosítókra (pl. unordered_map), dolgozónként gyűjtsd az azonosítókat, majd rendezéssel és unique-kel szűrd ki az ismétlődő (dolgozó, nyelv) párokat. ||
Hint 3: || A nyelvenként megszámolt dolgozók (cnt tömb) adják a 3. részfeladatot: a legnagyobb számlálóhoz tartozó nyelv kell, és döntetlennél a kisebb azonosító (vagyis a korábbi előfordulás) nyer. Az 5. részfeladatnál a nyelvlisták szerint sorba rendezett dolgozók közül a különböző listák darabszáma adja a választ. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    unordered_map<string, int> langId;
    vector<string> langName;
    vector<vector<int>> speaks(n + 1);

    for (int k = 0; k < m; ++k) {
        int h;
        string nyelv;
        cin >> h >> nyelv;
        auto it = langId.find(nyelv);
        int id;
        if (it == langId.end()) {
            id = (int)langName.size();
            langId.emplace(nyelv, id);
            langName.push_back(nyelv);
        } else {
            id = it->second;
        }
        speaks[h].push_back(id);
    }

    for (auto& v : speaks) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    // 1. részfeladat: a beszélt nyelvek száma
    cout << "#\n";
    cout << langName.size() << "\n";

    // 2. részfeladat: dolgozónként a nyelvek száma
    cout << "#\n";
    for (int i = 1; i <= n; ++i) {
        if (!speaks[i].empty()) cout << i << " " << speaks[i].size() << "\n";
    }

    // 3. részfeladat: a legtöbb dolgozó által beszélt nyelv
    vector<int> cnt(langName.size(), 0);
    for (int i = 1; i <= n; ++i)
        for (int id : speaks[i]) cnt[id]++;
    int best = -1;
    for (int id = 0; id < (int)cnt.size(); ++id)
        if (best == -1 || cnt[id] > cnt[best]) best = id;
    cout << "#\n";
    if (best != -1) cout << langName[best] << "\n";

    // 4. részfeladat: egy dolgozó, aki egy nyelven sem beszél
    cout << "#\n";
    int silent = -1;
    for (int i = 1; i <= n; ++i) {
        if (speaks[i].empty()) {
            silent = i;
            break;
        }
    }
    cout << silent << "\n";

    // 5. részfeladat: a csoportok száma (azonos nyelvlista = azonos csoport)
    vector<int> workers;
    for (int i = 1; i <= n; ++i)
        if (!speaks[i].empty()) workers.push_back(i);
    sort(workers.begin(), workers.end(),
         [&](int a, int b) { return speaks[a] < speaks[b]; });
    int groupCount = 0;
    for (size_t k = 0; k < workers.size(); ++k)
        if (k == 0 || speaks[workers[k]] != speaks[workers[k - 1]]) ++groupCount;
    cout << "#\n";
    cout << groupCount << "\n";
    return 0;
}
