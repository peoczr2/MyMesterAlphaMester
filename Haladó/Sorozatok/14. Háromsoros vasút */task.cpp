/*
Megoldas lenyege:
A kocsikat harom oldalsinre kell szetosztani ugy, hogy mindegyik oldalsinen az oda kerulo
kocsik az input sorrendjeben csokkeno sorozatot alkossanak. Ehhez konfliktusgrafot epitunk:
ket kocsi nem lehet ugyanazon a sinen, ha van egy kesobbi, nala kisebb kocsi, amely miatt a
ketto egyutt mar nem lenne jo. A konfliktusgrafot harom szinnel színezzuk.
A színezés után az egyes színekhez tartozó kocsikat külön-ből a megfelelő sínre rakjuk,
majd a végén a három sínről a legkisebb éppen elérhető címkét adjuk vissza az A sínre.
*/
/*
Hint 1: || Egy oldalsínre kerülő kocsiknak az input sorrendjében csökkenő sorozatot kell alkotniuk. ||
Hint 2: || Két kocsi csak akkor kerülhet ugyanarra a sínre, ha nincs olyan későbbi kisebb kocsi, amely miatt blokkolnák egymást. ||
Hint 3: || A színezés után a kész oldalsínekről mindig a legkisebb felső címkét érdemes visszatolni az A sínre. ||
*/
#include <bits/stdc++.h>
using namespace std;

static vector<vector<int>> buildConflictGraph(const vector<int> &a) {
    int n = (int)a.size();
    vector<int> suffixMin(n + 1, INT_MAX);
    for (int i = n - 1; i >= 0; --i) suffixMin[i] = min(suffixMin[i + 1], a[i]);

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (a[i] < a[j] && suffixMin[j + 1] < a[i]) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }
    return adj;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    auto adj = buildConflictGraph(a);

    vector<int> order(n);
    iota(order.begin(), order.end(), 0);
    sort(order.begin(), order.end(), [&](int lhs, int rhs) {
        if (a[lhs] != a[rhs]) return a[lhs] < a[rhs];
        return lhs < rhs;
    });

    vector<int> color(n, -1);
    for (int v : order) {
        bool used[3] = {false, false, false};
        for (int u : adj[v]) {
            if (color[u] != -1) used[color[u]] = true;
        }
        int chosen = -1;
        for (int c = 0; c < 3; ++c) {
            if (!used[c]) {
                chosen = c;
                break;
            }
        }
        if (chosen == -1) {
            cout << "NEM\n";
            return 0;
        }
        color[v] = chosen;
    }

    array<vector<int>, 3> stacks;
    vector<string> ops;
    ops.reserve(2 * n);

    for (int i = 0; i < n; ++i) {
        int c = color[i];
        ops.push_back(string("B") + char('1' + c));
        stacks[c].push_back(a[i]);
    }

    auto popOnce = [&](int idx) {
        ops.push_back(string("K") + char('1' + idx));
        stacks[idx].pop_back();
    };

    while (true) {
        int bestIdx = -1;
        int bestVal = INT_MAX;
        for (int i = 0; i < 3; ++i) {
            if (!stacks[i].empty() && stacks[i].back() < bestVal) {
                bestVal = stacks[i].back();
                bestIdx = i;
            }
        }
        if (bestIdx == -1) break;
        popOnce(bestIdx);
    }

    for (const string &op : ops) cout << op << '\n';
    return 0;
}
