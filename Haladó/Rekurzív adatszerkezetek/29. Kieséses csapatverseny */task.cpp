/*
Megoldási ötlet:
Kieséses versenyben minden csapat legfeljebb egyszer esik ki, tehát a gráfban a vesztesekhez legfeljebb
egy bejövő él tartozik. Ha az élt a győztestől a vesztes felé irányítjuk, akkor egy erdőt kapunk, amelynek
gyökerei a még versenyben levő csapatok. Ezután:
- még versenyben levő csapat: nincs bejövő éle;
- legalább egyszer győzött, de kiesett: van bejövő és kimenő éle is;
- legtöbb közvetlenül vagy közvetve legyőzött csapat: annak a csapatnak a részfája a legnagyobb,
  tehát a részfaméretből 1-et levonva kapjuk a legyőzöttek számát.
Az erdő részfaméreteit egy postorder bejárással kiszámítjuk.
*/
/*
Hint 1: || Irányítsd az éleket a győztestől a vesztes felé. Milyen szerkezetet kapsz egy kieséses versenyből? ||
Hint 2: || Azok maradtak versenyben, akikhez nem mutat él, mert őket még senki sem győzte le. ||
Hint 3: || Egy csapat közvetlenül vagy közvetve legyőzött ellenfelei pontosan a gyerekei részfájában vannak. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> children(n + 1);
    vector<int> indegree(n + 1, 0);
    vector<int> outdegree(n + 1, 0);

    for (int i = 0; i < m; ++i) {
        int winner, loser;
        cin >> winner >> loser;
        children[winner].push_back(loser);
        ++indegree[loser];
        ++outdegree[winner];
    }

    vector<int> alive;
    vector<int> wonButEliminated;
    for (int team = 1; team <= n; ++team) {
        if (indegree[team] == 0) {
            alive.push_back(team);
        }
        if (indegree[team] > 0 && outdegree[team] > 0) {
            wonButEliminated.push_back(team);
        }
    }

    vector<int> subtreeSize(n + 1, 0);
    vector<pair<int, bool>> stack;
    for (int root : alive) {
        stack.push_back({root, false});
        while (!stack.empty()) {
            auto [node, processed] = stack.back();
            stack.pop_back();
            if (!processed) {
                stack.push_back({node, true});
                for (int child : children[node]) {
                    stack.push_back({child, false});
                }
            } else {
                subtreeSize[node] = 1;
                for (int child : children[node]) {
                    subtreeSize[node] += subtreeSize[child];
                }
            }
        }
    }

    int bestTeam = 1;
    for (int team = 2; team <= n; ++team) {
        if (subtreeSize[team] > subtreeSize[bestTeam]) {
            bestTeam = team;
        }
    }

    cout << alive.size();
    for (int team : alive) {
        cout << ' ' << team;
    }
    cout << '\n';

    cout << wonButEliminated.size();
    for (int team : wonButEliminated) {
        cout << ' ' << team;
    }
    cout << '\n';

    cout << bestTeam << '\n';
    return 0;
}