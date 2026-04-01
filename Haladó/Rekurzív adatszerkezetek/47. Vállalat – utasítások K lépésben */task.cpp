/*
Megoldási ötlet:
Az igazgató az 1-es csúcs, és minden utasítás egy él mentén pontosan egy lépést tesz meg lefelé. Ezért azokhoz a
munkatársakhoz jut el pontosan K lépésben az utasítás, akiknek a mélysége K a gyökértől mérve.

Az input már közvetlenül megadja minden csúcs legfeljebb két gyerekét. Elég egy DFS vagy BFS az 1-es csúcsból,
közben kiszámítani a mélységeket, majd összegyűjteni a K mélységű csúcsokat.
*/
/*
Hint 1: || A „pontosan K lépés” egyszerűen gyökértől mért mélységet jelent. ||
Hint 2: || Az igazgató sorszáma fixen 1, tehát innen kell indulni. ||
Hint 3: || Ha bejárás közben viszed a mélységet, külön bonyolult logika nélkül ki tudod gyűjteni a megfelelő csúcsokat. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    vector<vector<int>> children(n + 1);
    for (int node = 1; node <= n; ++node) {
        int leftChild, rightChild;
        cin >> leftChild >> rightChild;
        if (leftChild != 0) {
            children[node].push_back(leftChild);
        }
        if (rightChild != 0) {
            children[node].push_back(rightChild);
        }
    }

    vector<int> result, depth(n + 1, 0), stack = {1};
    while (!stack.empty()) {
        int node = stack.back();
        stack.pop_back();
        if (depth[node] == k) {
            result.push_back(node);
        }
        for (int child : children[node]) {
            depth[child] = depth[node] + 1;
            stack.push_back(child);
        }
    }

    cout << result.size() << '\n';
    for (int i = 0; i < static_cast<int>(result.size()); ++i) {
        if (i > 0) {
            cout << ' ';
        }
        cout << result[i];
    }
    cout << '\n';
    return 0;
}