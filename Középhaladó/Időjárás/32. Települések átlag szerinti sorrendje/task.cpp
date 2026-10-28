/*
Megoldás lényege:
Mivel minden településnek ugyanannyi (M) napja van, az átlagok sorrendje megegyezik az összegek sorrendjével, így törtet nem kell számolnunk. A sorok beolvasása közben minden településre kiszámoljuk a hőmérsékletek összegét, majd a sorszámokat ebben a sorrendben rendezzük: csökkenő összeg szerint, egyenlő összegnél a kisebb sorszám kerül előre. Az idő O(N*M + N log N), a memória O(N).
*/
/*
Hint 1: || Az átlagok sorrendjéhez nem kell osztani: minden településnek ugyanannyi napja van, így az összegek ugyanabban a sorrendben állnak, mint az átlagok. ||
Hint 2: || Tárold az összegeket és a sorszámokat egy vektorban, és a `sort` függvénynek adj olyan összehasonlítót, amely először az összeg szerint csökkenőt rendez, egyenlő összegnél pedig a kisebb sorszámot teszi előre. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> sum(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            sum[i] += h;
        }
    }

    vector<int> order(n);
    for (int i = 0; i < n; i++) order[i] = i + 1;
    sort(order.begin(), order.end(), [&](int a, int b) {
        if (sum[a] != sum[b]) return sum[a] > sum[b];
        return a < b;
    });

    for (int i = 0; i < n; i++) {
        if (i > 0) cout << ' ';
        cout << order[i];
    }
    cout << '\n';
    return 0;
}
