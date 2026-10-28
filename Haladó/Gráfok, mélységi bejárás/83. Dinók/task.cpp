/*
Megoldás lényege:
Minden dinó faj élettartama [L_i, R_i]. Az állítások két fajta feltételt adnak: az 1-es típus szerint a két intervallum metszi egymást (L_A <= R_B és L_B <= R_A), a 2-es típus szerint az A faj véget ér, mielőtt a B elkezdődne (R_A < L_B). Mindegyik feltétel "x_v <= x_u + w" alakú, ezért irányított gráfot építünk a 2N végponton: egy él u -> v súllyal w jelenti, hogy x_v <= x_u + w. Az R_A < L_B feltétel súlya -1, a többi 0, és minden fajhoz él megy R_i -> L_i súllyal 0. A rendszer akkor megoldható, ha nincs negatív kör. Mivel minden negatív él egy 2-es típusú állításból jön, negatív kör pontosan akkor van, ha valamelyik -1 élnek mindkét végpontja ugyanabban az erősen összefüggő komponensben van. Ezt Tarjan-algoritmussal ellenőrizzük. Megoldható esetben a komponenseken, a topologikus sorrendben, számoljuk a láncokban szereplő -1 élek maximális számát, és ebből egész értékeket adunk az intervallumoknak. Az egész algoritmus O(N + M).
*/
/*
Hint 1: || Az állítások mindegyike két végpont közötti egyenlőtlenség: L_A <= R_B, R_A < L_B stb. Írd fel őket egy irányított gráfon, ahol a súly 0 vagy -1. ||
Hint 2: || Negatív kör akkor és csak akkor van, ha egy "R_A < L_B" típusú él benne van körben, vagyis mindkét végpontja egy erősen összefüggő komponensben van. Erre Tarjan-algoritmus elég. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> adj;
vector<int> idxv, low, comp, stk;
vector<char> onStack;
int timerCnt = 0, compCount = 0;

void tarjan(int u) {
    idxv[u] = low[u] = ++timerCnt;
    stk.push_back(u);
    onStack[u] = 1;
    for (auto [v, w] : adj[u]) {
        if (!idxv[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if (onStack[v]) {
            low[u] = min(low[u], idxv[v]);
        }
    }
    if (low[u] == idxv[u]) {
        while (true) {
            int x = stk.back();
            stk.pop_back();
            onStack[x] = 0;
            comp[x] = compCount;
            if (x == u) break;
        }
        ++compCount;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    int V = 2 * n;   // i. faj: L = 2i, R = 2i + 1
    adj.assign(V, {});
    auto Lnode = [](int i) { return 2 * i; };
    auto Rnode = [](int i) { return 2 * i + 1; };

    for (int i = 0; i < n; ++i) adj[Rnode(i)].push_back({Lnode(i), 0});   // L_i <= R_i

    for (int j = 0; j < m; ++j) {
        int t, a, b;
        cin >> t >> a >> b;
        --a;
        --b;
        if (t == 1) {
            adj[Rnode(b)].push_back({Lnode(a), 0});   // L_A <= R_B
            adj[Rnode(a)].push_back({Lnode(b), 0});   // L_B <= R_A
        } else {
            adj[Lnode(b)].push_back({Rnode(a), -1});  // R_A < L_B
        }
    }

    idxv.assign(V, 0);
    low.assign(V, 0);
    comp.assign(V, -1);
    onStack.assign(V, 0);
    for (int v = 0; v < V; ++v)
        if (!idxv[v]) tarjan(v);

    // Negatív kör: egy -1 él mindkét végpontja ugyanabban a komponensben van
    for (int u = 0; u < V; ++u)
        for (auto [v, w] : adj[u])
            if (w < 0 && comp[u] == comp[v]) {
                cout << "NEM\n";
                return 0;
            }

    // Tarjan a komponenseket fordított topologikus sorrendben adja: az élek id-je csökken
    vector<vector<int>> members(compCount);
    for (int v = 0; v < V; ++v) members[comp[v]].push_back(v);

    // pot[c]: az adott komponensbe vezető láncokban szereplő -1 élek maximális száma
    vector<int> pot(compCount, 0);
    for (int c = compCount - 1; c >= 0; --c)
        for (int u : members[c])
            for (auto [v, w] : adj[u])
                if (comp[v] != c)
                    pot[comp[v]] = max(pot[comp[v]], pot[c] + (w < 0 ? 1 : 0));

    int maxPot = *max_element(pot.begin(), pot.end());
    auto value = [&](int v) { return maxPot - pot[comp[v]] + 1; };

    cout << "IGEN\n";
    for (int i = 0; i < n; ++i)
        cout << value(Lnode(i)) << ' ' << value(Rnode(i)) << '\n';
    return 0;
}
