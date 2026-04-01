/*
Megoldási ötlet:
Az a legnagyobb részhalmaz kell, amelyben senki nem ismer senkit. A fa értelmezése szerint ez pontosan a független
halmaz problémája egy gyökerezett fában: egy ember és a közvetlen főnöke/beosztottja nem lehet egyszerre a halmazban.

Klasszikus fa-DP elég:
- `dp0[u]`: az `u` részfájában elérhető legnagyobb független halmaz mérete, ha `u` nincs kiválasztva;
- `dp1[u]`: ugyanez, ha `u` ki van választva.

Ekkor `dp1[u] = 1 + Σ dp0[gyerek]`, míg `dp0[u] = Σ max(dp0[gyerek], dp1[gyerek])`.
A kiválasztott csúcsok egy maximumot adó visszaépítéssel megadhatók.
*/
/*
Hint 1: || Ha valaki benne van a halmazban, a közvetlen főnöke és a közvetlen beosztottai biztosan nem lehetnek benne. ||
Hint 2: || Két állapot elég minden csúcsra: benne van vagy nincs benne. ||
Hint 3: || A végeredmény a gyökér két állapotának maximuma, majd egy visszaépítés adja a konkrét tagokat. ||
*/

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> children(n + 1);
    for (int node = 2; node <= n; ++node) {
        int boss;
        cin >> boss;
        children[boss].push_back(node);
    }

    vector<int> dp0(n + 1, 0), dp1(n + 1, 1);
    for (int node = n; node >= 1; --node) {
        dp1[node] = 1;
        dp0[node] = 0;
        for (int child : children[node]) {
            dp1[node] += dp0[child];
            dp0[node] += max(dp0[child], dp1[child]);
        }
    }

    vector<int> chosen;
    vector<pair<int, bool>> stack = {{1, false}};
    while (!stack.empty()) {
        auto [node, parentTaken] = stack.back();
        stack.pop_back();
        bool take = false;
        if (!parentTaken && dp1[node] >= dp0[node]) {
            take = true;
            chosen.push_back(node);
        }
        for (int child : children[node]) {
            stack.push_back({child, take});
        }
    }

    sort(chosen.begin(), chosen.end());
    cout << max(dp0[1], dp1[1]) << '\n';
    for (int i = 0; i < static_cast<int>(chosen.size()); ++i) {
        if (i > 0) cout << ' ';
        cout << chosen[i];
    }
    cout << '\n';
    return 0;
}