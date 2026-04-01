/*
Megoldási ötlet:
A közös ős férfiági fájában a legtávolabbi utódok pontosan a legnagyobb mélységű csúcsok.
Elég a fában egy gyökértől induló bejárással kiszámítani minden csúcs mélységét, majd a maximális mélységűek közül
bármelyiket kiírni.
*/
/*
Hint 1: || A keresett utódok a gyökértől mért legnagyobb távolságú csúcsok. ||
Hint 2: || Egy DFS vagy BFS elég a mélységek kiszámítására. ||
Hint 3: || Ha több csúcs is ugyanilyen mély, bármelyik jó. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> children(n + 1);
    vector<int> indegree(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int parent, child;
        cin >> parent >> child;
        children[parent].push_back(child);
        ++indegree[child];
    }

    int root = 1;
    while (root <= n && indegree[root] != 0) ++root;

    vector<int> depth(n + 1, -1);
    vector<int> stack = {root};
    depth[root] = 0;
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            stack.push_back(child);
        }
    }

    int best = root;
    for (int node = 1; node <= n; ++node) {
        if (depth[node] > depth[best]) best = node;
    }
    cout << best << '\n';
    return 0;
}
