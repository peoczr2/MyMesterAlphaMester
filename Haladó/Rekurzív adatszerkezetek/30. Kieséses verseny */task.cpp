/*
Megoldási ötlet:
Az éleket itt is a győztestől a vesztes felé irányítjuk, így kieséses erdőt kapunk. Ebből:
1. a kiesettek közül legtöbbször győző csapat: azok közül választunk, akiknek van bejövő élük,
   és maximalizáljuk a kimenő élek számát;
2. a legtöbb közvetlenül vagy közvetve legyőzött csapat: a legnagyobb részfájú csapat, mert a
   részfa minden másik csúcsa általa lett legyőzve közvetlenül vagy közvetve;
3. a következő meccs két résztvevője: az élő (gyökér) csapatok közül azt a két csapatot kell venni,
   amelyek eddig a legkevesebb csapatot győzték le, vagyis a részfaméretük a legkisebb. Elegendő
   az élő csapatokat a (részfaméret, sorszám) kulcs szerint rendezni és az első kettőt venni.
*/
/*
Hint 1: || Az élők most is pontosan azok, akikhez nem mutat bejövő él. ||
Hint 2: || A közvetlen és közvetett legyőzöttek száma ugyanaz, mint a részfa mérete mínusz egy. ||
Hint 3: || A harmadik sorhoz csak az élő csapatokat kell vizsgálnod, és közülük a két legkisebb részfájút kiválasztanod. ||
*/

#include <algorithm>
#include <iostream>
#include <utility>
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
    for (int team = 1; team <= n; ++team) {
        if (indegree[team] == 0) {
            alive.push_back(team);
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

    int bestEliminated = -1;
    for (int team = 1; team <= n; ++team) {
        if (indegree[team] == 0) {
            continue;
        }
        if (bestEliminated == -1 || outdegree[team] > outdegree[bestEliminated] ||
            (outdegree[team] == outdegree[bestEliminated] && team < bestEliminated)) {
            bestEliminated = team;
        }
    }

    int bestOverall = 1;
    for (int team = 2; team <= n; ++team) {
        if (subtreeSize[team] > subtreeSize[bestOverall] ||
            (subtreeSize[team] == subtreeSize[bestOverall] && team < bestOverall)) {
            bestOverall = team;
        }
    }

    vector<pair<int, int>> liveTeams;
    for (int team : alive) {
        liveTeams.push_back({subtreeSize[team], team});
    }
    sort(liveTeams.begin(), liveTeams.end());

    cout << bestEliminated << '\n';
    cout << bestOverall << '\n';
    if (liveTeams.size() < 2) {
        cout << -1 << '\n';
    } else {
        int first = liveTeams[0].second;
        int second = liveTeams[1].second;
        if (first > second) {
            swap(first, second);
        }
        cout << first << ' ' << second << '\n';
    }

    return 0;
}