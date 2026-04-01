/*
Megoldási ötlet:
Egy út adója annyiszor számít bele a teljes bevételbe, ahány város-pár útvonalában szerepel. Ez az egyes élekre
pontosan a fa levágásával keletkező két rész méretének szorzatából adódik: egy élre az átmenő rendezett város-párok
száma 2 * s * (N - s), ahol s az alsó részfa mérete.

Mivel az adómennyiségek tetszőlegesen rendelhetők az utakhoz, a maximális bevétel a legnagyobb adó és a legnagyobb
használati szám párosításával érhető el. Ezután az optimális hozzárendelést ki is írjuk.
*/
/*
Hint 1: || Egy út értékét az dönti el, hány város-pár útvonalában szerepel. ||
Hint 2: || Egy faélre ez a szám csak a két oldal részfaméretéből számolható. ||
Hint 3: || A legnagyobb adók a legtöbbször használt élekre kerüljenek. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int a, b;
    long long cnt;
    int taxIndex;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Edge> edges(n - 1);
    vector<vector<int>> children(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        cin >> edges[i].a >> edges[i].b;
        edges[i].taxIndex = i;
        children[edges[i].a].push_back(edges[i].b);
    }
    vector<long long> taxes(n - 1);
    for (int i = 0; i < n - 1; ++i) cin >> taxes[i];

    vector<int> order;
    order.reserve(n);
    vector<int> stack = {1};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        order.push_back(node);
        for (int child : children[node]) stack.push_back(child);
    }

    vector<int> sub(n + 1, 1);
    for (int idx = n - 1; idx >= 0; --idx) {
        int node = order[idx];
        for (int child : children[node]) sub[node] += sub[child];
    }

    for (auto& edge : edges) {
        int s = sub[edge.b];
        edge.cnt = 2LL * s * (n - s);
    }

    vector<int> edgeOrder(n - 1);
    for (int i = 0; i < n - 1; ++i) edgeOrder[i] = i;
    sort(edgeOrder.begin(), edgeOrder.end(), [&](int lhs, int rhs) {
        return edges[lhs].cnt > edges[rhs].cnt;
    });
    sort(taxes.begin(), taxes.end(), greater<long long>());

    __int128 revenue = 0;
    vector<long long> assigned(n - 1);
    for (int i = 0; i < n - 1; ++i) {
        assigned[edgeOrder[i]] = taxes[i];
        revenue += (__int128)edges[edgeOrder[i]].cnt * taxes[i];
    }

    long long mod = static_cast<long long>(revenue % 32609);
    cout << mod << '\n';
    for (int i = 0; i < n - 1; ++i) {
        cout << edges[i].a << ' ' << edges[i].b << ' ' << assigned[i] << '\n';
    }
    return 0;
}
