/*
Megoldási ötlet:
A vizitúra minden folyószakaszt legfeljebb egyszer érinthet, ezért a bejárt út egyszerű út az alatta fekvő fában.
Pozitív élhosszak mellett a leghosszabb ilyen út a fa átmérője.

Először választunk egy tetszőleges csúcsot, és megkeressük a tőle legtávolabbi pontot. Onnan még egyszer futtatva
megkapjuk a másik végpontot is. A két futás során eltárolt távolság adja a keresett hosszát.
*/
/*
Hint 1: || A folyásirány nem korlátozza az út hosszát, mert az út tetszőlegesen mehet az élekkel szemben is. ||
Hint 2: || Ha egy ponttól megkeresed a legtávolabbi másikat, majd onnan megint a legtávolabbit, az a fa átmérője lesz. ||
Hint 3: || Elég két bejárás és az egyikben eltárolt távolságokból kiválasztott maximum. ||
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

struct Edge {
    int to;
    int w;
};

pair<int, long long> farthest(int start, const vector<vector<Edge>>& graph) {
    int n = static_cast<int>(graph.size()) - 1;
    vector<long long> dist(n + 1, -1);
    stack<int> st;
    st.push(start);
    dist[start] = 0;
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        for (const auto& edge : graph[node]) {
            if (dist[edge.to] != -1) continue;
            dist[edge.to] = dist[node] + edge.w;
            st.push(edge.to);
        }
    }
    int bestNode = start;
    for (int node = 1; node <= n; ++node) {
        if (dist[node] > dist[bestNode]) bestNode = node;
    }
    return {bestNode, dist[bestNode]};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<Edge>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b, t;
        cin >> a >> b >> t;
        graph[a].push_back({b, t});
        graph[b].push_back({a, t});
    }

    auto first = farthest(1, graph);
    auto second = farthest(first.first, graph);

    cout << second.second << '\n';
    cout << first.first << ' ' << second.first << '\n';
    return 0;
}
