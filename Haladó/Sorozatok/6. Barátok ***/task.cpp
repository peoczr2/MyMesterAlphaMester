/*
Megoldas lenyege:
Minden tanulo pontosan egy masik tanulot valaszt. Ez egy fuggvenyes grafot ad, amibol az
elsofoku informaciok egyszeruen kiolvashatok: a senkinek sem szimpatikusak az 0 bejovo
fokszamuek, a legkedveltebbek a maximum bejovo fokszamúak, a kolcsonosen egymasnak
szimpatikus parok pedig azok a ketesetek, ahol mindketten csak egymast valasztottak.
A szimpatiacsoportok maximalis szama a weak componentek szama.
*/
/*
Hint 1: || Minden diák pontosan egy másikat választ, ezért elég egy bejövő fokszámláló és egy union-find. ||
Hint 2: || A kölcsönös párhoz mindkét oldalnak pontosan egyszer kell szerepelnie választottként, és egymásra kell mutatniuk. ||
Hint 3: || A csoportszámot az összefüggő komponensek adják, ha az irányokat figyelmen kívül hagyjuk. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> parent, size;
    DSU(int n = 0) { init(n); }
    void init(int n) {
        parent.resize(n);
        size.assign(n, 1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] == x) return x;
        return parent[x] = find(parent[x]);
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] < size[b]) swap(a, b);
        parent[b] = a;
        size[a] += size[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> name(n), favName(n);
    unordered_map<string, int> id;
    id.reserve(n * 2 + 1);

    for (int i = 0; i < n; ++i) {
        cin >> name[i] >> favName[i];
        id.emplace(name[i], i);
    }

    vector<int> fav(n);
    for (int i = 0; i < n; ++i) {
        fav[i] = id[favName[i]];
    }

    vector<int> indeg(n, 0);
    for (int i = 0; i < n; ++i) ++indeg[fav[i]];

    vector<string> nobody;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == 0) nobody.push_back(name[i]);
    }

    vector<string> mutualPairs;
    for (int i = 0; i < n; ++i) {
        int j = fav[i];
        if (i < j && fav[j] == i && indeg[i] == 1 && indeg[j] == 1) {
            mutualPairs.push_back(name[i] + "-" + name[j]);
        }
    }

    int best = *max_element(indeg.begin(), indeg.end());
    vector<string> bestPeople;
    for (int i = 0; i < n; ++i) {
        if (indeg[i] == best) bestPeople.push_back(name[i]);
    }

    DSU dsu(n);
    for (int i = 0; i < n; ++i) dsu.unite(i, fav[i]);
    int groups = 0;
    for (int i = 0; i < n; ++i) {
        if (dsu.find(i) == i) ++groups;
    }

    auto printList = [](const vector<string> &items) {
        if (items.empty()) {
            cout << "-\n";
            return;
        }
        for (size_t i = 0; i < items.size(); ++i) {
            if (i) cout << ' ';
            cout << items[i];
        }
        cout << '\n';
    };

    printList(nobody);
    printList(mutualPairs);
    printList(bestPeople);
    cout << groups << '\n';

    return 0;
}
