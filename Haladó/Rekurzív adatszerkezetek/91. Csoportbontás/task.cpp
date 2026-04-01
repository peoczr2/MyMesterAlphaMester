/*
Megoldási ötlet:
Egy csúcs törlése után a keletkező komponensek közül minden gyerek-részfa fizikai munkásainak száma változatlan,
és az „felső” komponensben csak az eltávolított csúcs közvetlen főnöke változhat levéllé, ha neki már nem marad más
beosztottja.

Ezért elegendő minden csúcsra kiszámítani a részfájának levélszámát. Törléskor a komponensek levélszáma a gyerekek
részfáinak levélszámaiból és a felső komponens levélszámából áll össze. Olyan csúcsot keresünk, ahol legalább K
komponens van, és ezek minimuma a lehető legnagyobb.
*/
/*
Hint 1: || A gyerek-részfák levélszáma törléskor nem változik. ||
Hint 2: || Az upper komponensben csak az eltávolított csúcs főnöke válhat új levéllé. ||
Hint 3: || A válaszhoz elég a részfák levélszáma és a fokszámok ismerete. ||
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
        int boss, employee;
        cin >> boss >> employee;
        children[boss].push_back(employee);
        parent[employee] = boss;
    }

    vector<int> order;
    order.reserve(n);
    vector<int> stack = {1};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (int child : children[node]) stack.push_back(child);
    }

    vector<int> leafCount(n + 1, 0);
    for (int idx = n - 1; idx >= 0; --idx) {
        int node = order[idx];
        if (children[node].empty()) leafCount[node] = 1;
        else {
            for (int child : children[node]) leafCount[node] += leafCount[child];
        }
    }

    int bestNode = 1;
    int bestValue = -1;
    for (int node = 1; node <= n; ++node) {
        int components = static_cast<int>(children[node].size()) + (node == 1 ? 0 : 1);
        if (components < k) continue;
        int upperLeaves = 0;
        if (node != 1) {
            upperLeaves = leafCount[1] - leafCount[node];
            if (static_cast<int>(children[parent[node]].size()) == 1) ++upperLeaves;
        }
        int minLeaves = upperLeaves;
        for (int child : children[node]) minLeaves = min(minLeaves, leafCount[child]);
        if (bestValue < minLeaves) {
            bestValue = minLeaves;
            bestNode = node;
        }
    }

    cout << bestNode << ' ' << bestValue << '\n';
    return 0;
}
