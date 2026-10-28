/*
Megoldás lényege:
A járatok mindig keletre mennek, ezért a repülési gráf körmentes. Minden városra eldöntjük, hogy az ott éppen választó
játékos nyer-e. Ha egy városból nincs járat, a választó nem tud lépni, tehát veszít. Egy város nyerő, ha van olyan kimenő
járata, amelynél a másik játékos a következő városban veszít. Egy város vesztő, ha minden kimenő járata nyerő helyzetbe
viszi a másik játékost. A döntést a járatok fordított irányában terjesztjük (Kahn-algoritmussal, a kimenő járatok számát
csökkentve), így egy város akkor dől el, amikor minden célvárosa már eldőlt. Aladár kezd, így a kezdővárosban ő nyer,
ha az a nyerő helyzet. Az időigény O(N + M + Q).
*/
/*
Hint 1: || Csak azt kell tudnod minden városról, hogy az ott választó játékos nyer-e. Az a játékos nyer, aki a végső járatot
választotta, tehát a városban az nyer, aki olyan járatot tud választani, amelyről a másik vesztes helyzetbe kerül. ||
Hint 2: || A városokat a járatok fordított irányában dolgozd fel. Minden városhoz számold, hány kimenő járata van; ha egy
város célvárosai közül valamelyik vesztes, a város nyer, ha pedig az összes célváros nyerő, a város veszít. Az üres
kimenetű városok veszítenek. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    vector<int> starts(q);
    for (int& s : starts) {
        cin >> s;
    }

    // in[v]: azok a városok, ahonnan v-be vezet járat; outdeg[u]: u kimenő járatainak száma.
    vector<vector<int>> in(n + 1);
    vector<int> outdeg(n + 1, 0);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        in[v].push_back(u);
        ++outdeg[u];
    }

    // win[v]: nyer-e az a játékos, aki v-ben éppen járatot választ.
    vector<char> decided(n + 1, 0), win(n + 1, 0);
    queue<int> todo;
    for (int v = 1; v <= n; ++v) {
        if (outdeg[v] == 0) {
            decided[v] = 1;
            win[v] = 0;
            todo.push(v);
        }
    }

    while (!todo.empty()) {
        int v = todo.front();
        todo.pop();
        for (int u : in[v]) {
            if (decided[u]) {
                continue;
            }
            if (!win[v]) {
                // A másik játékos v-ben veszít, tehát u-ban a választó nyer.
                decided[u] = 1;
                win[u] = 1;
                todo.push(u);
            } else if (--outdeg[u] == 0) {
                // Minden célváros nyerő a másik játékosnak, tehát u vesztes.
                decided[u] = 1;
                win[u] = 0;
                todo.push(u);
            }
        }
    }

    // Aladár kezd a kezdővárosban.
    for (int s : starts) {
        cout << (win[s] ? "A" : "B") << '\n';
    }
    return 0;
}
