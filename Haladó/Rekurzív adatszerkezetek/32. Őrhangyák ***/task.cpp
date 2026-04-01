/*
Megoldási ötlet:
Az inputban az ágak irányítottak: az A csomópontból a B csomópont felé vezetnek a levelek irányába,
tehát a fa gyökere az a csomópont, amelynek nincs szülője. Egy őrhangya a saját csomópontjától lefelé
nem megy, csak a leszármazottai felé tud őrizni legfeljebb K él távolságig. Emiatt minden él
(szülő, gyerek) akkor őrzött, ha a gyereknek van legfeljebb K távolságra levő őr-őse.

A gyökér minden, alatta induló ághoz az egyetlen lehetséges őrhely, ezért ha van legalább egy él,
a gyökérre biztosan kell őr. Ezután a csúcsokat mélység szerint csökkenő sorrendben feldolgozzuk.
Ha egy csúcs bejövő éle még nincs őrizve, akkor a csúcs K-adik ősére kell őrt tenni (ha nincs ilyen,
akkor a gyökérre). Ez a lehető legmagasabb olyan őrhely, amely még lefedi ezt az élet, ezért mohón
optimális, és a mélyebb ágakon egyszerre minél több élet fed le.
*/
/*
Hint 1: || A fa gyökere az a csúcs, amely soha nem szerepel a második oszlopban. ||
Hint 2: || Egy él őrzéséhez nem elég, ha a gyerekcsúcsra teszel őrt, mert az őr onnan lefelé már nem mászik. ||
Hint 3: || A legmélyebb még őrizetlen élre mindig a lehetséges legmagasabb, még megfelelő ősre érdemes őrt tenni. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int from, to;
        cin >> from >> to;
        children[from].push_back(to);
        parent[to] = from;
    }

    int root = 1;
    for (int node = 1; node <= n; ++node) {
        if (parent[node] == 0) {
            root = node;
            break;
        }
    }

    vector<int> depth(n + 1, 0);
    vector<int> order = {root};
    for (size_t i = 0; i < order.size(); ++i) {
        int node = order[i];
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            order.push_back(child);
        }
    }

    vector<int> byDepth = order;
    sort(byDepth.begin(), byDepth.end(), [&](int left, int right) {
        if (depth[left] != depth[right]) {
            return depth[left] > depth[right];
        }
        return left < right;
    });

    vector<char> hasGuard(n + 1, false);
    int answer = 0;
    if (!children[root].empty()) {
        hasGuard[root] = true;
        answer = 1;
    }

    auto edgeCovered = [&](int node) {
        int current = parent[node];
        int distance = 1;
        while (current != 0 && distance <= k) {
            if (hasGuard[current]) {
                return true;
            }
            current = parent[current];
            ++distance;
        }
        return false;
    };

    for (int node : byDepth) {
        if (node == root) {
            continue;
        }
        if (edgeCovered(node)) {
            continue;
        }

        int guard = node;
        int steps = k;
        while (steps > 0 && parent[guard] != 0) {
            guard = parent[guard];
            --steps;
        }
        if (!hasGuard[guard]) {
            hasGuard[guard] = true;
            ++answer;
        }
    }

    cout << answer << '\n';
    return 0;
}