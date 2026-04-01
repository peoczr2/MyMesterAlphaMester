#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A vállalkozók egy fa csúcsai. A pénz minden továbbadással harmadolódik, ezért
egy csomópont pénze kizárólag a gyökértől mért mélységétől függ.

Így a legkevesebb pénzt a legmélyebb csomópontok kapják, a legtöbbet az 1-es
csúcs, a munkát tovább nem adó vállalkozók pedig pontosan a levelek.

Hint 1: || A pénz csak a mélységtől függ, mert minden továbbadáskor harmadolódik. ||
Hint 2: || A minimumot a legmélyebb csúcsok, a maximumot a gyökér adja. ||
Hint 3: || A levelek azok a csúcsok, amelyeknek nincs két újabb vállalkozójuk. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> children(2 * N + 5);
    vector<int> indeg(2 * N + 5, 0), outdeg(2 * N + 5, 0);
    for (int i = 0; i < N; ++i) {
        int s, a, b;
        cin >> s >> a >> b;
        children[s].push_back(a);
        children[s].push_back(b);
        ++outdeg[s];
        ++indeg[a];
        ++indeg[b];
    }

    int maxId = 2 * N + 1;
    vector<int> depth(maxId + 1, -1);
    queue<int> q;
    depth[1] = 0;
    q.push(1);
    int bestDepth = 0;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            bestDepth = max(bestDepth, depth[v]);
            q.push(v);
        }
    }

    vector<int> minMoney, maxMoney, leaves;
    for (int i = 1; i <= maxId; ++i) {
        if (depth[i] == bestDepth) minMoney.push_back(i);
        if (i == 1) maxMoney.push_back(i);
        if (outdeg[i] == 0 && depth[i] != -1) leaves.push_back(i);
    }

    cout << minMoney.size();
    for (int x : minMoney) cout << ' ' << x;
    cout << '\n';

    cout << maxMoney.size();
    for (int x : maxMoney) cout << ' ' << x;
    cout << '\n';

    cout << leaves.size();
    for (int x : leaves) cout << ' ' << x;
    cout << '\n';
    return 0;
}