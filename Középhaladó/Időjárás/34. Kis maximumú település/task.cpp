/*
Megoldás lényege:
Egy település maximális előrejelzéséhez és a hőmérsékletek összegéhez elég a sor beolvasása közben számolni. Az i. település maximuma akkor kisebb a k. település átlagánál, ha max_i < összeg_k / M, ami egész számokkal max_i * M < összeg_k alakban ellenőrizhető. Az i sorszámokat növekvő sorrendben vizsgáljuk, és az első olyan i-t írjuk ki, amelyre van ilyen k ≠ i település; ha nincs, -1. Az idő O(N*M + N^2), a memória O(N).
*/
/*
Hint 1: || Egy településről két adat kell: a napi előrejelzések maximuma, és a hőmérsékletek összege, amiből az átlag adódik. Mindkettő a sor beolvasása közben számolható. ||
Hint 2: || Az „átlagnál kisebb” feltételt szorzással is felírhatod: max_i < összeg_k / M pontosan akkor, ha max_i * M < összeg_k. Minden i-re keress olyan k ≠ i települést, amelyre ez teljesül. ||
*/
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<long long> sum(n + 1, 0);
    vector<int> maximum(n + 1, INT_MIN);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int h;
            cin >> h;
            sum[i] += h;
            maximum[i] = max(maximum[i], h);
        }
    }

    for (int i = 1; i <= n; i++) {
        bool ok = false;
        for (int k = 1; k <= n && !ok; k++) {
            if (k != i && (long long)maximum[i] * m < sum[k]) ok = true;
        }
        if (ok) {
            cout << i << '\n';
            return 0;
        }
    }

    cout << -1 << '\n';
    return 0;
}
