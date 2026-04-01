/*
Megoldas lenyege:
Egy lepes mindig pontosan egy lanc egyetlen kulso elet modositja: vagy levesszuk
egy gyokerdoboz belso lancat, vagy egy szabad egyedul allo dobozt rakunk egy masik
lanc elejere. Ha minden lancot teljesen szetszednenk egyes dobozokra, akkor a kezdeti
allapot minden nem gyoker elehez egy nyitas, a cel allapot minden nem gyoker elehez
egy berakas tartozna.

Ezt akkor lehet csokkenteni, ha egy el egy kozos levél->gyoker prefixben valtozatlanul
megmaradhat. Egy startbeli lancbol csak a legbelso, leveltol indulo prefix maradhat meg,
es ugyanez igaz a celbeli lancra is. Ezert pontosan azok az elek spórolhatók meg,
amelyek valamelyik kozos leveltol felfele haladva mindket allapotban ugyanugy szerepelnek.
Az eredmeny: start_elek + cel_elek - 2 * megmarado_kozos_elek.
*/
/*
Hint 1: || Szamold kulon a kezdeti es a cel allapotban, hany nem gyoker doboz van: ezek az elek. ||
Hint 2: || Egy megmarado resz csak egy kozos leveltol indulhat, mert csak a legbelso lanc maradhat egyben. ||
Hint 3: || A kozos levelektol felfele addig mehetsz, amig a ket allapotban ugyanaz a szulo. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> start(n + 1), target(n + 1);
    for (int i = 1; i <= n; ++i) cin >> start[i];
    for (int i = 1; i <= n; ++i) cin >> target[i];

    vector<int> startChild(n + 1, 0), targetChild(n + 1, 0);
    long long startEdges = 0, targetEdges = 0;
    for (int i = 1; i <= n; ++i) {
        if (start[i] != 0) {
            ++startEdges;
            startChild[start[i]] = i;
        }
        if (target[i] != 0) {
            ++targetEdges;
            targetChild[target[i]] = i;
        }
    }

    long long preservedEdges = 0;
    for (int leaf = 1; leaf <= n; ++leaf) {
        if (startChild[leaf] != 0 || targetChild[leaf] != 0) continue;

        int current = leaf;
        while (start[current] != 0 && start[current] == target[current]) {
            ++preservedEdges;
            current = start[current];
        }
    }

    cout << startEdges + targetEdges - 2 * preservedEdges << '\n';
    return 0;
}
