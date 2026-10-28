/*
Megoldás lényege:
A témákat visszalépéses kereséssel osztjuk szekciókba. Először az előadások
száma szerint csökkenő sorrendbe rendezzük a témákat, majd sorban elhelyezzük
őket: minden témát az első olyan szekcióba teszünk, ahová még elfér. Ha egy téma
egyik szekcióba sem fér, visszalépünk. Azonos szabad hellyel rendelkező
szekciók felcserélhetők, ezért közülük csak az elsőt próbáljuk ki. Egy téma
előadásai így automatikusan egymás után, ugyanabban a szekcióban állnak. A
kiíráskor a szekciókat sorban adjuk ki.
*/
/*
Hint 1: || Minden téma teljes egészében egyetlen szekcióba kerül, így a feladat a témák szekciókba pakolása, ahol minden szekcióba pontosan L előadás jut. ||
Hint 2: || Ha egy állapot (a még hátralévő témák és a szekciók szabad helyei) zsákutcának bizonyult, tároljuk el, és később ne számoljuk újra. ||
Hint 3: || Ha két szekciónak ugyanannyi szabad helye van, a közöttük lévő választás nem számít, így csak az egyiket próbáld ki. ||
*/

#include <bits/stdc++.h>
using namespace std;

int k, l, n;
vector<string> nev;
vector<int> db;
vector<int> marad;
vector<vector<int>> csoportok;
unordered_set<long long> zsakutca;

long long allapot_kulcs(int idx) {
    vector<int> m = marad;
    sort(m.begin(), m.end());
    long long kod = 0;
    for (int x : m) kod = kod * (l + 1) + x;
    return kod * (n + 1) + idx;
}

bool dfs(int idx) {
    if (idx == n) return true;
    long long kulcs = allapot_kulcs(idx);
    if (zsakutca.count(kulcs)) return false;
    bool probalt[11] = {};
    for (int s = 0; s < k; ++s) {
        if (marad[s] < db[idx] || probalt[marad[s]]) continue;
        probalt[marad[s]] = true;
        marad[s] -= db[idx];
        csoportok[s].push_back(idx);
        if (dfs(idx + 1)) return true;
        csoportok[s].pop_back();
        marad[s] += db[idx];
    }
    zsakutca.insert(kulcs);
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> l >> n;
    vector<string> be_nev(n);
    vector<int> be_db(n);
    for (int i = 0; i < n; ++i) cin >> be_nev[i] >> be_db[i];

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    stable_sort(ord.begin(), ord.end(), [&](int a, int b) { return be_db[a] > be_db[b]; });
    nev.resize(n);
    db.resize(n);
    for (int i = 0; i < n; ++i) {
        nev[i] = be_nev[ord[i]];
        db[i] = be_db[ord[i]];
    }

    marad.assign(k, l);
    csoportok.assign(k, {});
    dfs(0);

    for (int s = 0; s < k; ++s) {
        bool elso = true;
        for (int idx : csoportok[s]) {
            for (int rep = 0; rep < db[idx]; ++rep) {
                if (!elso) cout << ' ';
                cout << nev[idx];
                elso = false;
            }
        }
        cout << '\n';
    }
    return 0;
}
