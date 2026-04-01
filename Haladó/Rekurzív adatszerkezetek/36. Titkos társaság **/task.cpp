/*
Megoldási ötlet:
Az a részfa „teljes”, amelyben minden csúcsnak vagy 0, vagy 2 gyereke van, és az összes levél ugyanazon a
mélységen van. Ez pontosan egy tökéletes bináris részfa.

Gyökerezzük a társaság fáját a vezetőnél. Ezután postorder bejárásban minden csúcsra meghatározzuk:
- a részfa méretét;
- a részfa magasságát, ha tökéletes;
- hogy tökéletes-e.

Egy csúcs részfája akkor tökéletes,
1. ha levél, ekkor mérete 1;
2. vagy ha pontosan két gyereke van, mindkét gyerek részfája tökéletes, és a két magasság megegyezik.

Azok közül a csúcsok közül, amelyek tökéletes részfát gyökereznek és a részfájuk mérete legalább K, a
legnagyobb mélységűt választjuk, holtversenyben a kisebb sorszámút.
*/
/*
Hint 1: || A keresett alcsoport nem tetszőleges részgráf, hanem egy csúcs teljes leszármazotti részfája. ||
Hint 2: || A „mindenkinek 0 vagy 2 beosztottja van, és a levelek egyforma távol vannak” feltétel pontosan a tökéletes bináris fa definíciója. ||
Hint 3: || Alulról felfelé könnyű eldönteni, hogy egy csúcs részfája tökéletes-e: nézd meg a két gyerek részfáját és a magasságukat. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, minSize;
    cin >> n >> minSize;

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int boss, subordinate;
        cin >> boss >> subordinate;
        children[boss].push_back(subordinate);
        parent[subordinate] = boss;
    }

    int root = 1;
    for (int node = 1; node <= n; ++node) {
        if (parent[node] == 0) {
            root = node;
            break;
        }
    }

    vector<int> depth(n + 1, 0);
    vector<int> order = {root};
    for (size_t i = 0; i < order.size(); ++i) {
        int node = order[i];
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            order.push_back(child);
        }
    }

    vector<int> subtreeSize(n + 1, 1);
    vector<int> height(n + 1, 0);
    vector<char> isPerfect(n + 1, false);

    int answer = 0;
    int bestDepth = -1;

    for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {
        int node = order[i];
        for (int child : children[node]) {
            subtreeSize[node] += subtreeSize[child];
        }

        if (children[node].empty()) {
            isPerfect[node] = true;
            height[node] = 0;
        } else if (children[node].size() == 2) {
            int left = children[node][0];
            int right = children[node][1];
            if (isPerfect[left] && isPerfect[right] && height[left] == height[right]) {
                isPerfect[node] = true;
                height[node] = height[left] + 1;
            }
        }

        if (isPerfect[node] && subtreeSize[node] >= minSize) {
            if (depth[node] > bestDepth || (depth[node] == bestDepth && (answer == 0 || node < answer))) {
                bestDepth = depth[node];
                answer = node;
            }
        }
    }

    cout << answer << '\n';
    return 0;
}