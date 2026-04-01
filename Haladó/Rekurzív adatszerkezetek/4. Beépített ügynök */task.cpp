#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A beépített ügynököt a főnökhöz lehető legközelebb kell elhelyezni, ezért az
összes lehetséges jelölt közül csak a főnök közvetlen beosztottjai számítanak.
Ha több ilyen csomópont van, akkor azt választjuk, amelyiknek a legnagyobb a
teljes leszármazotti száma; holtversenyben a kisebb sorszám nyer.

Ezért elegendő a fa gyökerét megtalálni, majd minden csomópontra kiszámítani a
leszármazottainak számát egy DFS-sel.

Hint 1: || A lehető legközelebb a főnökhöz azt jelenti, hogy csak a gyökér közvetlen gyerekei jöhetnek szóba. ||
Hint 2: || A döntésnél csak a teljes részfa méretét kell összehasonlítani a gyökér gyerekei között. ||
Hint 3: || Először keresd meg a gyökeret, majd egyetlen mélységi bejárással számold ki a részfák méretét. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<vector<int>> children(N + 1);
    vector<int> hasParent(N + 1, 0);
    for (int i = 0; i < N - 1; ++i) {
        int x, y;
        cin >> x >> y;
        children[y].push_back(x);
        hasParent[x] = 1;
    }

    int root = 1;
    for (int i = 1; i <= N; ++i) {
        if (!hasParent[i]) {
            root = i;
            break;
        }
    }

    vector<int> subtree(N + 1, 1);
    function<void(int)> dfs = [&](int u) {
        subtree[u] = 1;
        for (int v : children[u]) {
            dfs(v);
            subtree[u] += subtree[v];
        }
    };
    dfs(root);

    int best = -1;
    for (int v : children[root]) {
        if (best == -1 || subtree[v] > subtree[best] || (subtree[v] == subtree[best] && v < best)) {
            best = v;
        }
    }

    cout << best << '\n';
    return 0;
}