/*
Megoldás lényege:
Minden gyermektelen szigetlakóra visszafelé, a szülőkön keresztül bejárjuk az összes ősét, és minden emberhez
feljegyezzük, hány gyermektelen személynek őse. Egy ember pontosan akkor közös ős, ha ez a szám megegyezik a
gyermektelenek számával. Egy gyermektelen bejárása alatt egy őst csak egyszer számolunk, ezt egy jelöléses tömbbel
biztosítjuk. Mivel a kapcsolatok körmentesek, a bejárás véges. Az időigény O(G·A), ahol G a gyermektelenek száma,
A pedig egy-egy személy őseinek száma, így legrosszabb esetben is O(N²) nagyságrendű.
*/
/*
Hint 1: || Egy ember pontosan akkor közös ős, ha minden gyermektelen személynek őse. Számold meg, hány gyermektelen személynek őse az egyes emberek! ||
Hint 2: || Egy ember ősei a szülőkön keresztül, visszafelé haladva érhetők el, ehhez egy egyszerű bejárás (verem vagy sor) elég. Vigyázz, hogy egy őst egy gyermektelen bejárásán belül csak egyszer számolj! ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> parents(n + 1);
    vector<bool> hasChild(n + 1, false);
    for (int i = 0; i < m; ++i) {
        int child, p1, p2;
        cin >> child >> p1 >> p2;
        parents[child] = {p1, p2};
        hasChild[p1] = true;
        hasChild[p2] = true;
    }

    vector<int> childless;
    for (int v = 1; v <= n; ++v) {
        if (!hasChild[v]) {
            childless.push_back(v);
        }
    }
    if (childless.empty()) {
        cout << 0 << "\n";
        return 0;
    }

    // cnt[v]: hány gyermektelen személynek v az őse; mark: a legutóbbi bejárás azonosítója
    vector<int> cnt(n + 1, 0), mark(n + 1, 0);
    vector<int> stack;
    for (size_t idx = 0; idx < childless.size(); ++idx) {
        int stamp = static_cast<int>(idx) + 1;
        stack.assign(1, childless[idx]);
        mark[childless[idx]] = stamp;
        while (!stack.empty()) {
            int v = stack.back();
            stack.pop_back();
            for (int p : parents[v]) {
                if (mark[p] != stamp) {
                    mark[p] = stamp;
                    ++cnt[p];
                    stack.push_back(p);
                }
            }
        }
    }

    int g = static_cast<int>(childless.size());
    vector<int> common;
    for (int v = 1; v <= n; ++v) {
        if (cnt[v] == g) {
            common.push_back(v);
        }
    }

    if (common.empty()) {
        cout << 0 << "\n";
        return 0;
    }
    cout << common.size() << "\n";
    for (size_t i = 0; i < common.size(); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << common[i];
    }
    cout << "\n";
    return 0;
}
