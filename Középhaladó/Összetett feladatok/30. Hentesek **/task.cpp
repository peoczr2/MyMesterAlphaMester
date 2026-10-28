/*
Megoldás lényege:
Minden húsfajtához az első bemenetbeli előfordulása szerinti azonosítót rendeljük, és hentesenként eltároljuk az általa árult fajták rendezett, ismétlésmentes listáját. Fajtánként megszámoljuk, hány hentes árulja, ebből adódik a fajták száma, az egyedül árult fajta (a bemenetben első ilyen) és a kiírandó darabszámok. A legtöbb fajtát áruló hentest a listahossz maximumával keressük, döntetlennél a kisebb sorszám marad. A nagykereskedők száma az egyforma, nem üres fajtahalmazok darabszámával egyezik, amit a listák rendezésével és szomszédos összevetésével kapunk; az összidő O(A log A).
*/
/*
Hint 1: || Egy hentes húsfélékből álló halmaza határozza meg, kitől vásárol: ugyanazt a halmazt árulók ugyanattól a nagykereskedőtől kapják a húst, így az 5. részfeladatban a különböző halmazok számát kell megtalálni. ||
Hint 2: || Húsfajtákat képezz egész azonosítókra (pl. unordered_map), hentesenként gyűjtsd az azonosítókat, majd rendezéssel és unique-kel szűrd ki az ismétlődéseket. ||
Hint 3: || Fajtánként számold meg, hány hentes árulja (cnt tömb): ebből jön a fajták száma, az egyedül árult fajta és a darabszámok. A legtöbb fajtát áruló hentest a listahossz maximumával keresd, és döntetlennél a kisebb sorszámot tartsd meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, a;
    cin >> n >> a;

    unordered_map<string, int> meatId;
    vector<string> meatName;
    vector<vector<int>> sells(n + 1);

    for (int k = 0; k < a; ++k) {
        string hus;
        int h;
        cin >> hus >> h;
        auto it = meatId.find(hus);
        int id;
        if (it == meatId.end()) {
            id = (int)meatName.size();
            meatId.emplace(hus, id);
            meatName.push_back(hus);
        } else {
            id = it->second;
        }
        sells[h].push_back(id);
    }

    for (auto& v : sells) {
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
    }

    vector<int> cnt(meatName.size(), 0);
    for (int i = 1; i <= n; ++i)
        for (int id : sells[i]) cnt[id]++;

    // 1. részfeladat: a húsfélék száma
    cout << "#\n";
    cout << meatName.size() << "\n";

    // 2. részfeladat: egy olyan hús, amit csak egy hentes árul
    cout << "#\n";
    int single = -1;
    for (int id = 0; id < (int)cnt.size(); ++id) {
        if (cnt[id] == 1) {
            single = id;
            break;
        }
    }
    if (single == -1) cout << "NINCS\n";
    else cout << meatName[single] << "\n";

    // 3. részfeladat: húsféleségenként a hentesek száma
    cout << "#\n";
    for (int id = 0; id < (int)cnt.size(); ++id)
        cout << meatName[id] << " " << cnt[id] << "\n";

    // 4. részfeladat: a legtöbb húsfélét áruló hentes (legkisebb sorszám)
    cout << "#\n";
    int bestButcher = 1;
    for (int i = 2; i <= n; ++i)
        if (sells[i].size() > sells[bestButcher].size()) bestButcher = i;
    cout << bestButcher << "\n";

    // 5. részfeladat: a nagykereskedők száma (azonos fajtahalmaz = azonos nagykereskedő)
    vector<int> butchers;
    for (int i = 1; i <= n; ++i)
        if (!sells[i].empty()) butchers.push_back(i);
    sort(butchers.begin(), butchers.end(),
         [&](int a, int b) { return sells[a] < sells[b]; });
    int wholesalers = 0;
    for (size_t k = 0; k < butchers.size(); ++k)
        if (k == 0 || sells[butchers[k]] != sells[butchers[k - 1]]) ++wholesalers;
    cout << "#\n";
    cout << wholesalers << "\n";
    return 0;
}
