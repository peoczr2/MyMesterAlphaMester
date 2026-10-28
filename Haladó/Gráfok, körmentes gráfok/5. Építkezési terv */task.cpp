/*
Megoldás lényege:
Egy napon csak egy munkaelem végezhető, egy előírás (A, B) pedig azt jelenti, hogy B napja szigorúan későbbi A napjánál.
Először a legkorábbi napokat javítjuk az előírások szerint: B legkorábbi napja legalább A legkorábbi napja + 1, ezt
topologikus sorrendben, a gráf éleit bejárva számoljuk. A javított értékek minden megoldásban teljesülő alsó korlátok.
Ezután a munkákat a javított legkorábbi nap szerint növekvően (döntetlennél topologikus sorrendben) egymás után
tesszük, mindig a lehető legkorábbi, még szabad napra. Ez a sorrend nem hagy feleslegesen üres napot, így a végső
nap minimális. A sorrend az előírásokat is betartja, mert az előírt munka javított legkorábbi napja kisebb.
Az időigény O(N + M + N log N).
*/
/*
Hint 1: || Mivel egy napon csak egy munka végezhető, a munkák egymás utáni napokra kerülnek. Az előírás miatt egy munka legkorábbi napja is növekedhet, ezt figyelembe kell venni. ||
Hint 2: || Ha A előbb kell, mint B, akkor B legkorábbi napját vedd legalább A legkorábbi napja + 1 értékének. Ezt topologikus sorrendben, a gráf éleit végigjárva kiszámolhatod. ||
Hint 3: || A javított legkorábbi napok szerint rendezd a munkákat, és sorban osztogasd ki a napokat: mindig a lehető legkorábbi, még szabad napot add a következő munkának. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> earliest(n + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> earliest[i];
    }

    vector<vector<int>> succ(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        succ[a].push_back(b);
        ++indeg[b];
    }

    // Topologikus sorrend; közben a legkorábbi napok javítása az előírások szerint.
    vector<int> order;
    order.reserve(n);
    queue<int> q;
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) {
            q.push(v);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        order.push_back(v);
        for (int w : succ[v]) {
            earliest[w] = max(earliest[w], earliest[v] + 1);
            if (--indeg[w] == 0) {
                q.push(w);
            }
        }
    }

    if (static_cast<int>(order.size()) < n) {
        cout << 0 << "\n";
        return 0;
    }

    vector<int> rank(n + 1);
    for (int i = 0; i < n; ++i) {
        rank[order[i]] = i;
    }

    vector<int> items(order);
    sort(items.begin(), items.end(), [&](int a, int b) {
        if (earliest[a] != earliest[b]) {
            return earliest[a] < earliest[b];
        }
        return rank[a] < rank[b];
    });

    vector<long long> day(n + 1, 0);
    long long last = 0;
    for (int v : items) {
        last = max(last + 1, earliest[v]);
        day[v] = last;
    }

    cout << last << "\n";
    for (int v = 1; v <= n; ++v) {
        if (v > 1) {
            cout << ' ';
        }
        cout << day[v];
    }
    cout << "\n";
    return 0;
}
