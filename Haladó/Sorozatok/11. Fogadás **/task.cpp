/*
Megoldas lenyege:
A találkozási gráf egy egyforma hosszúságú intervallumokból származó proper interval graph.
Ilyen gráfban létezik olyan sorrend, amelyben minden csúcs szomszédai egy összefüggő blokkot
alkotnak. Egy végpontból indított LexBFS ezt a sorrendet adja meg, ezért kipróbáljuk a
minimális fokszámú csúcsokat kezdőpontnak, és amelyik sorrendben a szomszédságok valóban
összefüggő blokkok, az egy helyes érkezési sorrend.
*/
/*
Hint 1: || Az egyforma ideig jelen lévő vendégek találkozási gráfja proper interval graph. ||
Hint 2: || A keresett érkezési sorrendben minden vendég szomszédai összefüggő intervallumot alkotnak. ||
Hint 3: || Elég a minimális fokszámú csúcsokból induló LexBFS-eket kipróbálni, majd az eredményt ellenőrizni. ||
*/
#include <bits/stdc++.h>
using namespace std;

static vector<int> lexBfs(const vector<vector<char>> &adj, int start) {
    int n = (int)adj.size() - 1;
    vector<vector<int>> label(n + 1);
    vector<char> used(n + 1, 0);
    vector<int> order;
    order.reserve(n);

    label[start].push_back(n + 1);

    for (int step = n; step >= 1; --step) {
        int best = -1;
        for (int v = 1; v <= n; ++v) {
            if (used[v]) continue;
            if (best == -1 || label[v] > label[best] || (label[v] == label[best] && v < best)) {
                best = v;
            }
        }
        order.push_back(best);
        used[best] = 1;
        for (int v = 1; v <= n; ++v) {
            if (!used[v] && adj[best][v]) {
                label[v].push_back(step);
            }
        }
    }
    return order;
}

static bool validOrder(const vector<vector<char>> &adj, const vector<int> &order) {
    int n = (int)order.size();
    vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) pos[order[i]] = i;

    for (int v = 1; v <= n; ++v) {
        int left = n, right = -1;
        for (int u = 1; u <= n; ++u) {
            if (!adj[v][u]) continue;
            left = min(left, pos[u]);
            right = max(right, pos[u]);
        }
        if (right == -1) continue;
        for (int i = left; i <= right; ++i) {
            if (order[i] != v && !adj[v][order[i]]) return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> adj(n + 1, vector<char>(n + 1, 0));
    vector<int> degree(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        if (!adj[a][b]) {
            adj[a][b] = adj[b][a] = 1;
            ++degree[a];
            ++degree[b];
        }
    }

    int minDeg = *min_element(degree.begin() + 1, degree.end());
    vector<int> candidates;
    for (int v = 1; v <= n; ++v) {
        if (degree[v] == minDeg) candidates.push_back(v);
    }

    vector<int> answer;
    for (int start : candidates) {
        auto order = lexBfs(adj, start);
        if (validOrder(adj, order)) {
            answer = order;
            break;
        }
    }

    if (answer.empty()) {
        for (int start = 1; start <= n && answer.empty(); ++start) {
            auto order = lexBfs(adj, start);
            if (validOrder(adj, order)) answer = order;
        }
    }

    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
