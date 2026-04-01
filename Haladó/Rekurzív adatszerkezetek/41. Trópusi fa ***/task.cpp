/*
Megoldási ötlet:
Akkor és csak akkor tükörképe egymásnak egy pont bal és jobb oldali teljes ága, ha a bal részfa pontosan
megegyezik a jobb részfa tükrözöttjével. Ezt alulról felfelé lehet eldönteni: minden ponthoz rendelünk egy
azonosítót a részfa alakjára, és egy másikat a részfa tükrözött alakjára.

Legyen `id[u]` az `u` pontból induló rendezett bináris részfa kanonikus azonosítója, `tukorId[u]` pedig ugyanennek
a tükrözött alakja. Egy levél azonosítója ugyanaz, mint a `(0,0)` gyerekpáré. Postorderben feldolgozva minden pontnál
az `(id[bal], id[jobb])` párból kapjuk az `id[u]` értékét, a `(tukorId[jobb], tukorId[bal])` párból a `tukorId[u]`-t.
Egy pont akkor jó, ha `id[bal] == tukorId[jobb]`. A jó pontok közül a legkisebb mélységű kell, holtversenyben a
legkisebb sorszámú.
*/
/*
Hint 1: || Egy pont akkor szimmetrikus, ha a bal oldali részfa ugyanaz, mint a jobb oldali részfa tükörképe. ||
Hint 2: || A részfák alakját hash helyett biztonságosan lehet kanonikus azonosítókkal is reprezentálni: azonos gyerekpárhoz azonos ID tartozzon. ||
Hint 3: || Postorder bejárásban már ismered a gyerekek részfa-azonosítóit, így a szülőé egyetlen párosító táblából előállítható. ||
*/

#include <iostream>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct PairHash {
    size_t operator()(const pair<int, int>& value) const {
        return (static_cast<size_t>(value.first) << 32) ^ static_cast<unsigned int>(value.second);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> leftChild(n + 1, 0), rightChild(n + 1, 0), parent(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int node, left, right;
        cin >> node >> left >> right;
        leftChild[node] = left;
        rightChild[node] = right;
        if (left != 0) {
            parent[left] = node;
        }
        if (right != 0) {
            parent[right] = node;
        }
    }

    vector<int> depth(n + 1, 0), order;
    order.reserve(n);
    vector<pair<int, int>> stack = {{1, 0}};
    while (!stack.empty()) {
        auto [node, phase] = stack.back();
        stack.pop_back();
        if (phase == 0) {
            stack.push_back({node, 1});
            if (rightChild[node] != 0) {
                depth[rightChild[node]] = depth[node] + 1;
                stack.push_back({rightChild[node], 0});
            }
            if (leftChild[node] != 0) {
                depth[leftChild[node]] = depth[node] + 1;
                stack.push_back({leftChild[node], 0});
            }
        } else {
            order.push_back(node);
        }
    }

    unordered_map<pair<int, int>, int, PairHash> idOf;
    idOf.reserve(2 * n + 1);
    idOf[{0, 0}] = 1;
    int nextId = 2;

    vector<int> id(n + 1, 1), mirrorId(n + 1, 1);
    int bestNode = 1;
    int bestDepth = n + 1;

    for (int node : order) {
        pair<int, int> normalKey = {id[leftChild[node]], id[rightChild[node]]};
        auto normalIt = idOf.find(normalKey);
        if (normalIt == idOf.end()) {
            normalIt = idOf.emplace(normalKey, nextId++).first;
        }
        id[node] = normalIt->second;

        pair<int, int> mirrorKey = {mirrorId[rightChild[node]], mirrorId[leftChild[node]]};
        auto mirrorIt = idOf.find(mirrorKey);
        if (mirrorIt == idOf.end()) {
            mirrorIt = idOf.emplace(mirrorKey, nextId++).first;
        }
        mirrorId[node] = mirrorIt->second;

        if (id[leftChild[node]] == mirrorId[rightChild[node]]) {
            if (depth[node] < bestDepth || (depth[node] == bestDepth && node < bestNode)) {
                bestDepth = depth[node];
                bestNode = node;
            }
        }
    }

    cout << bestNode << '\n';
    return 0;
}