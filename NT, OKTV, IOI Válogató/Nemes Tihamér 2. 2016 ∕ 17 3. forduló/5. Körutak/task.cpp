/*
Megoldás lényege:
Egy csúcs akkor van körön, ha a 2-magban marad, vagyis a 2-nél kisebb fokú csúcsok sorban történő eltávolítása után is megmarad. A tervezési feltétel miatt két körút között nem húzódhat olyan út, amelynek csúcsai körön kívül esnek, így a 2-magban maradó csúcsok mind valamely körön vannak. A sorban eltávolított csúcsok viszont egyetlen körön sem lehetnek, ezek a válasz. A fokszámokat tömbben tartjuk, és az elhagyott csúcsok szomszédainak fokát csökkentjük, így az idő O(N + M).
*/
/*
Hint 1: || Egy körön lévő csúcsnak legalább két szomszédja van, amelyek szintén a körön vannak. Ha egy csúcsnak legfeljebb egy szomszédja van, rajta biztosan nincs kör, és elhagyható. ||
Hint 2: || Az elhagyott csúcs szomszédainak fokszámát csökkentsd eggyel. Ha egy szomszéd fokszáma 1-re csökken, ő is elhagyható, ezért sorba állítva dolgozhatod fel a csúcsokat. ||
Hint 3: || A végén az elhagyott csúcsok lesznek a válasz; a feladat szerint növekvő sorrendben kell kiírni őket, ezt az 1-től N-ig tartó végigjárással kapod meg. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n + 1);
    vector<int> deg(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y;
        cin >> x >> y;
        g[x].push_back(y);
        g[y].push_back(x);
        ++deg[x];
        ++deg[y];
    }

    queue<int> q;
    vector<char> alive(n + 1, 1);
    for (int i = 1; i <= n; ++i) if (deg[i] < 2) q.push(i);
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        if (!alive[v]) continue;
        alive[v] = 0;
        for (int to : g[v]) {
            if (--deg[to] == 1) q.push(to);
        }
    }

    vector<int> ans;
    for (int i = 1; i <= n; ++i) if (!alive[i]) ans.push_back(i);
    cout << ans.size() << '\n';
    for (int i = 0; i < (int)ans.size(); ++i) {
        if (i) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}