/*
Megoldás lényege:
A barátság szimmetrikus és tranzitív, ezért a baráti csoportok pontosan a barátsági gráf összefüggő komponensei.
Ezeket unió-keresés (DSU) segítségével határozzuk meg: minden barátpárnál egyesítjük a két tanuló csoportját, a keresésnél útösszenyomást alkalmazunk.
Ezután a tanulókat sorszámuk szerint végigjárjuk: minden új csoport első tagja (a legkisebb sorszám) új csoportot nyit, így a csoportok és a tagjaik a kívánt sorrendben kerülnek kiírásra.
A művelet ideje közel lineáris: O(N + M * α(N)).
*/
/*
Hint 1: || A barátság tranzitív és szimmetrikus, így minden baráti csoport a barátsági kapcsolatok egy összefüggő része. Azt kell megszámolnod, hány ilyen rész van. ||
Hint 2: || Minden barátpárnál egyesítsd a két tanuló csoportját; ehhez elég minden tanulóhoz egy szülő-mutatót tárolni a csoportjának vezetőjéről. ||
Hint 3: || A tanulókat sorszámuk szerint járd be: egy csoport első (legkisebb sorszámú) tagjánál nyiss új csoportot, a többi tagot az adott csoporthoz add hozzá. ||
*/
#include <bits/stdc++.h>
using namespace std;

vector<int> parent;

int leader(int x) {
    while (parent[x] != x) {
        parent[x] = parent[parent[x]];
        x = parent[x];
    }
    return x;
}

int main() {
    int n, m;
    cin >> n >> m;
    parent.resize(n + 1);
    for (int i = 0; i <= n; i++) parent[i] = i;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        parent[leader(a)] = leader(b);
    }

    vector<int> groupOf(n + 1, -1);
    vector<vector<int>> groups;
    for (int i = 1; i <= n; i++) {
        int r = leader(i);
        if (groupOf[r] == -1) {
            groupOf[r] = groups.size();
            groups.push_back({});
        }
        groups[groupOf[r]].push_back(i);
    }

    cout << groups.size() << '\n';
    for (const auto &g : groups) {
        for (size_t j = 0; j < g.size(); j++) {
            if (j) cout << ' ';
            cout << g[j];
        }
        cout << '\n';
    }
    return 0;
}
