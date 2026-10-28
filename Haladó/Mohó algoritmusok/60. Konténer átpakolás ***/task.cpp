/*
Megoldás lényege:
A 59. feladat számlálásának döntéseit követjük, de most a mozgatásokat is rögzítjük. Minden konténer vagy a helyén marad (saját torony alja), vagy egy jobbra lévő, befogadó toronyba mozog, és így egy szabad hely keletkezik. A célpozíciókat jobbról balra haladva választjuk: saját torony esetén a méretnél nagyobb tornyok közül a következő még szabadot, szabad torony esetén az első olyan tornyot, amelyben az adott méret még nem szerepel. Egy torony alját csak akkor lehet betölteni, ha a korábbi tartalmát már kiürítettük, ezért a mozgatásokat fába rendezzük (a szülő a célpozíció), és a gyerekeket méret szerint csökkenő sorrendben, mélységi bejárással írjuk ki. Az időigény O(N log N).
*/
/*
Hint 1: || A mozgatások mindig jobbra mennek, ezért minden konténer legfeljebb egyszer mozog, és a célhelye tőle jobbra van. ||
Hint 2: || Egy toronyban a méretek felfelé egyre kisebbek; a jobbról balra haladó döntések így csak a méretek előfordulásától függenek. ||
Hint 3: || Egy torony alját csak akkor lehet betölteni, ha a konténer korábban onnan kiment; ezért a szülő mozgatását a gyerekei előtt kell kiírni. ||
Hint 4: || Egy torony gyerekeit méret szerint csökkenően kell kiírni, különben a tetejénél nagyobb elem rakódna rá. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    long long k;
    cin >> n >> k;
    vector<long long> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<long long> caps;          // saját tornyok alja (pozíció szerint), növekvő
    vector<int> ownPos;              // a saját tornyok pozíciója
    map<long long, int> jOwn;        // saját toronyba került azonos méretek száma
    vector<int> freeList;            // nem üres szabad tornyok pozíciója
    vector<int> emptyStack;          // felszabadult, még üres pozíciók
    unordered_set<unsigned long long> inFree; // (szabad torony sorszáma, méret) párok
    map<long long, int> ptrFree;     // szabad tornyok keresési mutatója méretenként
    map<long long, int> cntFree;     // szabad toronyba került azonos méretek száma
    vector<int> parent(n + 1, 0);    // a konténer célpozíciója
    vector<char> vacated(n + 1, 0);

    auto key = [](size_t idx, long long v) {
        return ((unsigned long long)idx << 28) | (unsigned long long)v;
    };

    for (int p = n; p >= 1; --p) {
        long long v = a[p];
        int greater = (int)(caps.end() - upper_bound(caps.begin(), caps.end(), v));
        if (greater > jOwn[v]) {
            // saját torony: a v-edik (0-tól) nagyobb alj következő még szabad tornyába
            size_t idx = (size_t)(upper_bound(caps.begin(), caps.end(), v) - caps.begin()) + jOwn[v];
            jOwn[v]++;
            parent[p] = ownPos[idx];
            vacated[p] = 1;
            emptyStack.push_back(p);
            continue;
        }
        if ((long long)freeList.size() > cntFree[v]) {
            int &ptr = ptrFree[v];
            size_t i = (size_t)ptr;
            while (inFree.count(key(i, v))) ++i;
            inFree.insert(key(i, v));
            cntFree[v]++;
            ptr = (int)i + 1;
            parent[p] = freeList[i];
            vacated[p] = 1;
            emptyStack.push_back(p);
            continue;
        }
        if (!emptyStack.empty()) {
            int j = emptyStack.back();
            emptyStack.pop_back();
            freeList.push_back(j);
            inFree.insert(key(freeList.size() - 1, v));
            cntFree[v]++;
            parent[p] = j;
            vacated[p] = 1;
            emptyStack.push_back(p);
            continue;
        }
        caps.push_back(v);
        ownPos.push_back(p);
    }

    // a mozgatások fája: minden mozgó konténer szülője a célpozíció
    vector<vector<int>> ch(n + 1);
    for (int x = 1; x <= n; ++x) if (vacated[x]) ch[parent[x]].push_back(x);
    for (auto &c : ch) sort(c.begin(), c.end(), [&](int x, int y) { return a[x] > a[y]; });

    // bejárás: a célpozícióba érkezők méret szerint csökkenően, a szülő áthelyezése után
    vector<pair<int,int>> out;
    vector<pair<int,size_t>> st;
    for (int r : ownPos) {
        st.push_back({r, 0});
        while (!st.empty()) {
            int s = st.back().first;
            size_t idx = st.back().second;
            if (idx == ch[s].size()) { st.pop_back(); continue; }
            st.back().second++;
            int x = ch[s][idx];
            out.push_back({x, s});
            st.push_back({x, 0});
        }
    }

    cout << out.size() << '\n';
    for (auto [i, j] : out) cout << i << ' ' << j << '\n';
    return 0;
}
