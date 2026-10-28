/*
Megoldás lényege:
A járásközpontokat egyszerre, több forrásból indított szélességi bejárással (BFS) járjuk be.
A központokat növekvő sorszám szerint tesszük a sorba, így minden település azt a központot kapja,
amelyik a legkisebb távolságra van tőle, és egyenlő távolság esetén a kisebb sorszámút.
Ennek oka, hogy a sorban a csúcsok mindig távolság és címke szerint rendezve vannak, így az első
olyan szomszéd, amelyik elérné a csúcsot, már a legjobb címkével rendelkezik.
Az utak irányítatlanok, a gráf összefüggő, a végén a címkék alapján minden járást megszámoljuk.
Az időigény O(N + K), ami a korlátok mellett bőven elegendő.
*/
/*
Hint 1: || Több forrásból induló szélességi bejárást kell csinálni: a sorba kezdetben az összes járásközpont kerüljön. ||
Hint 2: || Minden csúcshoz tárold, melyik járásközpontból érkezett a bejárás, és ha egy csúcsot először érsz el, a szomszédjától örökölt címkét add neki. ||
Hint 3: || A központokat növekvő sorszám szerint add a sorhoz, így egyenlő távolságnál a kisebb sorszámú központ éri el előbb a csúcsot. Az eredményt a címkék darabszámából kapod meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> centers(m);
    for (int &v : centers) {
        cin >> v;
    }
    sort(centers.begin(), centers.end());

    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < k; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> label(n + 1, -1);
    queue<int> q;
    for (int i = 0; i < m; ++i) {
        label[centers[i]] = i;
        q.push(centers[i]);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (label[v] == -1) {
                label[v] = label[u];
                q.push(v);
            }
        }
    }

    vector<int> cnt(m, 0);
    for (int v = 1; v <= n; ++v) {
        if (label[v] >= 0) {
            ++cnt[label[v]];
        }
    }

    for (int i = 0; i < m; ++i) {
        cout << cnt[i] << '\n';
    }
    return 0;
}
