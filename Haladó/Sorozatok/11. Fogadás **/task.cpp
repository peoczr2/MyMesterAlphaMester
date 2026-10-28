/*
Megoldás lényege:
Mivel minden vendég ugyanannyi ideig marad, a találkozási gráf egyforma hosszú intervallumok metszetgráfja.
Ilyen gráfban van olyan sorrend, amelyben minden csúcs és szomszédai egy összefüggő szakaszt alkotnak, és ez a
sorrend adja meg a keresett érkezési sorrendet. Ezt a sorrendet Corneil háromszoros LexBFS-módszerével keressük:
az első bejárás tetszőleges kezdőpontból indul, a második és a harmadik az előző sorrend szerint tör döntetleneket.
Minden kapott sorrendet ellenőrzünk, és az első jót kiírjuk; N ≤ 200 miatt ez gyorsan lefut.
*/
/*
Hint 1: || Az egyforma ideig jelen lévő vendégek találkozási gráfjában keresünk olyan sorrendet, amelyben minden vendég szomszédai egy összefüggő szakaszt alkotnak. ||
Hint 2: || LexBFS: a még ki nem választott vendégek közül mindig azt vesszük, akinek a kiválasztott szomszédai lexikografikusan a legkorábbiak (a kiválasztási sorszámaik listáját hasonlítjuk össze); döntetlennél az előző sorrend szerint. ||
Hint 3: || Három bejárás után ellenőrizd, hogy minden csúcs és szomszédai összefüggő blokkot alkotnak; ha igen, ez érkezési sorrend. A kezdőpontot és a döntetlen-irányt próbáld ki, amíg jó sorrendet nem kapsz. ||
*/
#include <bits/stdc++.h>
using namespace std;

// LexBFS: a csúcsokat a label (csökkenő lépésszámok listája) szerint választja, döntetlennél a rank szerint kisebbet.
// start > 0 esetén azt a csúcsot járja be először.
static vector<int> lexBfs(const vector<vector<char>> &adj, int start, const vector<int> &rank) {
    int n = (int)adj.size() - 1;
    vector<vector<int>> label(n + 1);
    vector<char> used(n + 1, 0);
    vector<int> order;
    order.reserve(n);

    if (start > 0) label[start].push_back(n + 1);

    for (int step = n; step >= 1; --step) {
        int best = -1;
        for (int v = 1; v <= n; ++v) {
            if (used[v]) continue;
            if (best == -1 || label[v] > label[best] || (label[v] == label[best] && rank[v] < rank[best])) {
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

// Ellenőrzés: minden csúcs és a szomszédai pozíció szerint összefüggő blokkot alkotnak.
static bool validOrder(const vector<vector<char>> &adj, const vector<int> &order) {
    int n = (int)order.size();
    vector<int> pos(n + 1);
    for (int i = 0; i < n; ++i) pos[order[i]] = i;

    for (int v = 1; v <= n; ++v) {
        int left = pos[v], right = pos[v];
        for (int u = 1; u <= n; ++u) {
            if (!adj[v][u]) continue;
            left = min(left, pos[u]);
            right = max(right, pos[u]);
        }
        for (int i = left; i <= right; ++i) {
            if (order[i] != v && !adj[v][order[i]]) return false;
        }
    }
    return true;
}

// Rangok egy sorrendből: a korábban álló csúcs kisebb rangot kap (vagy fordítva, ha reversed).
static vector<int> rankFromOrder(const vector<int> &order, bool reversed) {
    int n = (int)order.size();
    vector<int> rank(n + 1);
    for (int i = 0; i < n; ++i) rank[order[i]] = reversed ? n - i : i;
    return rank;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<char>> adj(n + 1, vector<char>(n + 1, 0));
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a][b] = adj[b][a] = 1;
    }

    vector<int> identity(n + 1);
    for (int v = 0; v <= n; ++v) identity[v] = v;

    // Három LexBFS-bejárás: az elsőt tetszőleges kezdőpontból indítjuk, a másodikat és harmadikat az
    // előző sorrend szerinti döntetlen-töréssel. Az első érvényes (umbrella) sorrendet kiírjuk.
    vector<int> answer;
    for (int start = 1; start <= n && answer.empty(); ++start) {
        for (int dir = 0; dir < 2 && answer.empty(); ++dir) {
            bool reversed = (dir == 1);
            vector<int> rank1 = identity;
            if (reversed) rank1 = rankFromOrder(vector<int>(identity.begin() + 1, identity.end()), true);
            auto o1 = lexBfs(adj, start, rank1);
            if (validOrder(adj, o1)) { answer = o1; break; }
            auto o2 = lexBfs(adj, 0, rankFromOrder(o1, reversed));
            if (validOrder(adj, o2)) { answer = o2; break; }
            auto o3 = lexBfs(adj, 0, rankFromOrder(o2, reversed));
            if (validOrder(adj, o3)) { answer = o3; break; }
        }
    }

    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
