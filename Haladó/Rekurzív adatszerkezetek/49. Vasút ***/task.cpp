/*
Megoldási ötlet:
A hálózat fa, gyökere a főváros (1). Egy vonat mindig a gyökérből indul és egy levélig megy. Azt keressük, hogy egy
ilyen útvonalon mekkora a leghosszabb összefüggő szakasz, amelyen belül a vasút nem ágazik el.

Ez pontosan azt jelenti, hogy a szakasz belső csúcsaiban lefelé nézve mindig pontosan egyetlen gyerek van az adott
irányban. A szakasz csak ott törik meg, ahol a következő csúcsból már többfelé lehet továbbmenni.

Legyen `chain[u]` annak a leghosszabb lefelé induló, nem elágazó szakasznak a hossza csúcsokban mérve, amely `u`-ból
indul. Ha `u`-nak pontosan egy gyereke van, akkor `chain[u] = 1 + chain[gyerek]`, különben `chain[u] = 1`.
A válasz a teljes fában előforduló maximum `chain[u]`.
*/
/*
Hint 1: || A „nem ágazik el” feltétel egy csúcsnál azt jelenti, hogy legfeljebb egy irányba lehet továbbmenni. ||
Hint 2: || Ha egy csúcsnak több gyereke van, akkor itt biztosan megszakad az ilyen szakasz. ||
Hint 3: || Postorderben könnyű kiszámítani, hogy egy csúcsból milyen hosszú egygyerekes lánc indul lefelé. ||
*/

#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    vector<int> parent(n + 1, 0);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        children[a].push_back(b);
        parent[b] = a;
    }

    vector<int> order = {1};
    for (size_t i = 0; i < order.size(); ++i) {
        int node = order[i];
        for (int child : children[node]) {
            order.push_back(child);
        }
    }

    vector<int> chain(n + 1, 1);
    int answer = 1;
    for (int i = static_cast<int>(order.size()) - 1; i >= 0; --i) {
        int node = order[i];
        if (children[node].size() == 1) {
            chain[node] = 1 + chain[children[node][0]];
        }
        if (chain[node] > answer) {
            answer = chain[node];
        }
    }

    cout << answer << '\n';
    return 0;
}