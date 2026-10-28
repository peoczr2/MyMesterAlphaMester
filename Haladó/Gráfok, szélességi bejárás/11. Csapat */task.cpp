/*
Megoldás lényege:
Az "nem szeretik egymást" párok gráfot alkotnak, a feladat pedig azt kéri, hogy minden ilyen élnél a két végpont különböző csapatba kerüljön.
Ez pontosan a gráf kétszínezése, amelyet szélességi bejárással (BFS) végzünk: minden még nem színezett összefüggő rész kezdőpontja a 0-s színt kapja, a szomszédok pedig az ellentétes színt.
Ha egy élnél azonos színű végpontok adódnak (ide tartozik a saját magába mutató él is), nincs megoldás, és egyetlen -1-et írunk ki.
Mivel van legalább egy él, a kétszínezhető gráfnál mindkét csapat nem üres lesz; az időigény O(N+M).
*/
/*
Hint 1: || Rajzold fel a "nem szeretik egymást" kapcsolatokat gráfként: a tanulók a csúcsok, a párok az élek, a feladat pedig a gráf kétszínezése. ||
Hint 2: || Szélességi bejárásnál a szomszédnak mindig az ellentétes színt add; ha már színezett szomszéddal azonos színt találsz, nincs megoldás. Minden összefüggő részt külön, új kezdőponttal indíts. ||
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
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    vector<int> color(n + 1, -1);
    bool ok = true;
    for (int s = 1; s <= n && ok; s++) {
        if (color[s] != -1) continue;
        color[s] = 0;
        queue<int> q;
        q.push(s);
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

    if (!ok || n < 2) {
        cout << -1 << "\n";
        return 0;
    }

    vector<int> team[2];
    for (int i = 1; i <= n; i++) team[color[i]].push_back(i);
    if (team[0].empty()) {
        team[0].push_back(team[1].back());
        team[1].pop_back();
    }
    if (team[1].empty()) {
        team[1].push_back(team[0].back());
        team[0].pop_back();
    }

    for (int c = 0; c < 2; c++) {
        for (size_t i = 0; i < team[c].size(); i++) {
            if (i) cout << ' ';
            cout << team[c][i];
        }
        cout << "\n";
    }
    return 0;
}
