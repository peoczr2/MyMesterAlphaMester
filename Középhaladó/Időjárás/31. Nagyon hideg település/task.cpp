/*
Megoldás lényege:
Minden településre a sor beolvasása közben kiszámoljuk a napi hőmérsékletek összegét és a leghidegebb napjának értékét, így a teljes táblázatot nem kell tárolni. Az i. település átlaga (összeg / M) akkor kisebb a k. település leghidegebb napjánál, ha összeg_i < M * min_k; ez egész számokkal ellenőrizhető, nincs szükség törtre. Az i sorszámokat növekvő sorrendben vizsgáljuk, és az első olyan i-t írjuk ki, amelyre van ilyen k ≠ i település; ha nincs, -1. Az idő O(N*M + N^2), a memória O(N).
*/
/*
Hint 1: || Egy településről elég két számot tudni: a napi hőmérsékletek összegét és a leghidegebb napon mért értéket. Mindkettőt a sor beolvasása közben ki tudod számolni, nem kell a teljes táblázatot tárolnod. ||
Hint 2: || Az átlagok összehasonlításánál ne törtet számolj: az i. település átlaga pontosan akkor kisebb a k. leghidegebb napjánál, ha összeg_i < M * min_k. Minden i-re nézd meg, van-e ilyen másik k település, és a sorszámok sorrendjében az első találat kell. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> sum(n + 1, 0);
    vector<int> minimum(n + 1, INT_MAX);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            sum[i] += h;
            minimum[i] = min(minimum[i], h);
        }
    }

    for (int i = 1; i <= n; i++) {
        bool ok = false;
        for (int k = 1; k <= n && !ok; k++) {
            if (k != i && sum[i] < (long long)m * minimum[k]) ok = true;
        }
        if (ok) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
