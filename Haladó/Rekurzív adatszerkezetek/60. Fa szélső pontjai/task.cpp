/*
Megoldási ötlet:
Az ordered tree szintenkénti balról-jobbra sorrendje a gyerekek felsorolásából adódik. Egy csúcs szélső pont akkor,
ha az adott szinten ő az első vagy az utolsó megjelenő csúcs.

Ezért egy balról jobbra haladó BFS elegendő. Minden mélységnél eltesszük az elsőként és az utolsóként látott csúcsot,
majd ezek unionját adjuk vissza.
*/
/*
Hint 1: || Szintenként csak az első és az utolsó csúcs számít. ||
Hint 2: || A gyerekeket balról jobbra kell bejárni, különben a szélek rosszak lehetnek. ||
Hint 3: || A végén az összes ilyen first/last csúcs unionja a válasz. ||
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    for (int node = 1; node <= n; ++node) {
        while (true) {
            int child;
            cin >> child;
            if (child == 0) {
                break;
            }
            children[node].push_back(child);
        }
    }

    vector<int> depth(n + 1, 0), first(n + 1, 0), last(n + 1, 0), result;
    queue<int> q;
    q.push(1);
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        int d = depth[node];
        if (first[d] == 0) {
            first[d] = node;
        }
        last[d] = node;
        for (int child : children[node]) {
            depth[child] = d + 1;
            q.push(child);
        }
    }

    vector<char> marked(n + 1, false);
    for (int d = 0; d <= n; ++d) {
        if (first[d] != 0 && !marked[first[d]]) {
            marked[first[d]] = true;
            result.push_back(first[d]);
        }
        if (last[d] != 0 && !marked[last[d]]) {
            marked[last[d]] = true;
            result.push_back(last[d]);
        }
    }

    cout << result.size() << '\n';
    for (int i = 0; i < static_cast<int>(result.size()); ++i) {
        if (i > 0) cout << ' ';
        cout << result[i];
    }
    cout << '\n';
    return 0;
}