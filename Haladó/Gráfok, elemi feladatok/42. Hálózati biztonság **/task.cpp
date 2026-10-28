/*
Megoldás lényege: K-biztonságos részhálózatok uniója is K-biztonságos, ezért a legnagyobb ilyen részhálózat egyértelmű.
Ezt úgy kapjuk meg, hogy addig töröljük azokat a csomópontokat, amelyeknek a még megmaradt szomszédainak száma K-nál kisebb.
Egy csomópont törlésekor a szomszédainak fokszámát eggyel csökkentjük, így további csomópontok eshetnek ki.
Minden csomópont legfeljebb egyszer kerül a sorba, és minden él legfeljebb egyszer vesz részt a csökkentésben, ezért az időigény O(N+M).
*/
/*
Hint 1: || Egy csomópont csak akkor maradhat a részhálózatban, ha legalább K szomszédja is benne marad. Kezdetben tehát minden K-nál kisebb fokú csomópont biztosan kiesik. ||
Hint 2: || Egy csomópont kiesése csökkenti a szomszédai fokszámát, így további csomópontok eshetnek ki. Tartsunk egy sort a kiesésre váró csomópontokról, és dolgozzuk fel, amíg üres nem lesz. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> adj(n + 1);
    vector<int> deg(n + 1, 0);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
        deg[u]++;
        deg[v]++;
    }

    vector<char> removed(n + 1, 0);
    queue<int> q;
    for (int v = 1; v <= n; v++) {
        if (deg[v] < k) {
            removed[v] = 1;
            q.push(v);
        }
    }
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int u : adj[v]) {
            if (!removed[u]) {
                deg[u]--;
                if (deg[u] < k) {
                    removed[u] = 1;
                    q.push(u);
                }
            }
        }
    }

    vector<int> keep;
    for (int v = 1; v <= n; v++) {
        if (!removed[v]) keep.push_back(v);
    }
    cout << keep.size() << '\n';
    for (size_t i = 0; i < keep.size(); i++) {
        if (i) cout << ' ';
        cout << keep[i];
    }
    cout << '\n';
    return 0;
}
