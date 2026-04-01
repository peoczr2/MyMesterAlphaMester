/*
Megoldási ötlet:
Az 1-es személy a közös ős. A legtávolabbi leszármazottak azok, amelyeknek a gyökértől mért mélysége maximális.

Mivel minden csúcsnak ismert az apja, elég egy mélységszámítás. Ezután megszámoljuk a legnagyobb mélységű csúcsokat,
és növekvő sorrendben kiírjuk őket.
*/
/*
Hint 1: || A legtávolabbi leszármazottak egyszerűen a legnagyobb mélységű csúcsok. ||
Hint 2: || A mélységet a szülők láncán végiglépkedve vagy egy gyökérből induló bejárással is megkaphatod. ||
Hint 3: || A második sorba csak azokat kell kiírni, akiknek a mélysége eléri a maximumot. ||
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    for (int node = 2; node <= n; ++node) {
        int parent;
        cin >> parent;
        children[parent].push_back(node);
    }

    vector<int> depth(n + 1, 0), result;
    int maxDepth = 0;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        maxDepth = max(maxDepth, depth[node]);
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            q.push(child);
        }
    }

    for (int node = 1; node <= n; ++node) {
        if (depth[node] == maxDepth) {
            result.push_back(node);
        }
    }

    cout << result.size() << ' ' << maxDepth << '\n';
    for (int i = 0; i < static_cast<int>(result.size()); ++i) {
        if (i > 0) cout << ' ';
        cout << result[i];
    }
    cout << '\n';
    return 0;
}