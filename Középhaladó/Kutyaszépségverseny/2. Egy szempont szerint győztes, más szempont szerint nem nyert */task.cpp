/*
Megoldás lényege:
Szempontonként megkeressük a legjobb elért pontot, és a győztesek azok a kutyák, akik ezt kapták, feltéve, hogy a legjobb pont eléri az alsó ponthatárt. Kutyánként megszámoljuk, hány szempontban lettek győztesek, és a végén azokat írjuk ki, akiknek pontosan egy győzelmük van. Minden szempontot két lépésben dolgozunk fel: először a legjobb pont, majd a győztesek jelölése. Az időigény O(N·M), a memóriaigény O(N·M).
*/
/*
Hint 1: || Szempontonként határozd meg a legjobb pontot, és számold meg kutyánként, hány szempontban volt ezt elérve. A holtverseny is győzelem. ||
Hint 2: || Tarts N darab számlálót a győzelmeknek. Ha egy szempontban a legjobb pont az alsó ponthatár alatt van, azt a szempontot hagyd ki. A végén azoknak a kutyáknak a sorszámait írd ki, akiknek a számlálója pontosan 1. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    vector<int> mx(m), mn(m);
    for (int &x : mx) cin >> x;
    for (int &x : mn) cin >> x;

    vector<vector<int>> p(n, vector<int>(m));
    for (auto &row : p)
        for (int &x : row) cin >> x;

    vector<int> wins(n, 0);
    for (int j = 0; j < m; j++) {
        int best = -1;
        for (int i = 0; i < n; i++) best = max(best, p[i][j]);
        if (best < mn[j]) continue;
        for (int i = 0; i < n; i++)
            if (p[i][j] == best) wins[i]++;
    }

    vector<int> res;
    for (int i = 0; i < n; i++)
        if (wins[i] == 1) res.push_back(i + 1);

    cout << res.size();
    for (int x : res) cout << ' ' << x;
    cout << '\n';
    return 0;
}
