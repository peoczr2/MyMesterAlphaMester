/*
Megoldási ötlet:
Az inputban egy él azt mondja meg, hogy egy lónak ki az egyik szülője. Ha a gráfot a szülőtől a gyerek
felé irányítjuk, akkor egy irányított körmentes gráfot kapunk. Ebben:
1. egy ős többszörös őse az L lónak pontosan akkor, ha az őstől L-be egynél több különböző út vezet;
2. egy ló annyi leszármazási úton szerepel, ahány út vezet hozzá valamely forrástól szorozva azzal,
   ahány út vezet tőle valamely levélig.
Ezért topologikus sorrendben kiszámítjuk a forrásoktól induló útszámokat, fordított topologikus sorrendben
pedig a levelek felé vezető útszámokat, valamint külön az L-hez vezető útszámokat is.
*/
/*
Hint 1: || A szülő-gyerek kapcsolatokat érdemes a szülőtől a gyerek felé irányítani, mert így a leszármazási utak természetes irányba mennek. ||
Hint 2: || Egy csúcsból az L lóba vezető utak száma a gyerekeiből az L-be vezető utak összege. ||
Hint 3: || A teljes DAG-ban egy csúcson áthaladó leszármazási utak száma = (forrásból odáig vezető utak száma) * (onnan levélig vezető utak száma). ||
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> children(n + 1);
    vector<vector<int>> parents(n + 1);
    vector<int> indegree(n + 1, 0);
    vector<int> outdegree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int child, parent;
        cin >> child >> parent;
        children[parent].push_back(child);
        parents[child].push_back(parent);
        ++indegree[child];
        ++outdegree[parent];
    }

    int target;
    cin >> target;

    queue<int> q;
    vector<int> indegreeCopy = indegree;
    vector<int> topo;
    topo.reserve(n);
    for (int node = 1; node <= n; ++node) {
        if (indegreeCopy[node] == 0) {
            q.push(node);
        }
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        topo.push_back(node);
        for (int child : children[node]) {
            --indegreeCopy[child];
            if (indegreeCopy[child] == 0) {
                q.push(child);
            }
        }
    }

    vector<long long> waysFromSources(n + 1, 0);
    for (int node : topo) {
        if (indegree[node] == 0) {
            waysFromSources[node] = 1;
        }
        for (int child : children[node]) {
            waysFromSources[child] += waysFromSources[node];
        }
    }

    vector<long long> waysToLeaves(n + 1, 0);
    for (int i = n - 1; i >= 0; --i) {
        int node = topo[i];
        if (outdegree[node] == 0) {
            waysToLeaves[node] = 1;
        } else {
            for (int child : children[node]) {
                waysToLeaves[node] += waysToLeaves[child];
            }
        }
    }

    vector<long long> waysToTarget(n + 1, 0);
    waysToTarget[target] = 1;
    for (int i = n - 1; i >= 0; --i) {
        int node = topo[i];
        if (node == target) {
            continue;
        }
        for (int child : children[node]) {
            waysToTarget[node] += waysToTarget[child];
        }
    }

    int repeatedAncestorCount = 0;
    for (int node = 1; node <= n; ++node) {
        if (node != target && waysToTarget[node] > 1) {
            ++repeatedAncestorCount;
        }
    }

    int bestHorse = 1;
    long long bestPaths = waysFromSources[1] * waysToLeaves[1];
    for (int node = 2; node <= n; ++node) {
        long long pathCount = waysFromSources[node] * waysToLeaves[node];
        if (pathCount > bestPaths || (pathCount == bestPaths && node < bestHorse)) {
            bestPaths = pathCount;
            bestHorse = node;
        }
    }

    cout << repeatedAncestorCount << '\n';
    cout << bestHorse << '\n';
    return 0;
}