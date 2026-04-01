#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A bemenetben minden ismert személyhez megkapjuk az apja és az anyja sorszámát.
Ebből közvetlenül meg tudjuk határozni a keresett személy testvéreit,
féltestvéreit, apai ágon a férfiági felmenőit, valamint az első unokatestvéreit.

Testvérek: ugyanaz az apa és ugyanaz az anya, a keresett személy nélkül.
Féltestvérek: pontosan az egyik szülő közös, de nem testvérek.
Férfiági felmenők: ismételten az apa mezőt követjük.
Első unokatestvérek: akiknek a szülői között van olyan, akinek a szülői
megegyeznek a keresett személy valamelyik nagyszülőjével.

Hint 1: || A feladat központi adatai az apa és az anya táblák; ezekből minden kérdés lokálisan eldönthető. ||
Hint 2: || A testvér és féltestvér halmazt úgy érdemes előállítani, hogy végignézed az összes személyt, és a szülőpárjukat hasonlítod. ||
Hint 3: || Az első unokatestvérhez először gyűjtsd ki a keresett személy nagyszülőit, majd keresd meg azokat, akik ezek valamelyikének gyermekei. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<int> father(N + 1, 0), mother(N + 1, 0);
    for (int i = 0; i < M; ++i) {
        int self, dad, mom;
        cin >> self >> dad >> mom;
        father[self] = dad;
        mother[self] = mom;
    }

    vector<int> siblings, halfSiblings, paternal;
    for (int i = 1; i <= N; ++i) {
        if (i == K) continue;
        bool sameFather = father[i] != 0 && father[i] == father[K];
        bool sameMother = mother[i] != 0 && mother[i] == mother[K];
        if (sameFather && sameMother) {
            siblings.push_back(i);
        } else if (sameFather || sameMother) {
            halfSiblings.push_back(i);
        }
    }

    int cur = father[K];
    while (cur != 0) {
        paternal.push_back(cur);
        cur = father[cur];
    }

    set<int> cousins;
    auto addChildrenOfParentSiblings = [&](int parent) {
        if (!parent) return;
        for (int s = 1; s <= N; ++s) {
            if (s == parent) continue;
            bool shareFather = father[s] != 0 && father[s] == father[parent];
            bool shareMother = mother[s] != 0 && mother[s] == mother[parent];
            if (!shareFather && !shareMother) continue;
            for (int child = 1; child <= N; ++child) {
                if (father[child] == s || mother[child] == s) {
                    if (child == K) continue;
                    if (father[child] == father[K] && mother[child] == mother[K]) continue;
                    if ((father[child] == father[K] && father[K] != 0) || (mother[child] == mother[K] && mother[K] != 0)) continue;
                    cousins.insert(child);
                }
            }
        }
    };
    addChildrenOfParentSiblings(father[K]);
    addChildrenOfParentSiblings(mother[K]);

    cout << siblings.size();
    for (int x : siblings) cout << ' ' << x;
    cout << '\n';

    cout << halfSiblings.size();
    for (int x : halfSiblings) cout << ' ' << x;
    cout << '\n';

    cout << paternal.size();
    for (int x : paternal) cout << ' ' << x;
    cout << '\n';

    cout << cousins.size();
    for (int x : cousins) cout << ' ' << x;
    cout << '\n';
    return 0;
}