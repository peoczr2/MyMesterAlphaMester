#include <bits/stdc++.h>
using namespace std;

/*
Megoldási ötlet:
A robot csak olyan csatornaszakaszt tud tisztítani, რომლის átmérője nagyobb a
robot méreténél. Ezek a „nagy” szakaszok a tisztító felé mutató fa irányában
egymás után következhetnek.

A minimális indulási pontok azok a csomópontok, amelyekből indulva van legalább
egy tisztítható szakasz felfelé, de alattuk már nincs további tisztítható szakasz.
Másképp: a nagy szakaszok által alkotott erdő leveleit kell kiválasztani.

Hint 1: || Csak a robotnál nagyobb átmérőjű szakaszok érdekesek. ||
Hint 2: || Egy robot egy nagy szakaszokból álló láncot tud végigtakarítani a tisztító felé. ||
Hint 3: || Az indulópontok a nagy szakaszok láncainak alsó végpontjai. ||
*/

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, R;
    cin >> N >> R;

    vector<int> parent(N + 1, 0), diam(N + 1, 0), largeChildCount(N + 1, 0);
    vector<vector<int>> children(N + 1);
    for (int i = 0; i < N - 1; ++i) {
        int a, b, d;
        cin >> a >> b >> d;
        parent[a] = b;
        diam[a] = d;
        children[b].push_back(a);
    }

    for (int u = 1; u <= N; ++u) {
        if (parent[u] != 0 && diam[u] > R) {
            ++largeChildCount[parent[u]];
        }
    }

    vector<int> startNodes;
    for (int u = 1; u <= N; ++u) {
        if (parent[u] != 0 && diam[u] > R && largeChildCount[u] == 0) {
            startNodes.push_back(u);
        }
    }
    sort(startNodes.begin(), startNodes.end());

    vector<int> memo(N + 1, -1);
    function<int(int)> calc = [&](int u) -> int {
        if (u == 0 || parent[u] == 0 || diam[u] <= R) return 0;
        if (memo[u] != -1) return memo[u];
        return memo[u] = 1 + calc(parent[u]);
    };

    cout << startNodes.size() << '\n';
    for (int i = 0; i < (int)startNodes.size(); ++i) {
        if (i) cout << ' ';
        cout << calc(startNodes[i]);
    }
    cout << '\n';
    return 0;
}