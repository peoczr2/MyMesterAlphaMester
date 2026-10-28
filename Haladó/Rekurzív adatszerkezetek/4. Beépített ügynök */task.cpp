#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
Az ügynök akkor van a főnökhöz legközelebb, ha a közvetlen főnöke a legkisebb mélységű
olyan tag, akinek még van szabad helye (kevesebb mint 2 közvetlen beosztottja van).
Több ilyen jelölt közül azt választjuk, akinek a legtöbb (nem csak közvetlen) beosztottja van;
ha ez is egyenlő, a kisebb sorszámút.

Ezért a főnöktől indított szélességi bejárással kiszámoljuk minden tag mélységét, majd a
bejárás fordított sorrendjében összeadjuk a leszármazottak számát. Végül a szabad helyű
tagok közül a (mélység, leszármazottak száma, sorszám) szerint legjobbat írjuk ki.
Ez O(N) időben fut.
*/
/*
Hint 1: || A főnökhöz legközelebbi hely azt jelenti, hogy a legkisebb mélységű olyan tagot keresed, akinek van szabad helye. ||
Hint 2: || Egy tag leszármazottainak száma a közvetlen gyerekei és azok leszármazottainak számának összege, ezért a bejárás fordított sorrendjében kiszámolható. ||
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

    // szélességi bejárás a főnöktől: mélységek és sorrend
    vector<int> depth(N + 1, 0);
    vector<int> order = {root};
    for (size_t i = 0; i < order.size(); ++i) {
        int u = order[i];
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            order.push_back(v);
        }
    }

    // leszármazottak száma: a gyerekek mindig a szülő előtt szerepelnek a fordított sorrendben
    vector<int> descendants(N + 1, 0);
    for (int i = (int)order.size() - 1; i >= 0; --i) {
        int u = order[i];
        for (int v : children[u]) {
            descendants[u] += 1 + descendants[v];
        }
    }

    int best = -1;
    for (int u = 1; u <= N; ++u) {
        if (children[u].size() >= 2) {
            continue;
        }
        if (best == -1 || depth[u] < depth[best] ||
            (depth[u] == depth[best] && (descendants[u] > descendants[best] ||
                                         (descendants[u] == descendants[best] && u < best)))) {
            best = u;
        }
    }

    cout << best << '\n';
    return 0;
}
