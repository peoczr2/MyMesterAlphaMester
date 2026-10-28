/*
Megoldás lényege:
Minden teremhez egy rácspontot rendelünk: x a vízszintes, h a függőleges koordináta (az 1-es terem a (0, 0) pont).
Egy járat mindig egy szinttel feljebb visz, a bal oldali felső végpontnál x eggyel csökken, a jobb oldalinál eggyel nő.
A felszínről függőlegesen lefelé fúrva egy adott x oszlopban a legmagasabban fekvő terem az első, amit elérünk, tehát
minden x-re a legnagyobb h-jú termet keressük.
A koordinátákat szélességi bejárással számoljuk az 1-es teremből; a járatokon lefelé is lépünk (ekkor x és h ellentétesen
változik), így minden terem sorra kerül, amely járatokon át összeköttetésben van az 1-essel.
Fontos, hogy minden termet csak egyszer veszünk sorra: ahol a járatok összefutnak, ugyanahhoz a teremhez sok út vezet,
de a koordinátája mindegyiken ugyanaz, ezért a már bejárt termet kihagyjuk. Jelölés nélkül az utak száma, és vele a
futásidő, a termek számában exponenciálisan nőhet.
Mivel |x| ≤ N, az oszlopok legjobb termét egy 2N+1 hosszú tömbben tartjuk. Az időigény O(N + M).
*/
/*
Hint 1: || Adj minden teremnek (x, magasság) koordinátát: balra lépésnél x−1, jobbra lépésnél x+1, a magasság eggyel nő. Egy fúrás egy x oszlopban a legmagasabb termet éri el. ||
Hint 2: || A koordinátákat bejárással (BFS) számold, de jelöld meg a már bejárt termeket: több út is vezethet ugyanahhoz a teremhez, és jelölés nélkül az utak száma exponenciálisan nőhet. ||
Hint 3: || x értéke −N és N közé esik, ezért egy x+N indexű tömbben tárold oszloponként a legnagyobb magasságú termet, és ezeket írd ki. ||
*/
#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int to, dx, dh;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<Edge>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, f;
        char c;
        cin >> a >> c >> f;
        int dx = (c == 'J') ? 1 : -1;
        g[a].push_back({f, dx, 1});    // felfelé
        g[f].push_back({a, -dx, -1});  // lefelé
    }

    vector<int> x(n + 1, 0), h(n + 1, 0);
    vector<bool> seen(n + 1, false);
    queue<int> q;
    q.push(1);
    seen[1] = true;
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (const Edge& e : g[v]) {
            if (seen[e.to]) continue;
            seen[e.to] = true;
            x[e.to] = x[v] + e.dx;
            h[e.to] = h[v] + e.dh;
            q.push(e.to);
        }
    }

    // best[x + n]: az x oszlop legmagasabb terme (0, ha nincs ott terem)
    vector<int> best(2 * n + 1, 0);
    for (int v = 1; v <= n; ++v) {
        if (!seen[v]) continue;
        int& b = best[x[v] + n];
        if (b == 0 || h[v] > h[b]) b = v;
    }

    vector<int> answer;
    for (int b : best)
        if (b != 0) answer.push_back(b);

    cout << answer.size() << '\n';
    for (int i = 0; i < (int)answer.size(); ++i) {
        if (i) cout << ' ';
        cout << answer[i];
    }
    cout << '\n';
    return 0;
}
