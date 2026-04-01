/*
Megoldas lenyege:
A ket oldalso sinre (C es D) kerulo kocsik sorrendje az eredeti bemenetben egy-egy
csokkeno reszsorozatot ad. Két kocsi nem kerülhet ugyanarra a sinre, ha van egy későbbi,
hozzajuk kepest kisebb kocsi, mert az a későbbi kis kocsi már nem férne ki előttük.
Ezért konfliktusgrafot építünk: két pozíció között él van, ha nem lehetnek azonos sinen.
A sor akkor rendezhető, ha ez a graf bipartit.
*/
/*
Hint 1: || Az oldalsínekre kerülő kocsik az eredeti sorrendben csökkenő sorozatot alkotnak. ||
Hint 2: || Két kocsi azért ütközik, mert van egy náluk későbbi kisebb kocsi, ami miatt nem kerülhetnek ugyanarra a sínre. ||
Hint 3: || Ha a konfliktusgraf két színnel színezhető, akkor a két szín adja a két oldalsínt. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        vector<int> a;
        for (;;) {
            int x;
            cin >> x;
            if (x == 0) break;
            a.push_back(x);
        }

        int n = (int)a.size();
        vector<int> suffixMin(n + 1, INT_MAX);
        for (int i = n - 1; i >= 0; --i) suffixMin[i] = min(suffixMin[i + 1], a[i]);

        vector<vector<int>> adj(n);
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (a[i] < a[j] && suffixMin[j + 1] < a[i]) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }

        vector<int> color(n, -1);
        bool ok = true;
        for (int i = 0; i < n && ok; ++i) {
            if (color[i] != -1) continue;
            queue<int> q;
            color[i] = 0;
            q.push(i);
            while (!q.empty() && ok) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (color[v] == -1) {
                        color[v] = color[u] ^ 1;
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        ok = false;
                        break;
                    }
                }
            }
        }

        cout << (ok ? "IGEN" : "NEM") << '\n';
    }

    return 0;
}
