/*
Megoldás lényege:
Minden háromszögnek három éle van, és két város pontosan akkor szomszédos, ha közös háromszögben vannak, vagyis ha köztük van háromszög-él. Egy él belső, ha két háromszög is tartalmazza, és határél, ha pontosan egy háromszögben szerepel. Az országhatáron levő városok a határélek végpontjai. Az éleket (kisebb csúcs, nagyobb csúcs) párként egy vektorba írjuk, rendezzük, majd az azonos élek megszámlálásával egyszerre kapjuk meg a határ városait és az egyedi szomszédok számát. Az időigény O(M log M), ahol M a háromszögek száma.
*/
/*
Hint 1: || Két város szomszédos, ha köztük van háromszög-él. Egy él határél, ha csak egyetlen háromszögben szerepel, mert a belső éleket két háromszög is tartalmazza. ||
Hint 2: || Minden háromszög három élét tedd egy listába úgy, hogy a kisebb sorszámú csúcs legyen elöl. Rendezés után az azonos elemek megszámlálásával megkapod a határéleket és az egyedi szomszédokat. Egy határél végpontjai határvárosok. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    // Az élt (u, v) párként, u < v esetén, egyetlen számba kódoljuk.
    vector<long long> edges;
    edges.reserve(3LL * m);
    auto addEdge = [&](long long u, long long v) {
        if (u > v) swap(u, v);
        edges.push_back(u * (n + 1) + v);
    };
    for (int i = 0; i < m; i++) {
        long long a, b, c;
        cin >> a >> b >> c;
        addEdge(a, b);
        addEdge(b, c);
        addEdge(a, c);
    }
    sort(edges.begin(), edges.end());

    vector<int> deg(n + 1, 0);
    vector<bool> onBorder(n + 1, false);
    size_t i = 0;
    while (i < edges.size()) {
        size_t j = i;
        while (j < edges.size() && edges[j] == edges[i]) j++;
        int u = edges[i] / (n + 1);
        int v = edges[i] % (n + 1);
        deg[u]++;
        deg[v]++;
        if (j - i == 1) {  // csak egy háromszögben szerepel: határél
            onBorder[u] = true;
            onBorder[v] = true;
        }
        i = j;
    }

    int borderCount = 0;
    for (int v = 1; v <= n; v++) {
        if (onBorder[v]) borderCount++;
    }

    cout << borderCount << '\n';
    for (int v = 1; v <= n; v++) {
        if (v > 1) cout << ' ';
        cout << deg[v];
    }
    cout << '\n';
    return 0;
}
