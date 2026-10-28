/*
Megoldás lényege:
Minden emlékezetből mondott pár (A, M) egy irányított élt jelent A-ból M felé, hiszen A alacsonyabb M-nél.
A tornasorok pontosan ennek a gráfnak a topologikus rendezései. Ezeket Kahn-algoritmussal (bemeneti fokok és sor) keressük meg:
ha nem tudunk minden diákot kivenni, van ellentmondás (ciklus), és a válasz 0.
A rendezés pontosan akkor egyértelmű, ha a kapott sorrendben minden szomszédos párhoz van közvetlen él.
Ha van olyan szomszédos pár, amelyek között nincs él, a két diák felcserélésével egy másik helyes sorrendet kapunk, ez adja a 2-es választ.
Az időigény O(N + K log K), a közvetlen élek megkeresése bináris kereséssel történik.
*/
/*
Hint 1: || Tekintsd a párokat irányított éleknek: az alacsonyabb diákból a magasabb felé mutasson él. A keresett tornasorok ennek a gráfnak a topologikus rendezései. ||
Hint 2: || Kahn-algoritmussal add meg az egyik topologikus rendezést: a bemeneti fokszámú csúcsokat sorba teszed, és a kivételkor csökkented a szomszédok fokszámát. Ha nem tudsz minden csúcsot kivenni, a válasz 0. ||
Hint 3: || A rendezés pontosan akkor egyértelmű, ha minden egymás utáni pár között van közvetlen él. Ha egy ilyen pár között nincs él, a két elem felcserélésével egy második, különböző sorrendet kapsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0);
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        indeg[b]++;
    }
    for (auto &lst : adj) {
        sort(lst.begin(), lst.end());
    }

    vector<int> order;
    order.reserve(n);
    queue<int> q;
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] == 0) {
            q.push(v);
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int v : adj[u]) {
            if (--indeg[v] == 0) {
                q.push(v);
            }
        }
    }

    if ((int)order.size() < n) {
        cout << 0 << '\n';
        return 0;
    }

    int swapAt = -1;
    for (int i = 0; i + 1 < n; ++i) {
        const vector<int> &lst = adj[order[i]];
        if (!binary_search(lst.begin(), lst.end(), order[i + 1])) {
            swapAt = i;
            break;
        }
    }

    auto printOrder = [&](const vector<int> &ord) {
        for (int i = 0; i < n; ++i) {
            cout << ord[i] << (i + 1 < n ? ' ' : '\n');
        }
    };

    if (swapAt == -1) {
        cout << 1 << '\n';
        printOrder(order);
    } else {
        vector<int> other = order;
        swap(other[swapAt], other[swapAt + 1]);
        cout << 2 << '\n';
        printOrder(order);
        printOrder(other);
    }
    return 0;
}
