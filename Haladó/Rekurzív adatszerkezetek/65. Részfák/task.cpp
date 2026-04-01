/*
Megoldási ötlet:
Egy bináris fa teljes részfája pontosan akkor egyezik egy másik fával, ha a gyökerektől induló szerkezet és a csomópontok
értékei is teljesen megegyeznek. Ezért minden részfát kanonizálhatunk: a bal és jobb gyerek kanonikus azonosítója,
valamint a csomópont értéke együtt határozza meg a fa azonosítóját.

Az F fában kiszámítjuk minden csúcs kanonikus azonosítóját, majd a kérdezett fák gyökereinek azonosítóját csak meg kell
keresni ebben az azonosítóhalmazban.
*/
/*
Hint 1: || Két fa akkor ugyanaz, ha a gyökerük értéke és a két gyerekük is ugyanaz. ||
Hint 2: || Először az F fában számold ki minden részfa egyedi azonosítóját, majd ezeket tedd egy halmazba. ||
Hint 3: || Egy kérdezett fa akkor részfa, ha a gyökerének azonosítója szerepel az F valamelyik csúcsához tartozó azonosítók között. ||
*/

#include <algorithm>
#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

struct Tree {
    vector<string> label;
    vector<int> left;
    vector<int> right;
};

struct Key {
    string label;
    int leftId;
    int rightId;
    bool operator==(const Key& other) const {
        return leftId == other.leftId && rightId == other.rightId && label == other.label;
    }
};

struct KeyHash {
    size_t operator()(const Key& key) const {
        size_t h = hash<string>{}(key.label);
        h ^= hash<int>{}(key.leftId) + 0x9e3779b9 + (h << 6) + (h >> 2);
        h ^= hash<int>{}(key.rightId) + 0x9e3779b9 + (h << 6) + (h >> 2);
        return h;
    }
};

static unordered_map<Key, int, KeyHash> interned;
static int nextId = 1;

int intern(const string& label, int leftId, int rightId) {
    Key key{label, leftId, rightId};
    auto it = interned.find(key);
    if (it != interned.end()) return it->second;
    int id = nextId++;
    interned.emplace(move(key), id);
    return id;
}

int treeId(const Tree& tree, unordered_set<int>* allIds = nullptr) {
    int n = static_cast<int>(tree.label.size()) - 1;
    vector<int> order;
    order.reserve(n);
    vector<pair<int, bool>> st = {{1, false}};
    while (!st.empty()) {
        auto [node, visited] = st.back();
        st.pop_back();
        if (visited) {
            order.push_back(node);
        } else {
            st.push_back({node, true});
            if (tree.right[node] != 0) st.push_back({tree.right[node], false});
            if (tree.left[node] != 0) st.push_back({tree.left[node], false});
        }
    }

    vector<int> id(n + 1, 0);
    for (int node : order) {
        int leftId = tree.left[node] ? id[tree.left[node]] : 0;
        int rightId = tree.right[node] ? id[tree.right[node]] : 0;
        id[node] = intern(tree.label[node], leftId, rightId);
        if (allIds) allIds->insert(id[node]);
    }
    return id[1];
}

Tree readTree(int nodeCount) {
    Tree tree;
    tree.label.assign(nodeCount + 1, "");
    tree.left.assign(nodeCount + 1, 0);
    tree.right.assign(nodeCount + 1, 0);
    for (int i = 1; i <= nodeCount; ++i) cin >> tree.label[i];
    for (int i = 0; i < (nodeCount - 1) / 2; ++i) {
        int a, b, c;
        cin >> a >> b >> c;
        tree.left[a] = b;
        tree.right[a] = c;
    }
    return tree;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    Tree base = readTree(n);
    unordered_set<int> subtreeIds;
    treeId(base, &subtreeIds);

    int q;
    cin >> q;
    while (q--) {
        int m;
        cin >> m;
        Tree query = readTree(m);
        int id = treeId(query);
        cout << (subtreeIds.count(id) ? "IGEN" : "NEM") << '\n';
    }
    return 0;
}
