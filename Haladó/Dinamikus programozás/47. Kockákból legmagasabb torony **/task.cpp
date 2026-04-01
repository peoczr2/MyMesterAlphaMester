/*
A torony alulról felfelé nézve csak olyan kockákból állhat, amelyek oldalhossza és súlya is nem növekvő sorozatot ad.
Ha a kockákat oldalhossz szerint csökkenően rendezzük, akkor elég egy O(N^2) DP-t futtatni, amely minden kockára
megadja, mekkora torony teteje lehet. A szülőmutatók segítségével az egyik leghosszabb torony elemei sorban kiírhatók.
*/
/*
Hint 1: || Két dimenzióban kell részben rendezett láncot keresni: oldalhossz és súly szerint is. ||
Hint 2: || Érdemes előbb az egyik dimenzió szerint rendezni, és utána DP-vel ellenőrizni a másik feltételt is. ||
Hint 3: || A feladat a torony elemeit kéri, nem az eredeti indexeiket. ||
*/

#include <bits/stdc++.h>

using namespace std;

struct Cube {
    int side;
    int weight;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Cube> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].side >> a[i].weight;
    }

    sort(a.begin(), a.end(), [](const Cube& x, const Cube& y) {
        if (x.side != y.side) {
            return x.side > y.side;
        }
        return x.weight > y.weight;
    });

    vector<int> dp(n, 1), parent(n, -1);
    int best = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < i; ++j) {
            if (a[j].side >= a[i].side && a[j].weight >= a[i].weight && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > dp[best]) {
            best = i;
        }
    }

    vector<Cube> tower;
    for (int cur = best; cur != -1; cur = parent[cur]) {
        tower.push_back(a[cur]);
    }
    reverse(tower.begin(), tower.end());

    cout << tower.size() << '\n';
    for (const Cube& cube : tower) {
        cout << cube.side << ' ' << cube.weight << '\n';
    }
    return 0;
}
