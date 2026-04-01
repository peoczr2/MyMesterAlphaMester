/*
Megoldasi otlet:
Minden varosbol pontosan egy masik varosba megy a szallitasi ut, ezert a rendszer
egy gyokeres fa a 1-es varos felé mutatva. A kamionok a levelekbol indulnak, es
egy utjuk soran minden erintett varos termeleset felveszik.

Ezert egy kamionhoz szukseges kapacitas pontosan az adott leveltol a gyokerig
vezeto ut ossztermelese. A feladat valasza ezek kozul a legnagyobb ertek.

Hint 1: || A kamionok mindig a beszallasi pontokbol indulnak, vagyis azokbol a varosokbol, amelyekbe nem erkezik masik varosbol kamion. ||
Hint 2: || Egy kamion kapacitasat az utja menten osszegzett termeles hatarozza meg. ||
Hint 3: || Ezert eleg a gyokerbol egy DFS-sel vegigmenni, es minden levelre eltárolni a gyokerig tartó osszeget. ||
*/

#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> parent(N + 1, 0);
    vector<long long> prod(N + 1, 0);
    vector<vector<int>> children(N + 1);
    vector<int> indeg(N + 1, 0);

    for (int city = 2; city <= N; ++city) {
        int to;
        long long amount;
        cin >> to >> amount;
        parent[city] = to;
        prod[city] = amount;
        children[to].push_back(city);
        ++indeg[to];
    }

    long long answer = 0;
    function<void(int, long long)> dfs = [&](int u, long long sum) {
        sum += prod[u];
        if (children[u].empty()) {
            answer = max(answer, sum);
            return;
        }
        for (int v : children[u]) dfs(v, sum);
    };

    dfs(1, 0);
    cout << answer << '\n';
    return 0;
}