/*
Megoldás lényege:
Ha a hálózatnak K összefüggő komponense van, akkor K-1 új vonal elég és szükséges is, hiszen minden új vonal legfeljebb két komponenst köt össze.
A komponenseket BFS-sel határozzuk meg, és mindegyik komponensből a legkisebb sorszámú csomópontot választjuk képviselőnek (ezek a 1..N bejárás során elsőként érintett csomópontok).
A képviselőket sorban összekötjük: az i-edik és az (i+1)-edik képviselő közé húzunk új vonalat, így K-1 vonal összeköti az egész hálózatot.
Az időigény O(N+M), ami a 0.1 mp-es korláton belül van.
*/
/*
Hint 1: || Számold meg a összefüggő komponenseket; ha K darab van, a minimális vonalszám K-1. ||
Hint 2: || Minden komponens egy képviselőjét (például a legkisebb sorszámút) válaszd ki, és az egymás utáni képviselők közé húzz új vonalat. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    // a komponensek képviselői: minden még be nem járt csomópontból BFS indul
    vector<char> seen(n + 1, 0);
    vector<int> roots;
    for (int s = 1; s <= n; s++) {
        if (seen[s]) continue;
        roots.push_back(s);
        queue<int> q;
        q.push(s);
        seen[s] = 1;
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (int u : adj[v]) {
                if (!seen[u]) {
                    seen[u] = 1;
                    q.push(u);
                }
            }
        }
    }

    int k = (int)roots.size() - 1;
    cout << k << '\n';
    for (int i = 0; i < k; i++)
        cout << roots[i] << ' ' << roots[i + 1] << '\n';
    return 0;
}
