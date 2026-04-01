#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A főnök 1-es, és minden tag legfeljebb két közvetlen beosztottal rendelkezik.
Az üzenet egy nap alatt jut le egy szinttel mélyebbre, tehát azt kell keresni,
hogy melyik mélységi szinten van a legtöbb csúcs.

Egy BFS-sel kiszámítjuk minden tag napját (mélységét), majd megszámoljuk a
szintek elemszámát és a legnagyobbat választjuk. Holtversenyben a kisebb napot
írjuk ki.

Hint 1: || A kérdezett nap a gyökértől mért szintszámnak felel meg. ||
Hint 2: || Egy szintszámláló tömb elég, ha végigjárjuk a bináris fát. ||
Hint 3: || Holtversenyben a kisebb napot kell választani. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;
    vector<vector<int>> children(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int a, b;
        cin >> a >> b;
        children[a].push_back(b);
    }

    vector<int> depth(N + 1, 0);
    queue<int> q;
    q.push(1);
    vector<int> cnt(N + 1, 0);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : children[u]) {
            depth[v] = depth[u] + 1;
            ++cnt[depth[v]];
            q.push(v);
        }
    }

    int bestDay = 1;
    for (int day = 2; day <= N; ++day) {
        if (cnt[day] > cnt[bestDay]) bestDay = day;
    }
    cout << bestDay << '\n';
    return 0;
}