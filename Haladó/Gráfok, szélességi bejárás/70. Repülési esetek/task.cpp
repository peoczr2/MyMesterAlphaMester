/*
Megoldás lényege:
A csíkok a városok gráfját alkotják, minden csíkot a két végpontja közül az egyik városból induló
repülő húzta, és minden városból legfeljebb egy repülő indul. Két különböző összefüggő részben
a döntések függetlenek, ezért a lehetőségek számát komponensenként számoljuk, és a kapott
számokat összeszorozzuk. Ha egy komponens fa (E = V - 1), pontosan egy város marad repülés
nélkül, így V lehetőség van. Ha a komponensben pontosan egy kör van (E = V), akkor a kör két
irányban járható be, ezért 2 lehetőség. Kivétel a kétélű kör: a két azonos csík felcserélése
ugyanazt a repülési tervet adja, így ott 1 lehetőség van. A komponenseket egyesítéses
halmazokkal (DSU) kezeljük, az időigény O(M log M).
*/
/*
Hint 1: || Minden csík egy repülést jelent, amelyet a két végpont közül az egyik indít, és minden városból legfeljebb egy indulhat. ||
Hint 2: || Különböző összefüggő részekben a döntések függetlenek, ezért a lehetőségeket komponensenként kell kiszámolni, majd összeszorozni. ||
Hint 3: || Fánál pontosan egy város marad repülés nélkül, körös komponensnél viszont minden város indít egy repülőt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int findRoot(vector<int>& parent, int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const long long MOD = 123456789LL;

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges(M);
    for (auto& e : edges) {
        cin >> e.first >> e.second;
        if (e.first > e.second) swap(e.first, e.second);
    }

    vector<int> parent(N + 1);
    for (int i = 0; i <= N; ++i) parent[i] = i;
    for (const auto& e : edges) {
        int a = findRoot(parent, e.first), b = findRoot(parent, e.second);
        if (a != b) parent[a] = b;
    }

    vector<long long> vertices(N + 1, 0), edgeCount(N + 1, 0);
    vector<char> hasParallel(N + 1, 0);
    for (int i = 1; i <= N; ++i) vertices[findRoot(parent, i)]++;
    for (const auto& e : edges) edgeCount[findRoot(parent, e.first)]++;

    sort(edges.begin(), edges.end());
    for (size_t i = 1; i < edges.size(); ++i) {
        if (edges[i] == edges[i - 1]) hasParallel[findRoot(parent, edges[i].first)] = 1;
    }

    long long ans = 1;
    for (int i = 1; i <= N; ++i) {
        if (findRoot(parent, i) != i) continue;
        if (edgeCount[i] == vertices[i] - 1) {
            ans = ans * (vertices[i] % MOD) % MOD;
        } else if (edgeCount[i] == vertices[i]) {
            ans = ans * (hasParallel[i] ? 1 : 2) % MOD;
        } else {
            ans = 0;
        }
    }

    cout << ans << '\n';
    return 0;
}
