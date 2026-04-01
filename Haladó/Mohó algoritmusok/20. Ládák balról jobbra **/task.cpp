/*
Feladat: Balról jobbra haladva a ládákat egymásba rakhatjuk (csak kisebbet nagyobba), cél a végső csomagok számának minimalizálása, és egy konkrét csoportosítás kiírása.
Ötlet: Minden csomaghoz az aktuális „belső” (legkisebb) méretet tartjuk. Új x ládát ahhoz a csomaghoz rakunk, amelynek belső mérete a legkisebb, de még > x. Ha nincs ilyen, új csomag indul.
Hint 1: || Ha x-et túl nagy belső méretű csomagba teszed, az rosszabb lehet a későbbiekre nézve. ||
Hint 2: || A legkisebb még > x belső méret választása ugyanaz a mohó minta, mint „láncokra bontásnál”. ||
Hint 3: || A csoportokba a ládák indexeit a bejárás sorrendjében gyűjtsd, ez lesz a kimenet soraiban. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) cin >> a[i];

    if (N == 0) {
        cout << 0 << '\n';
        return 0;
    }

    multiset<pair<int,int>> inners; // (current smallest size in package, package id)
    vector<vector<int>> groups(1);
    int gCnt = 0;

    for (int i = 1; i <= N; ++i) {
        int x = a[i];
        auto it = inners.upper_bound({x, INT_MAX});
        if (it == inners.end()) {
            ++gCnt;
            groups.push_back({});
            groups[gCnt].push_back(i);
            inners.insert({x, gCnt});
        } else {
            int id = it->second;
            inners.erase(it);
            groups[id].push_back(i);
            inners.insert({x, id});
        }
    }

    cout << gCnt << '\n';
    for (int id = 1; id <= gCnt; ++id) {
        for (int j = 0; j < (int)groups[id].size(); ++j) {
            if (j) cout << ' ';
            cout << groups[id][j];
        }
        cout << '\n';
    }
    return 0;
}
