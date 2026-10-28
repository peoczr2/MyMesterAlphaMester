/*
Megoldás lényege:
A szakaszok felülről lefelé mutatnak, ezért a pontok egy körmentes irányított gráfot alkotnak. Starthelyek azok a
pontok, amelyekbe nem fut be szakasz, célhelyek pedig azok, amelyekből nem indul ki szakasz. Mivel legfeljebb 32
célhely van, minden pontra egy bitmaszkban tároljuk, mely célhelyek érhetők el onnan: a célhely saját bitjét, a
többit a kimenő szakaszok maszkjainak VAGY-olásával kapjuk, a topologikus sorrend fordított bejárásával. Ezután
minden starthely maszkjának bitjeit összeadjuk célhelyenként, és kiírjuk a legtöbb starthelyről elérhető célhely
számát és sorszámát. Az időigény O(N + M), mert minden élt egyszer dolgozunk fel.
*/
/*
Hint 1: || Az irányított gráfban a starthelyek azok a pontok, ahová nem fut be szakasz, a célhelyek pedig azok, ahonnan nem indul ki szakasz. Mivel a szakaszok lefelé mutatnak, a gráf körmentes. ||
Hint 2: || Minden pontra tárold bitmaszkban, mely célhelyek érhetők el onnan. Egy célhely maszkja csak a saját bitjét tartalmazza, más pontoké a kimenő szomszédok maszkjainak VAGY-a, és ezt a fordított topologikus sorrendben számold. ||
Hint 3: || Ha minden starthelyre megvan a maszkja, célhelyenként számold meg, hány starthely maszkjában szerepel a bitje. Az eredmény a legnagyobb ilyen szám és az a célhely, amelynek ez a szám a darabszáma. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);
    vector<int> indeg(n + 1, 0), outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int f, a;
        cin >> f >> a; // felső és alsó végpont
        adj[f].push_back(a);
        ++indeg[a];
        ++outdeg[f];
    }

    // Célhelyek sorszámozása (nincs kimenő szakasz)
    vector<int> sinkId(n + 1, -1), sinks;
    for (int v = 1; v <= n; ++v) {
        if (outdeg[v] == 0) {
            sinkId[v] = (int)sinks.size();
            sinks.push_back(v);
        }
    }

    // Topologikus sorrend (Kahn-algoritmus)
    vector<int> order, deg = indeg;
    order.reserve(n);
    queue<int> q;
    for (int v = 1; v <= n; ++v) {
        if (deg[v] == 0) q.push(v);
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (int w : adj[u]) {
            if (--deg[w] == 0) q.push(w);
        }
    }

    // mask[v]: a v-ből elérhető célhelyek bitjei
    vector<unsigned long long> mask(n + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int v = order[i];
        if (outdeg[v] == 0) mask[v] = 1ULL << sinkId[v];
        for (int w : adj[v]) mask[v] |= mask[w];
    }

    // Célhelyenként: hány starthelyről érhető el
    vector<int> cnt(sinks.size(), 0);
    for (int v = 1; v <= n; ++v) {
        if (indeg[v] != 0) continue;
        for (size_t b = 0; b < sinks.size(); ++b) {
            if (mask[v] >> b & 1ULL) ++cnt[b];
        }
    }

    int best = 0;
    for (size_t b = 1; b < sinks.size(); ++b) {
        if (cnt[b] >= cnt[best]) best = (int)b;
    }

    cout << cnt[best] << '\n' << sinks[best] << '\n';
    return 0;
}
